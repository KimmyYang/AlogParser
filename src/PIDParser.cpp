#include "PIDParser.h"
#include "Utility.h"
#include <iostream>
PIDParser::PIDParser()
{
    //ctor
}
PIDParser::PIDParser(int pid)
{
    //ctor
    mPID = pid;
}

PIDParser::~PIDParser()
{
    //dtor
}
string PIDParser::parserLine(string line){

    size_t pos = 0, index = 0;
    string _line = line;
#if (_VDEBUG)
    cout<<"[PIDParser_parserLine] + line = "<<line<<endl;
#endif
    while((pos=line.find(DELIM_SPACE))!=string::npos){
        string token = line.substr(0,pos);
        if(token==DELIM_SPACE || token.empty()){
            line.erase(0,pos+1);
            continue;
        }
        else if(index == CONT_PID){//PID
            if(isMatch(token)) return _line;
            else return EMPTY_STRING;
        }
        line.erase(0,pos+1);
        ++index;
    }
    return EMPTY_STRING;
}
bool PIDParser::isMatch(string token){
    if(mPID == Utility::Str2Int(token))return true;
    return false;
}
