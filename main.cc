#include "main.h"
#define SRCLEN 500

void readPara(HMM &m)
{
    ifstream para;
    char file_name_para[100] = "";
    cout <<"para_file_name: ";
    cin >> file_name_para;
    para.open(file_name_para);
    
    int a, s;
    para >> a;
    char as[256];
    for (int i = 0; i < a; ++ i)
        para >> as[i];
    para >> s;
    m.setNumOfAlphsAndStates(a, s);
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

int fastaNext(ofstream &o, ifstream &f, char *s)
{
    char c = '>';
    do
        if (-1 == (c = f.get()))
            return 0;
    while ('\n' == c);
    if ('>' == c) {
        char l[FASTA_MAX_LINELEN + 1];
        f.getline(l, FASTA_MAX_LINELEN + 1);
        o << '>' << l << endl;
    } else
        f.seekg(-1, f.cur);
    int count = 0;
    do {
        c = f.get();
        if ('>' == c) {
            f.seekg(-1, f.cur);
            continue;
        }
        if (-1 == c || '\n' == c)
            continue;
        s[count] = c;
        count += f.gcount();
    }
    while ('>' != c && -1 != c);
    s[count] = '\0';
    return count;
}

int main(int argc, char *argv[])
{
    HMM hmm;
    readPara(hmm);

    ifstream fasta;
    ofstream result;

    char file_name_fasta[100] = "";
    cout << "fasta file name: ";
    cin >> file_name_fasta;

    fasta.open(file_name_fasta);
    result.open("result");
    char src[SRCLEN + 1] = "";
    int len;
    while (0 != (len = fastaNext(result, fasta, src))) {
        char res[len + 1];
        viterbi(hmm, src, res);
        result << res << endl;
        result << forward(hmm, src, len - 1) << endl;
        result << backward(hmm, src, 0) << endl;
        baum_welch(hmm, src, 1);
    }
    fasta.close();
    result.close();
    return 0;
}
