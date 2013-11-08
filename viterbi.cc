/*
 * estimate most likely hidden state sequence with viterbi algorithm.
 * this is implemented without neither logarithm enginearing
 * nore scaling. practical version is not implemented yet.
 */
#include "hmmalgo.h"

int viterbi(const HMM &m, const char *s, char *r)
{
    const int len = strlen(s);

    /* initialize dp table */
    int v[len][m.numOfStates()];
    double c1[m.numOfStates()];
    double c2[m.numOfStates()];
    for (int i = 0; i < m.numOfStates(); ++ i)
        c1[i] = 0;
    c1[0] = 1;
    for (int j = 0; j < len; ++ j)
        for (int i = 0; i < m.numOfStates(); ++ i)
            v[j][i] = -1;

    /* fill in dp table */
    double *o = c1;
    double *n = c2;
    for (int i = 0; i < len; ++ i) {
        for (int j = 0; j < m.numOfStates(); ++ j) {
            n[j] = -inf;
            for (int k = 0; k < m.numOfStates(); ++ k) {
                double p = o[k] * m.transProb(k, j) * m.outputProb(j, s[i]);
                if (n[j] < p) {
                    n[j] = p;
                    v[i][j] = k;
                }
            }
        }
        swap(o, n);
    }
    swap(o, n);

    /* termination */
    int maxi = 0;
    double maxp = -inf;
    for (int i = 0; i < m.numOfStates(); ++ i) {
        if (maxp < n[i]) {
            maxi = i;
            maxp = n[i];
        }
    }

    /* trace back */
    for (int i = len - 1, j = maxi; i >= 0; -- i) {
        r[i + 1] = '0' + j;
        j = v[i][j];
    }
    r[0] = '0';
    r[len] = '\0';

    return len;
}
