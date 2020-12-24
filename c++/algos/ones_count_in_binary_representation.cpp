#include <iostream>
#include <fstream>
#include <string>
#include <functional>

int main() {
    int bits_count = (sizeof 1) * 8;
    int result = 0;
    int example = 6985286;

    int mask = 1;

    if ((example & mask) > 0) {
        result++;
    }

    for (int i = 1; i < bits_count; i++) {
        mask = mask << 1;
        if ((example & mask) > 0) {
            result++;
        }
    }

    printf("%d\n", result);

    return 0;
}