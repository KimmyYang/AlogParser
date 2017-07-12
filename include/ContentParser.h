#ifndef CONTENTPARSER_H
#define CONTENTPARSER_H
#include "AlogParser.h"
#include "TypeDef.h"
using namespace std;


class ContentParser:public AlogParser
{
    public:
        ContentParser(string,string);
        virtual ~ContentParser();
        string parserLine(string line);
        bool isMatch(string);
    protected:
    private:
        void createContentMap(string,string);
        void loadProfile(string);
        bool isPartialMatch(const string , string);

        TokenVector* mContentVector;
};

#endif // CONTENTPARSER_H
