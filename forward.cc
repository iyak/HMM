#include "hmmalgo.h"

double forward(const HMM &m, const char *s)
{
    const int len = strlen(s);

    double c1[m.numOfStates()];
    double c2[m.numOfStates()];
    for (int i = 0; i < m.numOfStates(); ++ i)
        c1[i] = -inf;
    c1[0] = 0;
    double *o = c1;
    double *n = c2;
    for (int i = 0; i < len; ++ i) {
        for (int j = 0; j < m.numOfStates(); ++ j) {
            n[j] = m.outputProbLog(j, s[i]);
            double sum = 0;
            for (int k = 0; k < m.numOfStates(); ++ k)
                sum += (pow(10, o[k]) * m.transProb(k, j));
            n[j] += log10(sum);
        }
        swap(o, n);
    }
    swap(o, n);

    /* termination */
    double sump = 0;
    for (int i = 0; i < m.numOfStates(); ++ i)
        sump += pow(10, n[i]);
    return sump;
}
