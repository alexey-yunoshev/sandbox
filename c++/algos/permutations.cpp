#include <iostream>
#include <fstream>
#include <string>
#include <functional>

// https://stackoverflow.com/questions/1995328/are-there-any-better-methods-to-do-permutation-of-string

void permutation(int k, std::string &s) {
    printf("-------start---------\n");

    for (int j = 1; j < s.size(); ++j) {
        printf("j = %d\n", j);
        printf("k = %d\n", k);
        std::cout << "s before: " << s << std::endl;
        std::swap(s[k % (j + 1)], s[j]);
        std::cout << "s after: " << s << std::endl;
        k = k / (j + 1);
    }
    printf("--------end--------\n");
}

int factorial(int n) {
    int result = 1;
    while (n != 0) {
        result *= n;
        n--;
    }
    return result;
}

int main() {
    std::string example = "abcd";

    for (int k = 0; k < factorial(example.length()); k++) {
        permutation(k, example);
        std::cout << example << "\n";
    }
    return 0;
}