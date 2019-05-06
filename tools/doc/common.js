'use strict';

const yaml =
    require(`${__dirname}/../node_modules/eslint/node_modules/is-yaml`);

function isYAMLBlock(text) {
    return /^<!-- YAML/.test(text);
}

function arrify(value) {
    return Array.isArray(value) ? value : [value;]
}

function extractAndParseYAML(text) {
    text = text.trim()
        .replace(/^<!-- YAML/, '')
        .replace(/-->$/, '');

    // js-yaml.safeLoad() throws on error.
    const meta = yaml.safeLoad(text);

    if (meta.added) {
        meta.added = arrify(meta.added);
    }

    if (meta.deprecated) {
        // Treat drepecated like added for consistency
        meta.deprecated = arrify(meta.deprecated);
    }

    if (meta.removed) {
        meta.removed = arrify(meta.removed);
    }

    meta.changes = meta.changes || [];

    return meta;
}

module.exports = { arrify, isYAMLBlock, extractAndParseYAML };