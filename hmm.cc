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

bool HMM::checkDim(int d) const
{
    if (d < 1 || num_dim <= d) {
        cerr << "HMM: dim is invalid: " << d << endl;
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

int HMM::checkAlph(T c) const
{
    for (int i = 0; i < num_alphs; ++ i)
        if (alphs[i] == c)
            return i;
    cerr << "HMM: invalid alphabet: " << c << endl;
    return -1;
}

HMM::~HMM(void)
{
    alphs = NULL;
    trans_probs = NULL;
    output_probs = NULL;
}

void HMM::setNumOfAll(int a, int s, int d)
{
    num_alphs = a;
    num_states = s;
    num_dim = d;

    alphs.resize(a);
    trans_probs.resize(s);
    for (auto i : trans_probs)
        i.resize(s);
    output_probs.resize(s);
    for (auto i : output_probs) {
        i.resize(d);
        for (auto j : i)
            j.resize(a);
    }
}

void HMM::setNumOfAlphs(int a)
{
    if (a < 0) {
        cerr << "setNumOfAlphs: num of alphs must non-negative: " << a << endl;
        return;
    }
    num_alphs = a;
    alphs.resize(a);
    output_probs.resize(num_states);
    for (auto i : output_probs) {
        i.resize(num_dims);
        for (auto j : i)
            j.resize(a);
    }
}

void HMM::setNumOfStates(int s)
{
    if (s < 0) {
        cerr << "setNumOfStates: num of states must non-negative: " << s << endl;
        return;
    }
    num_states = s;
    trans_probs.resize(s);
    for (auto i : trans_probs)
        i.resize(s);
    output_probs.resize(s);
    for (auto i : output_probs) {
        i.resize(num_dims);
        for (auto j : i)
            j.resize(a);
    }
}

void HMM::setNumOfDim(int d)
{
    if (d < 1) {
        cerr << "setNumOfDims: num of dim must positive: " << d << endl;
        return;
    }
    num_dim = d;
    output_probs.resize(num_states);
    for (auto i : output_probs) {
        i.resize(d);
        for (auto j : i)
            j.resize(num_alphs);
    }
}

void HMM::setAlphs(vector<T> *s)
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

void HMM::setOutputProb(int s, int d, int a, double p)
{
    if (!checkIndexState(s) || !checkIndexAlph(a) ||!checkDim(d) || !checkProb(p))
        return;
    output_probs[s][d][a] = p;
}

int HMM::numOfAlphs(void) const
{
    return num_alphs;
}

int HMM::numOfStates(void) const 
{
    return num_states;
}

T HMM::alph(int n) const
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

double HMM::outputProb(int s, int d, T a) const
{
    if (!checkIndexState(s) || !checkDim(d))
        return -1;
    int i;
    if (-1 == (i = checkAlph(a)))
        return -1;
    return output_probs[s][d][i];
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
    // cout << "output probs:" << endl;
    // for (int i = 0; i < num_states; ++ i) {
    //     for (int j = 0; j < num_alphs; ++ j)
    //         cout << fixed << setprecision(3) << output_probs[i][j] << "\t";
    //     cout << endl;
    // }
}
