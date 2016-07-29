#ifndef TIMEPARSER_H
#define TIMEPARSER_H
#include "AlogParser.h"
using namespace std;

class TimeParser: public AlogParser
{
    public:
        TimeParser(string , string);
        virtual ~TimeParser();
        string parserLine(string line);
        bool isMatch(string);
    protected:
    private:
        void printTime(TimeInfo _time);
        TimeInfo mStartTime;
        TimeInfo mEndTime;
        bool mUseStartTimeOnly;
};

#endif // TIMEPARSER_H
