#include "main.h"
#include <cstdlib>
#include <cstring>
#include <vector>

void readPara(HMM &m, ProgramOption &po)
{
    ifstream para;
    para.open(po.paraFileName);
    
    int a, s;
    para >> a;
    vector<char> as;
    for (int i = 0; i < a; ++ i) {
        char c;
        para >> c;
        as.push_back(c);
    }
    para >> s;
    m.setNumOfAlphs(a);
    m.setNumOfStates(s);
    m.setNumOfDim(1);
    m.setAlphs(as);
    double p;
    for (int i = 0; i < s; ++ i) {
        for (int j = 0; j < s; ++ j) {
            para >> p;
            m.setTransProb(i, j, p);
        }
    }
    for (int i = 1; i < s; ++ i) {
        for (int j = 0; j < a; ++ j) {
            para >> p;
            m.setOutputProb(i, j, p);
        }
    }
    para.close();
}

void parseEqu(const char *s, char *l, char *r)
{
    int c = 0, i = 0;
    for (i = 0; '=' != s[c]; ++ c, ++ i)
        l[i] = s[c];
    l[i] = '\0';
    ++ c;
    for (i = 0; '\0' != s[c]; ++ c, ++ i)
        r[i] = s[c];
    r[i] = '\0';
}

void setOption(ProgramOption &po, const int argc, char *argv[])
{
    for (int i = 1; i < argc; ++ i) {
        cout << argv[i] << endl;
        if ('-' == argv[i][0] && '-' == argv[i][1]) ;
        else {
            cerr << "bad usage!" << endl;
            continue;
        }
        char left[STRMAX], right[STRMAX];
        parseEqu(argv[i] + 2, left, right);
        if (0 == strcmp("fasta", left)) {
            if (NONE != po.inputType) {
                cerr << "file type is ambiguous" << endl;
                continue;
            }
            po.inputType = FASTA;
            strcpy(po.inputFileName, right);
            continue;
        }
        if (0 == strcmp("bivec", left)) {
            if (NONE != po.inputType) {
                cerr << "file type is ambiguous" << endl;
                continue;
            }
            po.inputType = BIVEC;
            strcpy(po.inputFileName, right);
            continue;
        }
        if (0 == strcmp("para", left)) {
            strcpy(po.paraFileName, right);
            continue;
        }
    }
}

int main(int argc, char *argv[])
{
    ProgramOption po;
    setOption(po, argc, argv);

    ifstream input;
    input.open(po.inputFileName);

    switch (po.inputType) {
        case NONE:
            cerr << "set input type" << endl;
            exit(EXIT_FAILURE);
        case FASTA:
            HMM<char> hmm;
            readPara(hmm, po);
            processFasta(input, hmm, po);
            break;
        case BIVEC:
            HMM<bool> hmm;
            processBivec(input, hmm, po);
            break;
    }

    input.close();
    return 0;
}
