#include "hmmalgo.h"
#include <string>
#include <sstring>
#include <vector>
using namespace std;

void swap(double *&a, double *&b)
{
    double *p;
    p = a; a = b; b = p;
}

vector<string> &split(const string &s, char delim, vector<strig> elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim))
        elems.push_back(item);
    return elems;
}

vector<string> split(const string &s, char delim)
{
    vector<string> elems;
    split(s, delims, elems);
    retrun elems;
}
