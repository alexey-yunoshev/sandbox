#include <iostream>
#include <set>
#include <string>
#include <functional>

using namespace std;

int min(int a, int b) {
    return a < b ? a : b;
}

string join(std::vector<string> const &v) {
    string result;
    for (const auto &el: v) {
        result.append(el);
    }

    return result;
}

string reverse_string(const string &str) {
    int length = str.length();

    string result;
    for (int i = length - 1; i > -1; i--) {
        result.append(std::string(1, str.at(i)));
    }

    return result;
}

template<typename T>
void print_vector(std::vector<T> const &v) {
    for (const auto &i: v) {
        cout << i << ' ';
    }
    std::cout << '\n';
}

/**
 *
 * @see range constructor at http://www.cplusplus.com/reference/vector/vector/vector/
 */
template<typename T>
std::vector<T> slice(std::vector<T> const &sourceVector, int start, int end) {
    auto first = sourceVector.cbegin() + start;
    auto last = sourceVector.cbegin() + end;
    std::vector<T> vectorSlice(first, last);
    return vectorSlice;
}

int main() {
    set<string> dictionary = {"hi", "hey", "her", "my", "ok", "he", "me", "orm", "no"};
    vector<vector<string>> puzzle;

    puzzle.push_back({"h", "e", "y", "o"});
    puzzle.push_back({"m", "e", "k", "m"});
    puzzle.push_back({"i", "h", "r", "n"});
    puzzle.push_back({"i", "o", "o", "i"});


    set<string> found_words;

    int height = puzzle.size();
    int width = puzzle.front().size();
    int minSide = min(height, width);

    for (int rowIndex = 0; rowIndex < height; rowIndex++) {
        for (int columnIndex = 0; columnIndex < width - 1; columnIndex++) {
            for (int columnEndIndex = columnIndex + 2; columnEndIndex < width + 1; columnEndIndex++) {
                string word = join(slice(puzzle[rowIndex], columnIndex, columnEndIndex));
                if (dictionary.count(word) > 0) {
                    found_words.insert(word);
                }
                string reversed_word = reverse_string(word);
                if (dictionary.count(reversed_word) > 0) {
                    found_words.insert(reversed_word);
                }
            }
        }
    }

    for (int columnIndex = 0; columnIndex < width; columnIndex++) {
        for (int rowIndex = 0; rowIndex < width - 1; rowIndex++) {
            for (int rowEndIndex = rowIndex + 2; rowEndIndex < width + 1; rowEndIndex++) {
                vector<string> word_letters;

                for (int i = rowIndex; i < rowEndIndex; i++) {
                    word_letters.push_back(puzzle[rowIndex][columnIndex]);
                }

                string word = join(word_letters);
                if (dictionary.count(word) > 0) {
                    found_words.insert(word);
                }
                string reversed_word = reverse_string(word);
                if (dictionary.count(reversed_word) > 0) {
                    found_words.insert(reversed_word);
                }
            }
        }
    }

    for (int row_index = 0; row_index < height - 1; row_index++) {
        for (int column_index = 0; column_index < width - 1; column_index++) {
            int remaining_slots_count = min(width - column_index, height - row_index);
            int end_index = remaining_slots_count < minSide ? remaining_slots_count: minSide;
            int row_index_end = row_index;

            for (int column_index_end = column_index + 1; column_index_end < column_index + end_index; column_index_end++) {
                row_index_end++;
                int column_i = column_index;
                vector<string> word_letters;

                for (int row_i = row_index; row_i < row_index_end + 1; row_i++) {
                    word_letters.push_back(puzzle[row_i][column_i]);
                    column_i++;
                }

                string word = join(word_letters);
                if (dictionary.count(word) > 0) {
                    found_words.insert(word);
                }
                string reversed_word = reverse_string(word);
                if (dictionary.count(reversed_word) > 0) {
                    found_words.insert(reversed_word);
                }
            }
        }
    }

    for (int row_index = 1; row_index < height; row_index++) {
        for (int column_index = 0; column_index < width - 1; column_index++) {
            int remaining_slots_count = min(width - column_index, row_index + 1);
            int end_index = remaining_slots_count < minSide ? remaining_slots_count: minSide;
            int row_index_end = row_index;

            for (int column_index_end = column_index + 1; column_index_end < column_index + end_index; column_index_end++) {
                row_index_end--;
                int column_i = column_index;
                vector<string> word_letters;

                for (int row_i = row_index; row_i > row_index_end - 1; row_i--) {
                    word_letters.push_back(puzzle[row_i][column_i]);
                    column_i++;
                }

                string word = join(word_letters);
                if (dictionary.count(word) > 0) {
                    found_words.insert(word);
                }
                string reversed_word = reverse_string(word);
                if (dictionary.count(reversed_word) > 0) {
                    found_words.insert(reversed_word);
                }
            }
        }
    }

    for (const auto &word: found_words) {
        cout << word << endl;
    }

    return 0;
}
