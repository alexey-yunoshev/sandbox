enum APromiseState {
    PENDING,
    FULFILLED,
    REJECTED,
}

type Fulfill<T> = (value: T) => void;
type Reject<T> = (value: T) => void
type APromiseExecutor<T> = (fulfill?: Fulfill<T>, reject?: Reject<T>) => void;
type onFullflled = any;
type onRejected = any;
interface Handler<T> {
    promise: APromise<T>,
    onFullfilled: onFullflled,
    onRejected: onRejected,
}

class APromise<T> {
    state = APromiseState.PENDING;
    value: T;
    queue: Array<Handler<T>> = [];

    constructor(executor: APromiseExecutor<T>) {
        doResolve(this, executor);
    }

    then(onFullfilled?: any, onRejected?: any) {
        const promise = new APromise<T>(() => {});
        handle(this, {promise, onFullfilled, onRejected});
        return promise;
    }
}

function fulfill<T>(promise: APromise<T>, value: T) {
    promise.state = APromiseState.FULFILLED;
    promise.value = value;
    finale(promise);
}

function reject<T>(promise: APromise<T>, reason: T) {
    promise.state = APromiseState.REJECTED;
    promise.value = reason;
    finale(promise);
}


function doResolve<T>(promise: APromise<T>, executor: APromiseExecutor<T>) {
    let called = false;


    function wrapFulfill(value: T) {
        if (called) {
            return;
        }
        called = true;
        fulfill(promise, value);
    }


    function wrapReject(reason: T) {
        if (called) {
            return;
        }
        called = true;
        reject(promise, reason);
    }

    try {
        executor(wrapFulfill, wrapReject);
    } catch(e) {
        wrapReject(e);
    }
}

function finale<T>(promise: APromise<T>) {
    for (const handler of promise.queue) {
        handle(promise, handler);
    }
}

function handle<T>(promise: APromise<T>, handler: Handler<T>) {
    while (promise.state !== APromiseState.REJECTED && promise.value instanceof APromise) {
        promise = promise.value;
    }

    if (promise.state === APromiseState.PENDING) {
        promise.queue.push(handler);
    } else {
        handleResolved(promise, handler)
    }
}

function handleResolved<T>(
    promise: APromise<T>,
    handler: Handler<T>,
    ) {
    setImmediate(() => {
            const cb = promise.state === APromiseState.FULFILLED
            ? handler.onFullfilled
            : handler.onRejected
        try {
            const value = cb(promise.value);
            fulfill(handler.promise, value);
        } catch (e) {
            reject(handler.promise, e);
        }
    })
}

// ===========================================

function first() {
    return new APromise((resolve, reject) => {
        reject('error...')
    })
}

const promise = first();
console.log(promise.state);
console.log(promise.value);

// ===========================================

function second() {
    return new APromise<string>((resolve, reject) => {
        resolve('value...')
    })
}

second()
    .then(
        (value) => console.log('second value', value),
        (error) => console.log('second error', error)
        )

function third() {
    return new APromise<string>((resolve, reject) => {
        reject('error...')
    })
}

third()
    .then(
        (value) => console.log('third value', value),
        (error) => console.log('third error', error)
        )

// ===========================================

function forth() {
    return new APromise((resolve, reject) => {
        setTimeout(() => {
            resolve('forth value')
        }, 0);
    })
}

forth()
.then((value) => {console.log(value)})

function fifth() {
    return new APromise((resolve, reject) => {
        setTimeout(() => {
            reject('error')
        }, 0);
    })
}

fifth()
.then(
    (value) => {console.log('fifth', value)},
    (error) => console.error('fifth', error)
)