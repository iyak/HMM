#include "hmmalgo.h"

double backward(const HMM &m, const char *s)
{
    const int len = strlen(s);

    double c1[m.numOfStates()];
    double c2[m.numOfStates()];
    for (int i = 0; i < m.numOfStates(); ++ i)
        c1[i] = 1;
    double *o = c1;
    double *n = c2;
    for (int i = len - 1; 0 <= i; -- i) {
        for (int j = 0; j < m.numOfStates(); ++ j) {
            n[j] = 0;
            for (int k = 0; k < m.numOfStates(); ++ k)
                n[j] += m.outputProb(k, s[i]) * o[k] * m.transProb(j, k);
        }
        swap(o, n);
    }
    swap(o, n);

    /* termination */
    return n[0];
}

