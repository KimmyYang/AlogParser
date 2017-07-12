#include "TIDParser.h"
#include "Utility.h"

TIDParser::TIDParser()
{
    //ctor
}
TIDParser::TIDParser(int tid)
{
    //ctor
    mTID = tid;
}

TIDParser::~TIDParser()
{
    //dtor
}
string TIDParser::parserLine(string line){
    size_t pos = 0, index = 0;
    string _line = line;
#if (_VDEBUG)
    cout<<"[TIDParser_parserLine] + line = "<<line<<endl;
#endif
    while((pos=line.find(DELIM_SPACE))!=string::npos){
        string token = line.substr(0,pos);

        if(token==DELIM_SPACE || token.empty()){
            line.erase(0,pos+1);
            continue;
        }
        else if(index == CONT_TID){//TID
            if(isMatch(token)) {
                    return _line;
            }
            else return EMPTY_STRING;
        }
        line.erase(0,pos+1);
        ++index;
    }
    return EMPTY_STRING;
}
bool TIDParser::isMatch(string token){
    if(mTID == Utility::Str2Int(token))return true;
    return false;
}
