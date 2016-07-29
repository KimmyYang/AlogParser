#ifndef ALOGPARSER_H
#define ALOGPARSER_H

#include <string>
#include "TypeDef.h"

class TagParser;
using namespace std;

//interface
class AlogParser
{
    public:
        AlogParser();
        virtual ~AlogParser();
        virtual string parserLine(string)=0;
        virtual bool isMatch(string)=0;
    protected:
    private:
};

#endif // ALOGPARSER_H
