#ifndef CONTENTPARSER_H
#define CONTENTPARSER_H
#include "AlogParser.h"
#include "TypeDef.h"
using namespace std;


class ContentParser:public AlogParser
{
    public:
        ContentParser(string);
        virtual ~ContentParser();
        string parserLine(string line);
        bool isMatch(string);
    protected:
    private:
        void createContentMap(string filePath);

        ContentVector* mContentVector;
};

#endif // CONTENTPARSER_H
