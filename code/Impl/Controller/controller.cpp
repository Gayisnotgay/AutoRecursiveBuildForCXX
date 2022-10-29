#include "controller.h"
#include <iostream>
#include <limits>
#include <functional>
#include <vector>
#include "repeat.h"
#include "reverse.h"
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::function;
using std::vector;
using std::numeric_limits;
using std::make_unique;

static void PrintFunctionHint()
{
    cout << "Pls choose my function: " << endl;
    cout << "[0]. Repeat." << endl;
    cout << "[1]. Reverse." << endl;
    cout << "[2]. Quit." << endl;
    cout << "Pls type in your selected option number:" << endl;
}

static vector<function<void()>>& RetriveControllerFunctionList()
{
    static vector<function<void()>> functionList = {
        []() { Repeat();},  
        []() { Reverse();}, 
        []() { exit(0);}, 
    };

    return functionList;
}

void Controller()
{
    constexpr auto max_size = numeric_limits<std::streamsize>::max();
    PrintFunctionHint();

    int selection = -1;
    while (cin.good()) {
        cin >> selection;
        if ((!cin.good()) || (selection >= RetriveControllerFunctionList().size())) {
            cout << "Error: Option number " << selection << " is not valid." << endl;
        } else {
            RetriveControllerFunctionList()[selection]();
        }
        
        cin.clear();
        clearerr(stdin);
        cin.ignore(max_size, '\n');
        
        PrintFunctionHint();
    }
}