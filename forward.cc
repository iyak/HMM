#include "hmmalgo.h"

double forward(const HMM &m, const char *s, const int t)
{
    const int len = strlen(s);
    if (len < t)
        return -inf;

    double c1[m.numOfStates()];
    double c2[m.numOfStates()];
    for (int i = 0; i < m.numOfStates(); ++ i)
        c1[i] = 0;
    c1[0] = 1;
    double *o = c1;
    double *n = c2;
    for (int i = 0; i <= t; ++ i) {
        for (int j = 0; j < m.numOfStates(); ++ j) {
            n[j] = m.outputProb(j, s[i]);
            double sum = 0;
            for (int k = 0; k < m.numOfStates(); ++ k)
                sum += o[k] * m.transProb(k, j);
            n[j] *= sum;
        }
        swap(o, n);
    }
    swap(o, n);

    /* termination */
    double sump = 0;
    for (int i = 0; i < m.numOfStates(); ++ i)
        sump += n[i];
    return sump;
}
