#ifndef PIDPARSER_H
#define PIDPARSER_H
using namespace std;
#include "AlogParser.h"

class PIDParser:public AlogParser
{
    public:
        PIDParser();
        PIDParser(int );
        virtual ~PIDParser();
        string parserLine(string line);
        bool isMatch(string);
    protected:
    private:
        int mPID;
};

#endif // PIDPARSER_H
