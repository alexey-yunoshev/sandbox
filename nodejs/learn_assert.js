const assert = require("assert").strict;

try {
    assert.deepStrictEqual({ a: 1 }, { a: '1' });
} catch (e) {
    // console.error(e);
    debugger;
}