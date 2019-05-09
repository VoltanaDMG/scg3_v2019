'use strict';

const fs = require('fs');
const path = require('path');
const unified = require('unified');
const markdown = require('remark-parse');
const remark2rehype = require('remark-rehype');
const raw = require('rehype-raw');
const htmlStringify = require('rehype-stringify');

const html = require('./html');
const json = require('./json');

// Parse the args.
// Don't use nopt or whatever for this. It's simple enough.

const args = process.argv.slice(2);
let filename = null;
let nodeVersion = null;
let outputDir = null;
let apilinks = {};

args.forEach((arg) => {
  if (!arg.startsWith('--')) {
    filename = arg;
  } else if (arg.startsWith('--node-version=')) {
    nodeVersion = arg.replace(/^--node-version=/, '');
  } else if (arg.startsWith('--output-directory=')) {
    outputDir = arg.replace(/^--output-directory=/, '');
  } else if (arg.startsWith('--apilinks=')) {
    const linkFile = arg.replace(/^--apilinks=/, '');
    const data = fs.readFileSync(linkFile, 'utf8');
    if (!data.trim()) {
      throw new Error(`${linkFile} is empty`);
    }
    apilinks = JSON.parse(data);
  }
});

nodeVersion = nodeVersion || process.version;

if (!filename) {
  throw new Error('No input file specified');
} else if (!outputDir) {
  throw new Error('No output directory specified');
}


fs.readFile(filename, 'utf8', (er, input) => {
  if (er) throw er;

  const content = unified()
    .use(markdown)
    .use(html.preprocessText)
    .use(json.jsonAPI, { filename })
    .use(html.firstHeader)
    .use(html.preprocessElements, { filename })
    .use(html.buildToc, { filename, apilinks })
    .use(remark2rehype, { allowDangerousHTML: true })
    .use(raw)
    .use(htmlStringify)
    .processSync(input);

  const basename = path.basename(filename, '.md');

  html.toHTML(
    { input, content, filename, nodeVersion },
    (err, html) => {
      const target = path.join(outputDir, `${basename}.html`);
      if (err) throw err;
      fs.writeFileSync(target, html);
    }
  );

  const target = path.join(outputDir, `${basename}.json`);
  fs.writeFileSync(target, JSON.stringify(content.json, null, 2));
});