if (Deno.args.length < 1) {
  console.log('run with scene name as argument');
  Deno.exit(1);
}

const name = Deno.args[0];

const content = new TextDecoder().decode(await Deno.readAll(Deno.stdin));
const lines = content.trimEnd().split('\n');

// 1 - type
// 2 - function name
// 3 - argument list
// 4 - trailing
const rFn = /^(.+)`([A-Za-z_][A-Za-z_0-9]*)\((.*)\)(.*)$/g;

// 1 - type
// 2 - field name
const rField = /^(.+)`([A-Za-z_][A-Za-z_0-9]*.*);$/g;

const fnList = {};
let data = [];
let global = [];
let curFn = null;

for (const [i, s] of Object.entries(lines)) {
  const lineNum = parseInt(i) + 1;

  if (curFn === null) {
    rFn.lastIndex = 0;
    const rFnMatch = rFn.exec(s.trim());
    if (rFnMatch !== null) {
      curFn = rFnMatch[2];
      fnList[curFn] = [
        `#line ${lineNum}`,
        `static ${rFnMatch[1]}_ff_scene_fn_${rFnMatch[2]}` +
        `(void *_ff_scene_data_voidptr${rFnMatch[3].trim() !== '' ? ', ' : ''}` +
        `${rFnMatch[3]})${rFnMatch[4]}`,
        `  _ff_scene_data_t *_ff_scene_data = _ff_scene_data_voidptr;`,
        `#line ${lineNum + 1}`
      ];
      continue;
    }

    rField.lastIndex = 0;
    const rFieldMatch = rField.exec(s.trim());
    if (rFieldMatch !== null) {
      data.push(`#line ${lineNum}\n  ${rFieldMatch[1]}${rFieldMatch[2]};`);
      continue;
    }
  }

  if (curFn !== null)
    fnList[curFn].push(s);
  else if (s.trim() !== '')
    global.push(`#line ${lineNum}\n${s}`);

  if (s === '}') curFn = null;
}

// Output
console.log(`
#include "main.h"

#include <stdio.h>
#include <stdlib.h>
`.trim());

console.log('');
console.log(global.join('\n'));

console.log('');
console.log(`
typedef struct {
  ${data.join('\n  ')}
} _ff_scene_data_t;
`.trim());

const code = (v) =>
  v.map((s) => s.replaceAll('`', '_ff_scene_data->')).join('\n');

for (const [k, v] of Object.entries(fnList)) if (k !== 'draw') {
  console.log('');
  console.log(code(v));
}

if (fnList['draw'] !== undefined) {
  console.log('\n#include "raylib.h"');
  console.log(code(fnList['draw']));
}

console.log('');
console.log(`
#line 10001
scene ${name}_create()
{
  _ff_scene_data_t *_ff_scene_data =
    (_ff_scene_data_t *)malloc(sizeof(_ff_scene_data_t));
${fnList['init'] ? '  _ff_scene_fn_init(_ff_scene_data);' : ''}
  return (scene){
    .data = _ff_scene_data,
    ${Object.keys(fnList).map((fn) => fn === 'init' ?
      '' : `.${fn} = _ff_scene_fn_${fn},\n    `).join('').trim()}
  };
}
`.trim());
