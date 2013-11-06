#ifndef __HMM_H_INCLUDED__
#define __HMM_H_INCLUDED__

const double inf = 1.0 / 0.0;

template<class T>
class HMM
{
private:
    int num_alphs;
    vector<T> alphs;
    int num_states;
    int num_dim;
    vector< vector<double> > trans_probs;
    vector< vector< vector<double> > > output_probs;
    bool checkIndexState(int s) const;
    bool checkIndexAlph(int a) const;
    bool checkProb(double p) const;
    int checkAlph(char c) const;
public:
    HMM(void);
    ~HMM(void);
    int numOfAlphs(void) const;
    int numOfStates(void) const;
    void setNumOfAlphs(int a);
    void setNumOfStates(int s);
    void setNumOfDim(int d);
    void setAlphs(vector<T> s);
    void setTransProb(int s1, int s2, double p);
    void setOutputProb(int s, int a, double p);
    T alph(int n) const;
    double transProb(int f, int t) const;
    double outputProb(int s, T a) const;
    void disp(void) const;
};

#endif
