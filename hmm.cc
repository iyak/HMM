#include <iostream>
#include <iomanip>
#include <cmath>
#include "hmm.h" 
using namespace std;

HMM::HMM(void)
{
    num_alphs = 0;
    num_states = 0;
    alphs = NULL;
    trans_probs = NULL;
    output_probs = NULL;
    trans_probs_log = NULL;
    output_probs_log = NULL;
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
    if (NULL != trans_probs_log)
        for (int i = 0; i < num_states; ++ i)
            delete [] trans_probs_log[i];
    delete [] trans_probs_log;
    if (NULL != output_probs_log)
        for (int i = 0; i < num_states; ++ i)
            delete [] output_probs_log[i];
    delete [] output_probs_log;
    alphs = NULL;
    trans_probs = NULL;
    output_probs = NULL;
    trans_probs_log = NULL;
    output_probs_log = NULL;
}

bool HMM::checkIndexState(int s)
{
    if (s < 0 || num_states <= s) {
        cout << "HMM: index of state is invalid: " << s << endl;
        return false;
    }
    return true;
}

bool HMM::checkIndexAlph(int a)
{
    if (a < 0 || num_alphs <= a) {
        cout << "HMM: index of alph is invalid: " << a << endl;
        return false;
    }
    return true;
}

HMM::~HMM(void)
{
    release();
}

void HMM::setNumOfAlphsAndStates(int a, int s)
{
    release();
    
    if (a < 0 || s < 0) {
        cout << "setNumOfAlphsAndStates: num must non-negative" << endl;
        return;
    }
    num_alphs = a;
    num_states = s;
    alphs = new char[a]();
    trans_probs = new float *[s];
    for (int i = 0; i < s; ++ i)
        trans_probs[i] = new float [s]();
    output_probs = new float *[s];
    for (int i = 0; i < s; ++ i)
        output_probs[i] = new float [a]();
    trans_probs_log = new float *[s];
    for (int i = 0; i < s; ++ i)
        trans_probs_log[i] = new float [s]();
    output_probs_log = new float *[s];
    for (int i = 0; i < s; ++ i) {
        output_probs_log[i] = new float [a]();
        if (0 == i)
            for (int j = 0; j < a; ++ j)
                output_probs_log[i][j] = -inf;
    }
}

void HMM::setAlphs(char *s)
{
    for (int i = 0; i < num_alphs; ++ i)
        alphs[i] = s[i];
}
void HMM::setTransProb(int s1, int s2, float p)
{
    if (!checkIndexState(s1) || !checkIndexState(s2))
        return;
    trans_probs[s1][s2] = p;
    trans_probs_log[s1][s2] = log10(p);
}

void HMM::setOutputProb(int s, int a, float p)
{
    if (!checkIndexState(s) || !checkIndexAlph(a))
        return;
    output_probs[s][a] = p;
    output_probs_log[s][a] = log10(p);
}

int HMM::numOfAlphs(void)
{
    return num_alphs;
}

int HMM::numOfStates(void)
{
    return num_states;
}

inline char HMM::alph(int n)
{
    if (!checkIndexAlph(n))
        return '\0';
    return alphs[n];
}

inline float HMM::transProb(int f, int t)
{
    if (!checkIndexState(f) || !checkIndexState(t))
        return -1;
    return trans_probs[f][t];
}

inline float HMM::outputProb(int s, char a)
{
    if (!checkIndexState(s))
        return -1;
    int i;
    for (i = 0; i < num_alphs; ++ i)
        if (a == alphs[i])
            break;
    if (num_alphs == i)
        return 0;
    return output_probs[s][i];
}

float HMM::transProbLog(int f, int t)
{
    if (!checkIndexState(f) || !checkIndexState(t))
        return -1;
    return trans_probs_log[f][t];
}

float HMM::outputProbLog(int s, char a)
{
    if (!checkIndexState(s))
        return -1;
    int i;
    for (i = 0; i < num_alphs; ++ i)
        if (a == alphs[i])
            break;
    if (num_alphs == i)
        return 0;
    return output_probs_log[s][i];
}

void HMM::disp(void)
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
    cout << "trans probs log:" << endl;
    for (int i = 0; i < num_states; ++ i) {
        for (int j = 0; j < num_states; ++ j)
            cout << fixed << setprecision(3) << trans_probs_log[i][j] << "\t";
        cout << endl;
    }
    cout << "output probs log:" << endl;
    for (int i = 0; i < num_states; ++ i) {
        for (int j = 0; j < num_alphs; ++ j)
            cout << fixed << setprecision(3) << output_probs_log[i][j] << "\t";
        cout << endl;
    }
}