#ifndef __PO_H_INCLUDED__
#define __PO_H_INCLUDED__

#define STRMAX 50

enum inputType_t {NONE, FASTA, BIVEC};

class ProgramOption
{
public:
    inputType_t inputType;
    char *inputFileName;
    char *paraFileName;
    ProgramOption(void);
    ~ProgramOption(void);
    void disp(void);
};

#endif
