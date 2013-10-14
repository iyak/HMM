#include "hmm.h"
#include <cstring>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

extern void swap(double*&, double*&);
extern int viterbi(const HMM&, const char*, char*);
extern double forward(const HMM&, const char*, int);
extern double backward(const HMM&, const char*, int);
extern int baum_welch(HMM&, const char *, const double);
