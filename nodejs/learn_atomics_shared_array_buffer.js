const threads = require('worker_threads');
const {Worker, isMainThread, parentPort, workerData} = threads;

if (isMainThread) {
    const buffer = new SharedArrayBuffer(1024);
    const array = new Int32Array(buffer);

    const worker = new Worker(__filename, {workerData: {buffer}});
    worker.on('message', (...args) => {
        console.log('message from child', array);
    })
    worker.on('error', (...args) => {
        console.log('child error', {args});
    })
    worker.on('exit', (...args) => {
        console.log('child exit', {args});
    })

    const w1 = Atomics.wait(array, 6, 0, 3000);
    console.log('w1', w1)
} else {
    const {buffer} = threads.workerData;
    const array = new Int32Array(buffer); 
    Atomics.store(array, 6, 123);
    Atomics.notify(array, 6);
    parentPort.postMessage('sup');
}
