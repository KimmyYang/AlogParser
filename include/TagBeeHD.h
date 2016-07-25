#ifndef TAGBEEHD_H
#define TAGBEEHD_H
#include <string>
#include "TagParser.h"

using namespace std;
class TagBeeHD: public TagParser
{
    public:
        TagBeeHD();
        virtual ~TagBeeHD();
        bool isTagMatch(string);
    protected:

    private:
        void initTagSet();
        TagSet *mTagSet;
};

#endif // TAGBEEHD_H
