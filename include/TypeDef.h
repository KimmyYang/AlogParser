#ifndef TYPEDEF_H_INCLUDED
#define TYPEDEF_H_INCLUDED

#include <vector>
#include <map>
#include <set>
#include <string>
#include <iostream>

class LogData;
class AlogParser;
#define _VDEBUG 0
#define _DEBUG 1

#define EMPTY_STRING ""
#define DELIM_SPACE " "
#define DELIM_COMMA ","
#define DELIM_COLON ":"
#define DELIM_SEMICOLON ";"
#define DELIM_RIGHT_SLASH "\\" //add terminating character
#define DELIM_LEFT_SLASH "/" //add terminating character
#define TAG_TAG "-s"
#define TAG_TAG_PROFILE "-sp" //parser tag with external profile
#define TAG_START_TIME "-st"
#define TAG_END_TIME "-et"
#define TAG_PROCESS_ID "-p"
#define TAG_THREAD_ID "-t"
#define TAG_CONTENT "-c"
#define TAG_OR "-or"
#define TAG_AND "-and"
#define TAG_FILE "-f"
#define TAG_HELP "-h"

#define compare_number(a, b) a<b?-1:a==b?0:1

using namespace std;

typedef unsigned long long _ULL;

enum eContent{
    CONT_DATE = 0,
    CONT_TIME = 1,
    CONT_PID = 2,
    CONT_TID = 3,
    CONT_LOG_TYPE = 4,
    CONT_TAG = 5,
    CONT_CONT = 6
};
typedef struct sCommandInfo{
    std::string content;
}CommandInfo;

typedef struct sTimeInfo{
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int minsecond;

    /*
    return value >0 : _time bigger
    return value =0 : equal
    return value <0 : _time smaller
    */
    int compare(sTimeInfo _time){
        _ULL _ullTime = _time.month*100000000000;
        _ullTime = (_ULL)(_ullTime+((_ULL)_time.day*1000000000)+
                            ((_ULL)_time.hour*10000000)+
                            ((_ULL)_time.minute*100000)+
                            ((_ULL)_time.second*1000)+
                            ((_ULL)_time.minsecond));
        _ULL ullTime = month*100000000000;
        ullTime = (_ULL)(ullTime+((_ULL)day*1000000000)+
                            ((_ULL)hour*10000000)+
                            ((_ULL)minute*100000)+
                            ((_ULL)second*1000)+
                            ((_ULL)minsecond));
#if (_VDEBUG)
        cout<<"_ullTime = "<<_ullTime<<", ullTime = "<<ullTime<<endl;
#endif
        return compare_number(_ullTime,ullTime);
    }
}TimeInfo;



typedef std::vector<std::string> TokenVector;
typedef std::map<std::string,CommandInfo*> CommandMap;
typedef std::vector<LogData*> LogDataVector;
typedef std::set<std::string> TagSet;
typedef std::vector<std::string> LogLineVector;
typedef std::vector<std::string> ContentVector;
typedef std::map<string, AlogParser*> ParserMap;
typedef std::map<int,string> ExceptionMap;
typedef std::map<string, int> ConditionMap;
#endif // TYPEDEF_H_INCLUDED
