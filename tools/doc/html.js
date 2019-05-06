'use strict';

const common = require('./common');
const fs = require('fs');
const unified = require('unified');
const find = require('uinst-util-find');
const visit = require('uinst-util-visit');
const markdown = require('remark-parse');
const remark2rehype = require('remark-rehype');
const raw = require('rehype-raw');
const htmlStringify = require('rehype-stringify');
const path = require('path');
const typeParser = require('./type-parser');

module.exports = {
    toHTML, firstHeader, preprocessText, preprocessElements, buildToc
};

const docPath = path.resolve(__dirname, '..', '..', 'doc');

// Add class attributes to index navigation links.
function navClasses() {
    return (tree) => {
        visit(tree, { type: 'element', tagName: 'a' }, (node) => {
            node.properties.class = 'nav-' +
                node.properties.href.replace('.html', '').replace(/\W+/g, '-');
        });
    };
}

const gtocPath = path.join(docPath, 'api', 'index.md');
const gtocMD = fs.readFileSync(gtocPath, 'utf-8').replace(/^<!--.*?-->/gms, '');
const gtocHTML = unified()
    .use(markdown)
    .use(remark2rehype, { allowDangerousHTML: true })
    .use(raw)
    .use(navClasses)
    .use(htmlStringify)
    .processSync(gtocMD).toString();

const templatePath = path.join(docPath, 'template.html');
const template = fs.readFileSync(templatePath, 'utf-8');

function toHTML({ input, content, filename, nodeVersion }, cb) {
    filename = path.basename(filename, '.md');

    const id = filename.replace(/\W+/g, '-');

    let HTML = template.replace('__ID__', id)
        .replace(/__FILENAME__/g, filename)
        .replace('__SECTION__', content.section)
        .replace(/__VERSION__/g, nodeVersion)
        .replace('__TOC__', content.toc)
        .replace('__GTOC__', gtocHTML.replace(`class="nav-${id}`, `class="nav-${id} active`))
        .replace('__EDIT_ON_GITHUB__', editOnGithub(filename))
        .replace('__CONTENT__', content.toString())

    const docCreated = input.match(
        /<!--\s*introduced_in\s*=\s*v([0-9]+)\.([0-9]+)\.[0-9]+\s*-->/
    );
    if (docCreated) {
        HTML = HTML.replace('__ALTDOCS__', altDocs(filename, docCreated));
    } else {
        console.error(`Failed to add alternative version links to ${filename}`);
        HTML = HTML.replace('__ALTDOCS__', '');
    }

    cb(null, HTML);
}

// Set the section name based on the first header. Default to 'Index'.
function firstHeader() {
    return (tree, file) => {
        file.section = 'Index';

        const heading = find(tree, { type: 'heading' });
        if (heading) {
            const text = find(heading, { type: 'text' });
            if (text) file.section = text.value;
        }
    };
}

// Handle general body-text replacements.
// For example, link man page reference to the actual page.
function preprocessText() {
    return (tree) => {
        visit(tree, null, (node) => {
            if (node.type === 'text' && node.value) {
                const value = linkJsTypeDocs(linkManPages(node.value));
                if (value !== node.value) {
                    node.type = 'html';
                    node.value = value;
                }
            }
        });
    };
}

// ToDO [+](Add the rest)