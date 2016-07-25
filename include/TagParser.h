#ifndef TAGPARSER_H
#define TAGPARSER_H
#include <iostream>
#include "AlogParser.h"
using namespace std;
class ProfileLoader;
class TagParser: public AlogParser
{
    public:
        TagParser();
        TagParser(string );
        virtual ~TagParser();
        string parserLine(string line);

    protected:
    private:
        void createTag(string tag);
        TagParser* mTagParser;
        ProfileLoader *mProfileLoader;

};

#endif // TAGPARSER_H
