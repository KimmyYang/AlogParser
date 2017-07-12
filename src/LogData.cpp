
#include "LogData.h"
#include "Utility.h"


LogData::LogData(string time, int pid, int tid, string tag, string content)
{
    //ctor
    mTime = time;
    mPID = pid;
    mTID = tid;
    mTag = tag;
    mContent = content;
}

LogData::~LogData()
{
    //dtor
}

string LogData::toString()
{
    string data;
    data.append(mTime+DELIM_SPACE+
                Utility::Int2Str(mPID)+DELIM_SPACE+
                Utility::Int2Str(mTID)+DELIM_SPACE+
                mTag+DELIM_SPACE+
                mContent);
    return data;
}
