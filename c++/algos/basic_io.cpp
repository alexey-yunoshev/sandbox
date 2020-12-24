// basic file operations
#include <iostream>
#include <fstream>
#include <string>
#include <functional>

using namespace std;

#define IMPORT "#include "

string get_relative_module_name(string line) {
    string module_name = "";
    bool add = false;
    int seen_quotes_count = 0;

    for (const char& letter : line) {
        if (letter == '"') {
            seen_quotes_count++;

            if (seen_quotes_count == 1) {
                add = true;
                continue;
            } else {
                return module_name;
            }
        }

        if (add) {
            module_name.push_back(letter);
        }

    }
}

void link_files(string file_name, ofstream& target) {
    ifstream input (file_name);
    if (input.is_open()) {
        string line;
        while (getline(input, line)) {
            if (line.rfind(IMPORT) == 0) {
                link_files(get_relative_module_name(line), target);
                continue;
            }
            target << line << std::endl;
        }
        input.close();
    } else {
        std::cout << "Unable to open file " << file_name << endl;
    }
}

int main () {
    ofstream result ("result.cpp");
    if (result.is_open()) {
        link_files("example.cpp", result);
    } else {
        std::cout << "Unable to open file" << endl;
    }
    result.open ("result.cpp");
    result << "Writing this to a file.\n";
    result.close();
    return 0;
}