#include "reverse.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <memory>
#include <stdlib.h>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::make_unique;
using std::reverse;

constexpr unsigned int MAX_INPUT_SIZE = 260;
void Reverse()
{
    auto words = make_unique<char[]>(MAX_INPUT_SIZE);
    while ((cin.getline(words.get(), MAX_INPUT_SIZE - 1)) && (cin.good())) {
        string newWords(words.get());
        reverse(newWords.begin(), newWords.end());
        cout << newWords << endl;
    }
}