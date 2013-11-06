#include <iostream>
#include "hmm.h"
#include "program_option.h"
using namespace std;

extern void processFasta(ifstream&, HMM&, ProgramOption&);
extern void processBivec(ifstream&, HMM&, ProgramOption&);
