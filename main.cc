#include "main.h"

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
    float p;
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

void readFasta(ifstream &f)
{
    char file_name_fasta[100] = "";
    cout << "fasta file name: ";
    cin >> file_name_fasta;
    f.open(file_name_fasta);
}

int getQueryLen(ifstream &f)
{
    int retval = 0;
    while (!f.eof())
        if ('\n' != f.get())
            ++ retval;
    -- retval;
    f.seekg(0, f.beg);
    f.clear();
    return retval;
}

void viterbi(HMM &m, ifstream &f)
{
    int len = getQueryLen(f);

    /* create dp table */
    vc_t **v;
    v = new vc_t *[m.numOfStates()];
    for (int i = 0; i < m.numOfStates(); ++ i)
        v[i] = new vc_t[len + 1];

    /* initialize dp table */
    for (int i = 0; i < m.numOfStates(); ++ i)
        v[i][0].prev = -1;
    v[0][0].prob = 0;
    for (int i = 1; i < m.numOfStates(); ++ i)
        v[i][0].prob = -inf;

    /* fill in dp table */
    f.seekg(0, f.beg);
    f.clear();
    int cur = 1;
    while (!f.eof()) {
        char q[FASTA_MAX_LINELEN + 1] = "";
        f >> q;
        cout << q;
        for (int i = 0; '\0' != q[i]; ++ i, ++ cur) {
            for (int j = 0; j < m.numOfStates(); ++ j) {
                v[j][cur].prob = -inf;
                for (int k = 0; k < m.numOfStates(); ++ k) {
                    float new_prob = v[k][cur - 1].prob + m.transProbLog(k, j) + m.outputProbLog(j, q[i]);
                    if (v[j][cur].prob < new_prob) {
                        v[j][cur].prob = new_prob;
                        v[j][cur].prev = k;
                    }
                }
            }
        }
    }

    /* display viterbi dp table */
    cout << endl;
    for (int i = 0; i < m.numOfStates(); ++ i) {
        for (int j = 0; j < 20; ++ j)
            cout << fixed << setprecision(3) << v[i][j].prob << "\t";
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < m.numOfStates(); ++ i) {
        for (int j = 0; j < 20; ++ j)
            cout << v[i][j].prev << "\t";
        cout << endl;
    }

    /* termination */
    cout << cur << endl;
    int tb_index = 0;
    int tb_count = len;
    float max_prob = v[tb_index][tb_count].prob;
    for (int i = 1; i < m.numOfStates(); ++ i) {
        if (max_prob < v[i][tb_count].prob) {
            max_prob = v[i][tb_count].prob;
            tb_index = i;
        }
    }

    /* trace back */
    ofstream r("result");
    r.flush();
    for (; 0 <= tb_count; -- tb_count) {
        r.seekp(tb_count, r.beg);
        r << tb_index;
        tb_index = v[tb_index][tb_count].prev;
    }
    r.close();

    cout << endl;
    f.close();
    for (int i = 0; i < m.numOfStates(); ++ i) {
        delete [] v[i];
    }
    delete [] v;
}

int main(int argc, char *argv[])
{
    HMM hmm;
    readPara(hmm);
    ifstream fasta;
    readFasta(fasta);
    viterbi(hmm, fasta);
    hmm.disp();
    return 0;
}
