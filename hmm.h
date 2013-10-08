#ifndef __HMM_H_INCLUDED__
#define __HMM_H_INCLUDED__

const double inf = 1.0 / 0.0;

class HMM
{
private:
    int num_alphs;
    char *alphs;
    int num_states;
    double **trans_probs;
    double **output_probs;
    double **trans_probs_log;
    double **output_probs_log;
    void release(void);
    bool checkIndexState(int s) const;
    bool checkIndexAlph(int a) const;
public:
    HMM(void);
    ~HMM(void);
    int numOfAlphs(void) const;
    int numOfStates(void) const;
    void setNumOfAlphsAndStates(int a, int s);
    void setAlphs(char *s);
    void setTransProb(int s1, int s2, double p);
    void setOutputProb(int s, int a, double p);
    char alph(int n) const;
    double transProb(int f, int t) const;
    double outputProb(int s, char a) const;
    double transProbLog(int f, int t) const;
    double outputProbLog(int s, char a) const;
    void disp(void) const;
};

#endif
