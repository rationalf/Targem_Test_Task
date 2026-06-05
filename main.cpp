#include "String.h"
#include <iostream>
#include <cctype>
#include <cstdlib>

static int icompare(const char* left, const char* right) {
    for (;;) {
        int left_char  = tolower(static_cast<unsigned char>(*left));
        int right_char = tolower(static_cast<unsigned char>(*right));
        if (left_char != right_char) return left_char - right_char;
        if (left_char == '\0') return 0;
        ++left; ++right;
    }
}

static void sort_strings(String* strings, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (icompare(strings[j].c_str(), strings[j + 1].c_str()) < 0) {
                String temp = strings[j];
                strings[j] = strings[j + 1];
                strings[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <string1> [string2] ..." << std::endl;
        return 1;
    }

    int count = argc - 1;
    String* strings = new String[count];
    
    for (int i = 0; i < count; ++i)
        strings[i] = String(argv[i + 1]);

    sort_strings(strings, count);

    for (int i = 0; i < count; ++i)
        std::cout << strings[i].c_str() << '\n';

    delete[] strings;
    return 0;
}
