#include <iostream>
#include <set>
#include <string>
#include <cstring>
#include <time.h>
#include "Utility.h"

using namespace std;
Utility::Utility()
{
    //ctor
}

Utility::~Utility()
{
    //dtor
}

TokenVector* Utility::StrParser2Vector(string str, string delim){
    size_t pos = 0;
    TokenVector *tokenVector = new TokenVector();
    tokenVector->clear();

    while((pos=str.find(delim))!=string::npos){
        tokenVector->push_back(str.substr(0,pos));
#if (_VDEBUG)
    couti("[StrParser2Vector] token="+tokenVector->back());
    cout<<"pos = "<<pos<<endl;
    cout<<"str = "<<str<<endl;
#endif
        str.erase(0,pos+delim.length());
    }
    if(!str.empty()){
        tokenVector->push_back(str);
    }
    return tokenVector;
}

int Utility::Str2Int(string str){
    return atoi(str.c_str());
}

string Utility::Int2Str(int value){
    return to_string(value);
}

string Utility::splitTagColon(string str){
    size_t colonPos = str.find(DELIM_COLON);
    if(colonPos!=string::npos){
        return str.substr(0,colonPos);
    }
    return str;
}

string Utility::splitDelim(string str, string delim){
    size_t delimPos = str.find(delim);
    if(delimPos!=string::npos){
        return str.substr(0,delimPos);
    }
    return str;
}

string Utility::getNowTime2Str(){
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%H.%M.%S", &tstruct);
    return buf;
}

/*
call DelepChar after execute Str2pChar
*/
char* Utility::Str2pChar(string str){
    char* cstr = new char[str.length()+1];
    strcpy(cstr, str.c_str());
    return cstr;
}
void Utility::delete_pChar(char* cstr){
    delete cstr;
}

/*
format : 06-02 13:42:01
*/
TimeInfo Utility::Str2TimeInfo(string str){
    TimeInfo _time;
    char* pch;
    char* cstr = Str2pChar(str);
    pch = strtok(cstr, " ,.-:");
    _time.month = atoi(pch);
    _time.day = atoi(strtok(NULL, " ,.-:"));
    _time.hour = atoi(strtok(NULL, " ,.-:"));
    _time.minute = atoi(strtok(NULL, " ,.-:"));
    _time.second = atoi(strtok(NULL, " ,.-:"));
    _time.minsecond = atoi(strtok(NULL, " ,.-:"));

    delete_pChar(cstr);
    return _time;
}

//log
void Utility::coutw(string output){
    cout<<"[Warning]: "<<output<<endl;
}
void Utility::couti(string output){
    cout<<"[Info]: "<<output<<endl;
}
void Utility::coute(string output){
    cerr<<"[Error]: "<<output<<endl;
}

