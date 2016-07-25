#ifndef ALOGPARSER_H
#define ALOGPARSER_H

#include <string>
#include "TypeDef.h"

class TagParser;
using namespace std;

class AlogParser
{
    public:
        AlogParser();
        virtual ~AlogParser();
        virtual string parserLine(string line)=0;

    protected:

    private:
};

#endif // ALOGPARSER_H
