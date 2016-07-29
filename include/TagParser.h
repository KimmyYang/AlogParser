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
        TagParser(string, string );
        virtual ~TagParser();
        string parserLine(string line);
        bool isMatch(string);
    protected:
    private:
        string mTagType;
        string mTag;
        void createTag(string tag);
        void loadProfile(string file);
        bool isMatchVectorTag(string tag);
        void printTagVector();
        TagParser* mTagParser;
        ProfileLoader *mProfileLoader;
        TokenVector *mTagVector;
};

#endif // TAGPARSER_H
