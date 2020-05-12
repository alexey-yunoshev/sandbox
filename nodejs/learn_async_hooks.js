// source https://itnext.io/a-pragmatic-overview-of-async-hooks-api-in-node-js-e514b31460e9

const asyncHooks = require('async_hooks');
const fs = require('fs');

const track = (types) => {
    // will contain metadata for all tracked events
    this._tracked = {}
    const asyncHook = asyncHooks.createHook({
      init: (asyncId, type, triggerAsyncId, resource) => {
        if (!types || types.includes(type)) {
          const meta = {
            asyncId,
            type,
            pAsyncId: triggerAsyncId,
            res: resource
          }
          this._tracked[asyncId] = meta
          printMeta('init', meta)
        }
      },
      before: (asyncId) => {
        const meta = this._tracked[asyncId]
        if (meta) printMeta('before', meta)
      },
      after: (asyncId) => {
        const meta = this._tracked[asyncId]
        if (meta) printMeta('after', meta)
      },
      destroy: (asyncId) => {
        const meta = this._tracked[asyncId]
        if (meta) printMeta('destroy', meta)
        // delete meta for the event
        delete this._tracked[asyncId]
      },
      promiseResolve: (asyncId) => {
        const meta = this._tracked[asyncId]
        if (meta) printMeta('promiseResolve', meta)
      }
    })
    asyncHook.enable()
    function printMeta (eventName, meta) {
      console.log(`[${eventName}] asyncId=${meta.asyncId}, ` +
        `type=${meta.type}, pAsyncId=${meta.pAsyncId}, ` +
        `res type=${meta.res.constructor.name}`)
    }
}

// track((['Timeout']));

// setTimeout(() => {
//     console.log('Timeout 1 happened')
//     setTimeout(() => {
//       console.log('Timeout 2 happened')
//     }, 0)
//     console.log('Registered timeout 2')
//   }, 0)
//   console.log('Registered timeout 1')

track((['PROMISE']));

// Promise.resolve()
// console.log('Registered Promise.resolve')

Promise.reject()
  .catch(() => console.log('Promise.reject callback'))
console.log('Registered Promise.reject')