#ifndef TIDPARSER_H
#define TIDPARSER_H
#include "AlogParser.h"
using namespace std;

class TIDParser:public AlogParser
{
    public:
        TIDParser();
        TIDParser(int);
        virtual ~TIDParser();
        string parserLine(string line);

    protected:
    private:
        int mTID;

};

#endif // TIDPARSER_H
