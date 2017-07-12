#include <iostream>
#include "TimeParser.h"
#include "Utility.h"

TimeParser::TimeParser(string startTime, string endTime)
{
    //ctor
    mStartTime = Utility::Str2TimeInfo(startTime);
    mEndTime = Utility::Str2TimeInfo(endTime);
    if(0==mStartTime.compare(mEndTime) || endTime.empty())mUseStartTimeOnly=true;
    else mUseStartTimeOnly=false;
    cout<<"mUseStartTimeOnly = "<<mUseStartTimeOnly<<endl;
}

TimeParser::~TimeParser()
{
    //dtor
}

string TimeParser::parserLine(string line){
    size_t pos = 0, index = 0;
    string _line = line;
    string _sTime;
    while((pos=line.find(DELIM_SPACE))!=string::npos){
        string token = line.substr(0,pos);
        if(token==DELIM_SPACE || token.empty()){
            line.erase(0,pos+1);
            continue;
        }
        else if(index == CONT_DATE){
            _sTime = token;
        }
        else if(index == CONT_TIME){
            _sTime.append(" ");
            _sTime.append(token);
            if(isMatch(_sTime)){
                return _line;
            }
            return EMPTY_STRING;
        }
        line.erase(0,pos+1);
        ++index;
    }
    return EMPTY_STRING;
}
bool TimeParser::isMatch(string token){
    TimeInfo _time = Utility::Str2TimeInfo(token);
    int s_compare_result = mStartTime.compare(_time);
    int e_compare_result = mEndTime.compare(_time);
#if (_VDEBUG)
    printTime(mStartTime);
    printTime(_time);
    printTime(mEndTime);
    cout<<"[parserLine] s_compare_result = "<<s_compare_result<<", e_compare_result = "<<e_compare_result<<endl;
#endif
    if(mUseStartTimeOnly && -1 != s_compare_result){
#if (_VDEBUG)
        printTime(mStartTime);
        printTime(_time);
        printTime(mEndTime);
#endif
        return true;
    }
    else if(-1 != s_compare_result && 1 != e_compare_result){
#if (_VDEBUG)
        printTime(mStartTime);
        printTime(_time);
        printTime(mEndTime);
#endif
        return true;
    }
    return false;
}
void TimeParser::printTime(TimeInfo _time){
    cout<<"[printTime] "<<_time.month<<"-"<<_time.day<<" "<<_time.hour<<":"<<_time.minute<<":"<<_time.second<<":"<<_time.minsecond<<endl;
}
