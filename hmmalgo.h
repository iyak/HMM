#include "hmm.h"
#include <cstring>
#include <cmath>
#include <cstdio>

extern void swap(double*&, double*&);
extern int viterbi(const HMM&, const char*, char*);
extern double forward(const HMM&, const char*);
extern double backward(const HMM&, const char*);
