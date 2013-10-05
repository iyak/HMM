#ifndef __HMM_H_INCLUDED__
#define __HMM_H_INCLUDED__

const float inf = 1.0 / 0.0;

class HMM
{
private:
    int num_alphs;
    char *alphs;
    int num_states;
    float **trans_probs;
    float **output_probs;
    float **trans_probs_log;
    float **output_probs_log;
    void release(void);
    bool checkIndexState(int s);
    bool checkIndexAlph(int a);
public:
    HMM(void);
    ~HMM(void);
    int numOfAlphs(void);
    int numOfStates(void);
    void setNumOfAlphsAndStates(int a, int s);
    void setAlphs(char *s);
    void setTransProb(int s1, int s2, float p);
    void setOutputProb(int s, int a, float p);
    char alph(int n);
    float transProb(int f, int t);
    float outputProb(int s, char a);
    float transProbLog(int f, int t);
    float outputProbLog(int s, char a);
    void disp(void);
};

#endif
