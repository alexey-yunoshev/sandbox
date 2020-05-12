const PENDING = 'PENDING'
const FULFILLED = 'FULFILLED'
const REJECTED = 'REJECTED'

class APromise {
  constructor(executor) {
    // initial state
    this.state = PENDING
    // the fulfillment value or rejection reason is mapped internally to `value`
    // initially the promise doesn't have a value

    // .then handler queue
    this.queue = []

    // call the executor immediately
    doResolve(this, executor)
  }

  then(onFulfilled, onRejected) {
    // empty executor
    const promise = new APromise(() => {})
    // store the promise too
    handle(this, { promise, onFulfilled, onRejected })
    return promise
  }
}

// checks the state of the promise to either:
// - queue it for later use if the promise is PENDING
// - call the handler if the promise is not PENDING
function handle(promise, handler) {
  // take the state of the innermost promise
  while (promise.state !== REJECTED && promise.value instanceof APromise) {
    promise = promise.value
  }

  if (promise.state === PENDING) {
    // queue if PENDING
    promise.queue.push(handler)
  } else {
    // execute immediately
    handleResolved(promise, handler)
  }
}

// call either the onFulfilled or onRejected function
function handleResolved(promise, handler) {
  setImmediate(() => {
    const cb = promise.state === FULFILLED ? handler.onFulfilled : handler.onRejected

    // resolve immediately if the handler is not a function
    if (typeof cb !== 'function') {
      if (promise.state === FULFILLED) {
        fulfill(handler.promise, promise.value)
      } else {
        reject(handler.promise, promise.value)
      }
      return
    }

    // execute the handler and transition according to the rules
    try {
      const value = cb(promise.value)
      fulfill(handler.promise, value)
    } catch (err) {
      reject(handler.promise, err)
    }
  })
}

// fulfill with `value`
function fulfill(promise, value) {
  if (value === promise) {
    return reject(promise, new TypeError())
  }
  if (value && (typeof value === 'object' || typeof value === 'function')) {
    let then
    try {
      then = value.then
    } catch (err) {
      return reject(promise, err)
    }

    // promise
    if (then === promise.then && promise instanceof APromise) {
      promise.state = FULFILLED
      promise.value = value
      return finale(promise)
    }

    // thenable
    if (typeof then === 'function') {
      return doResolve(promise, then.bind(value))
    }
  }
  promise.state = FULFILLED
  promise.value = value
  finale(promise)
}

// reject with `reason`
function reject(promise, reason) {
  promise.state = REJECTED
  promise.value = reason
  finale(promise)
}

// invoke all the handlers stored in the promise
function finale(promise) {
  const length = promise.queue.length
  for (let i = 0; i < length; i += 1) {
    handle(promise, promise.queue[i])
  }
}

// creates the fulfill/reject functions that are arguments of the executor
function doResolve(promise, executor) {
  let called = false

  function wrapFulfill(value) {
    if (called) {
        return
    }
    called = true
    fulfill(promise, value)
  }

  function wrapReject(reason) {
    if (called) {
        return
    }
    called = true
    reject(promise, reason)
  }

  try {
    executor(wrapFulfill, wrapReject)
  } catch (err) {
    wrapReject(err)
  }
}

// function first() {
//     return new APromise((resolve, reject) => {
//         reject('error...')
//     })
// }

// const promise = first();
// console.log(promise.state);
// console.log(promise.value);

// // ===========================================

// function second() {
//     return new APromise((resolve, reject) => {
//         resolve('value...')
//     })
// }

// second()
//     .then(
//         (value) => console.log('second value', value),
//         (error) => console.log('second error', error)
//         )

// function third() {
//     return new APromise<string>((resolve, reject) => {
//         reject('error...')
//     })
// }

// third()
//     .then(
//         (value) => console.log('third value', value),
//         (error) => console.log('third error', error)
//         )

// // ===========================================

function forth() {
    return new APromise((resolve, reject) => {
        setTimeout(() => {
            resolve('forth value')
        }, 0);
    })
}

const promise1 = forth()
promise1.then((value) => {console.log(value)})
promise1.then(() => forth())
promise1.then((value) => console.log(value, 'again'))

// function fifth() {
//     return new APromise((resolve, reject) => {
//         setTimeout(() => {
//             reject('error')
//         }, 0);
//     })
// }

// fifth()
// .then(
//     (value) => {console.log('fifth', value)},
//     (error) => console.error('fifth', error)
// )