const outer = [1, 2];
const inner = [3, 4];

outerloop:
for (const n1 of outer) {
    for (const n2 of inner) {
        console.log('inside inner loop')
        console.log(n2 == 3)
        if (n2 === 3) {
            continue outerloop;
        }
        console.log(n1, n2);
    }
}
