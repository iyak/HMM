#include "program_option.h"
#include <iostream>
#include <cstdlib>
using namespace std;

ProgramOption::ProgramOption(void)
{
    inputType = NONE;
    inputFileName = new char[STRMAX + 1];
    paraFileName = new char[STRMAX + 1];
}

ProgramOption::~ProgramOption(void)
{
    delete [] inputFileName;
    delete [] paraFileName;
}

void ProgramOption::disp(void)
{
    cout << "input type: " << inputType << endl;
    cout << "input file name: " << inputFileName << endl;
    cout << "para file name: " << paraFileName << endl;
}
