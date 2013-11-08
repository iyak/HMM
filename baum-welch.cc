/*
 * compute likelyhood without neither logarithm enginearing
 * nore scaling. practical version is baum_welch_scaling.cc.
 */
#include "hmmalgo.h"

int baum_welch(HMM &m, const char *s)
{
    int len = strlen(s);

    double f[len + 1][m.numOfStates()];
    double b[len + 1][m.numOfStates()];

    /* fill forward dp */
    for (int i = 0; i < m.numOfStates(); ++ i)
        f[0][i] = 0;
    f[0][0] = 1;
    for (int i = 1; i <= len; ++ i) {
        for (int j = 0; j < m.numOfStates(); ++ j) {
            f[i][j] = 0;
            for (int k = 0; k < m.numOfStates(); ++ k)
                f[i][j] += f[i - 1][k] * m.transProb(k, j) * m.outputProb(j, s[i - 1]);
        }
    }

    /* fill backward dp */
    for (int i = 0; i < m.numOfStates(); ++ i)
        b[len][i] = 1;
    b[len][0] = 0;
    for (int i = len - 1; 0 <= i; -- i) {
        int j = 0 == i ? 0 : 1;
        for (; j < m.numOfStates(); ++ j) {
            b[i][j] = 0;
            for (int k = 0; k < m.numOfStates(); ++ k)
                b[i][j] += b[i + 1][k] * m.transProb(j, k) * m.outputProb(k, s[i]);
        }
    }

    /* xi value -- prob of transition at time */
    double x[len][m.numOfStates()][m.numOfStates()];
    for (int i = 0; i < len; ++ i) {
        double p = 0;
        for (int j = 0; j < m.numOfStates(); ++ j)
            for (int k = 0; k < m.numOfStates(); ++ k)
                p += f[i][j] * m.transProb(j, k) * b[i + 1][k] * m.outputProb(k, s[i]);
        for (int j = 0; j < m.numOfStates(); ++ j)
            for (int k = 0; k < m.numOfStates(); ++ k)
                x[i][j][k] = f[i][j] * m.transProb(j, k) * b[i + 1][k] * m.outputProb(k, s[i]) / p;
    }

    /* gamma value -- prob of state at time */
    double g[len + 1][m.numOfStates()];
    for (int i = 0; i <= len; ++ i) {
        double p = 0;
        for (int j = 0; j < m.numOfStates(); ++ j)
            p += f[i][j] * b[i][j];
        for (int j = 0; j < m.numOfStates(); ++ j)
            g[i][j] = f[i][j] * b[i][j] / p;
    }

    /* update */
    for (int i = 0; i < m.numOfStates(); ++ i) {
        double s_g = 0;
        for (int j = 0; j < len; ++ j)
            s_g += g[j][i];
        for (int j = 0; j < m.numOfStates(); ++ j) {
            double s_x = 0;
            for (int k = 0; k < len; ++ k)
                s_x += x[k][i][j];
            m.setTransProb(i, j, s_x / s_g);
        }
        s_g += g[len][i];
        double s_g2[m.numOfAlphs()];
        for (int j = 0; j < m.numOfAlphs(); ++ j)
            s_g2[j] = 0;
        for (int j = 1; j <= len; ++ j) {
            for (int k = 0; k < m.numOfAlphs(); ++ k) {
                if (s[j - 1] == m.alph(k)) {
                    s_g2[k] += g[j][i];
                    break;
                }
            }
        }
        for (int j = 0; j < m.numOfAlphs(); ++ j)
            m.setOutputProb(i, j, s_g2[j] / s_g);
    }

    return 1;
}
