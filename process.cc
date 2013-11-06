#include "process.h"
#include "hmmalgo.h"
#include <fstream>
#include <cstdlib>
#include <vector>
#define SRCLEN 500
#define FASTA_MAX_LINELEN 80
#define BIVEC_LEN 50000

int fastaNext(ifstream &f, char *s, bool echo_comment)
{
    char c = '>';
    do
        if (-1 == (c = f.get()))
            return 0;
    while ('\n' == c);
    if ('>' == c) {
        char l[FASTA_MAX_LINELEN + 1];
        f.getline(l, FASTA_MAX_LINELEN + 1);
        if (echo_comment)
            cout << '>' << l << endl;
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

void set0(ifstream &f)
{
    f.clear();
    f.seekg(0, f.beg);
}

void processFasta(ifstream &f, HMM &m, ProgramOption &o)
{
    char src[SRCLEN + 1] = "";
    int len;

    /* hidden states and likelyhood of query with initial HMM */
    while (0 != (len = fastaNext(f, src, true))) {
        char res[len + 1];
        viterbi(m, src, res);
        cout << res << endl;
        cout << forward(m, src, len - 1) << endl;
    }
    set0(f);

    /* baum-welch algorithm */
    int bwCount = 10;
    for (; bwCount --; set0(f))
        while (0 != (len = fastaNext(f, src, false)))
            baum_welch_scaling(m, src);
    cout << endl << "baum-welch" << endl;

    /* hidden states and likelyhood of query with new HMM */
    while (0 != (len = fastaNext(f, src, true))) {
        char res[len + 1];
        viterbi(m, src, res);
        cout << res << endl;
        cout << forward(m, src, len - 1) << endl;
    }
}

void processBivec(ifstream &f, HMM &m, ProgramOption &o)
{
    vector< vector<bool> > q;
    for (int i = 0; f.good(); ++ i) {
        string b;
        f >> b;
        vector<string> line = split(b, ',');
        for (int i = 1; i < line.size(); ++ i) {
            
        }
        // string b;
        // unsigned char c = 0;
        // getline(f, b, ','); /* ignore first column */
        // for (int j = 0; j < m.numOfAlphs(); ++ j, c <<= 1) {
        //     if (j == m.numOfAlphs() - 1)
        //         getline(f, b, '\n');
        //     else
        //         getline(f, b, ',');
        //     int binary = atoi(b.c_str());
        //     if (0 != binary && 1 != binary) {
        //         cerr << "input binary vector contains invalid format" << endl;
        //         continue;
        //     }
        //     c += binary;
        // }
        // cout << q[i];
    }
}
