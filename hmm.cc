#include <iostream>
#include <iomanip>
#include <cmath>
#include <cfloat>
#include "hmm.h" 
using namespace std;

HMM::HMM(void)
{
    num_alphs = 0;
    num_states = 0;
    alphs = NULL;
    trans_probs = NULL;
    output_probs = NULL;
}

inline void HMM::release(void)
{
    delete [] alphs;
    if (NULL != trans_probs)
        for (int i = 0; i < num_states; ++ i)
            delete [] trans_probs[i];
    delete [] trans_probs;
    if (NULL != output_probs)
        for (int i = 0; i < num_states; ++ i)
            delete [] output_probs[i];
    delete [] output_probs;
    alphs = NULL;
    trans_probs = NULL;
    output_probs = NULL;
}

bool HMM::checkIndexState(int s) const
{
    if (s < 0 || num_states <= s) {
        cerr << "HMM: index of state is invalid: " << s << endl;
        return false;
    }
    return true;
}

bool HMM::checkIndexAlph(int a) const
{
    if (a < 0 || num_alphs <= a) {
        cerr << "HMM: index of alph is invalid: " << a << endl;
        return false;
    }
    return true;
}

bool HMM::checkProb(double p) const
{
    if (p < 0 - 2 * DBL_EPSILON || 1 + 2 * DBL_EPSILON < p) {
        cerr << "HMM: probability out of range: " << p << endl;
        return false;
    }
    return true;
}

int HMM::checkAlph(char c) const
{
    for (int i = 0; i < num_alphs; ++ i)
        if (alphs[i] == c)
            return i;
    cerr << "HMM: invalid alphabet: " << c << endl;
    return -1;
}

HMM::~HMM(void)
{
    release();
    alphs = NULL;
    trans_probs = NULL;
    output_probs = NULL;
}

void HMM::setNumOfAlphsAndStates(int a, int s)
{
    release();
    
    if (a < 0 || s < 0) {
        cerr << "setNumOfAlphsAndStates: num must non-negative" << endl;
        return;
    }
    num_alphs = a;
    num_states = s;
    alphs = new char[a]();
    trans_probs = new double *[s];
    for (int i = 0; i < s; ++ i)
        trans_probs[i] = new double [s]();
    output_probs = new double *[s];
    for (int i = 0; i < s; ++ i)
        output_probs[i] = new double [a]();
}

void HMM::setAlphs(char *s)
{
    for (int i = 0; i < num_alphs; ++ i)
        alphs[i] = s[i];
}
void HMM::setTransProb(int s1, int s2, double p)
{
    if (!checkIndexState(s1) || !checkIndexState(s2) || !checkProb(p))
        return;
    trans_probs[s1][s2] = p;
}

void HMM::setOutputProb(int s, int a, double p)
{
    if (!checkIndexState(s) || !checkIndexAlph(a) || !checkProb(p))
        return;
    output_probs[s][a] = p;
}

int HMM::numOfAlphs(void) const
{
    return num_alphs;
}

int HMM::numOfStates(void) const 
{
    return num_states;
}

char HMM::alph(int n) const
{
    if (!checkIndexAlph(n))
        return '\0';
    return alphs[n];
}

double HMM::transProb(int f, int t) const
{
    if (!checkIndexState(f) || !checkIndexState(t))
        return -1;
    return trans_probs[f][t];
}

double HMM::outputProb(int s, char a) const
{
    if (!checkIndexState(s))
        return -1;
    int i;
    if (-1 == (i = checkAlph(a)))
        return -1;
    return output_probs[s][i];
}

void HMM::disp(void) const
{
    cout << "alphabets:";
    for (int i = 0; i < num_alphs; ++ i)
        cout << alphs[i] << " ";
    cout << endl << "trans probs:" << endl;
    for (int i = 0; i < num_states; ++ i) {
        for (int j = 0; j < num_states; ++ j)
            cout << fixed << setprecision(3) << trans_probs[i][j] << "\t";
        cout << endl;
    }
    cout << "output probs:" << endl;
    for (int i = 0; i < num_states; ++ i) {
        for (int j = 0; j < num_alphs; ++ j)
            cout << fixed << setprecision(3) << output_probs[i][j] << "\t";
        cout << endl;
    }
}
