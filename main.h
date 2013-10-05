#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <climits>
#include "hmm.h"
using namespace std;

#define FASTA_MAX_LINELEN 80

typedef struct __viterbi_cell
{
    float prob;
    int prev;
} vc_t;
