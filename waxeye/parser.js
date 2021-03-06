/*
 * Generated by the Waxeye Parser Generator - version 0.8.1
 * www.waxeye.org
 */

var waxeye = waxeye;
if (typeof module !== 'undefined') {
    // require from module system
    waxeye = require('waxeye');
}

function Parser() {}
Parser.prototype = new waxeye.WaxeyeParser(
{'calc': { mode: 1 /* NORMAL */, exp: { type: 3 /* SEQ */, exprs: [{ type: 1 /* NT */, name: 'ws' }, { type: 1 /* NT */, name: 'sum' }] } },
    'sum': { mode: 1 /* NORMAL */, exp: { type: 3 /* SEQ */, exprs: [{ type: 1 /* NT */, name: 'prod' }, { type: 5 /* STAR */, expr: { type: 3 /* SEQ */, exprs: [{ type: 12 /* CHAR_CLASS */, codepoints: [0x2b, 0x2d] }, { type: 1 /* NT */, name: 'ws' }, { type: 1 /* NT */, name: 'prod' }] } }] } },
    'prod': { mode: 1 /* NORMAL */, exp: { type: 3 /* SEQ */, exprs: [{ type: 1 /* NT */, name: 'unary' }, { type: 5 /* STAR */, expr: { type: 3 /* SEQ */, exprs: [{ type: 12 /* CHAR_CLASS */, codepoints: [0x2a, 0x2f] }, { type: 1 /* NT */, name: 'ws' }, { type: 1 /* NT */, name: 'unary' }] } }] } },
    'unary': { mode: 2 /* PRUNING */, exp: { type: 2 /* ALT */, exprs: [{ type: 3 /* SEQ */, exprs: [{ type: 11 /* CHAR */, char: '-' }, { type: 1 /* NT */, name: 'ws' }, { type: 1 /* NT */, name: 'unary' }] }, { type: 3 /* SEQ */, exprs: [{ type: 9 /* VOID */, expr: { type: 11 /* CHAR */, char: '(' } }, { type: 1 /* NT */, name: 'ws' }, { type: 1 /* NT */, name: 'sum' }, { type: 9 /* VOID */, expr: { type: 11 /* CHAR */, char: ')' } }, { type: 1 /* NT */, name: 'ws' }] }, { type: 1 /* NT */, name: 'num' }] } },
    'num': { mode: 1 /* NORMAL */, exp: { type: 3 /* SEQ */, exprs: [{ type: 4 /* PLUS */, expr: { type: 12 /* CHAR_CLASS */, codepoints: [[0x30, 0x39]] } }, { type: 6 /* OPT */, expr: { type: 3 /* SEQ */, exprs: [{ type: 11 /* CHAR */, char: '.' }, { type: 4 /* PLUS */, expr: { type: 12 /* CHAR_CLASS */, codepoints: [[0x30, 0x39]] } }] } }, { type: 1 /* NT */, name: 'ws' }] } },
    'ws': { mode: 3 /* VOIDING */, exp: { type: 5 /* STAR */, expr: { type: 12 /* CHAR_CLASS */, codepoints: [[0x9, 0xa], 0xd, 0x20] } } }}
, 'calc');

// Add to module system
if (typeof module !== 'undefined') {
    module.exports.Parser = Parser;
}
