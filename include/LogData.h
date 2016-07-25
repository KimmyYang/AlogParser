#ifndef LOGDATA_H
#define LOGDATA_H
#include <string>
using namespace std;

class LogData
{
    public:
        LogData(string time, int pid, int tid, string tag, string content);
        virtual ~LogData();
        string toString();
    protected:
    private:
        string mTime;
        int mPID;
        int mTID;
        string mTag;
        string mContent;
};

#endif // LOGDATA_H
