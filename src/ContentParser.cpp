#include <iostream>
#include <fstream>
#include <sstream>
#include "Utility.h"
#include "Constants.h"
#include "ContentParser.h"
#include "AlogParserException.h"

using namespace std;

ContentParser::ContentParser(string tag, string source)
{
    //ctor
    createContentMap(tag, source);
}

ContentParser::~ContentParser()
{
    //dtor
}
string ContentParser::parserLine(string line){
    size_t pos = 0, index = 0;
    string _line = line;
#if (_VDEBUG)
    cout<<"_line = "<<_line<<endl;
#endif
    while((pos=line.find(DELIM_SPACE))!=string::npos){
        string token = line.substr(0,pos);
#if (_VDEBUG)
        cout<<"token = "<<token<<" index = "<<index<<endl;
#endif
        if(token==DELIM_SPACE || token.empty()){
            line.erase(0,pos+1);
            continue;
        }
        if(index == CONT_CONT || //ex. RIL: content
        (index==CONT_TAG && token.find(DELIM_COLON)!=string::npos)){//ex. GSMDCT:content
#if (_VDEBUG)
            cout<<"line="<<line<<endl;
#endif
            if(isMatch(line))return _line;
            return EMPTY_STRING;
        }
        line.erase(0,pos+1);
        ++index;
    }
    return EMPTY_STRING;
}

bool ContentParser::isMatch(string content){
#if (_VDEBUG)
    cout<<"content = "<<content<<endl;
#endif
    for(int i=0; i<mContentVector->size(); ++i){
#if (_VDEBUG)
        cout<<"mContentVector[i] = "<<mContentVector->at(i)<<endl;
#endif
        if(content.find(mContentVector->at(i)) != string::npos){
            return true;
        }
    }
    return false;
}

/*
bool ContentParser::isMatch(string content){
    for(int i=0; i<mContentVector->size(); ++i){
        int result = mContentVector->at(i).compare(content);
#if (_DEBUG)
        cout<<"mContentVector->at(i) = "<<mContentVector->at(i)<<endl;
        cout<<"content = "<<content<<endl;
        cout<<"result = "<<result<<endl;
#endif
        if(0==result || result<-1 || isPartialMatch(content,mContentVector->at(i))){
#if (_VDEBUG)
        cout<<"mContentVector->at(i) = "<<mContentVector->at(i)<<endl;
        cout<<"content = "<<content<<endl;
        cout<<"result = "<<result<<endl;
#endif
            return true;
        }
    }
    return false;
}
*/

bool ContentParser::isPartialMatch(const string _str1, string _str2){//_str1:log, _str2:profile
    TokenVector tokenVec;
    Utility::StrParser2Vector(_str1,DELIM_SPACE,tokenVec);

    for(int i=0;i<tokenVec.size();++i){
        //filter space
        string item = tokenVec.at(i);
        if(item.find_first_not_of(' ') != std::string::npos){
#if (_VDEBUG)
            cout<<"item = "<<item<<endl;
#endif
            if(_str2.compare(item) == 0){
                return true;
            }
        }
    }
    return false;
    /*
    std::stringstream ss;
    ss.str(_str);
    std::string item;
    char delim = ' ';
    while (std::getline(ss, item, delim)) {

        //*(result++) = item;
        if(item.find_first_not_of(delim) != std::string::npos)
        {
            // There's a non-space.
            cout<<"item = "<<item<<endl;
        }
    }*/
}

void ContentParser::createContentMap(string tag, string source){
    mContentVector = new TokenVector();
    mContentVector->reserve(20);
#if (_VDEBUG)
    cout<<"createContentMap: content = "<<source<<endl;
#endif
    if(tag == TAG_CONTENT){
        //if(source.find(DELIM_COLON) != string::npos){
            //cout<<"find "<<DELIM_COLON<<endl;
            Utility::StrParser2Vector(source,DELIM_COMMA,*mContentVector);
        //}
    }else if(tag == TAG_CONTENT_PROFILE){
        loadProfile(source);
    }else{
        mContentVector->push_back(source);
    }
#if (_VDEBUG)
    cout<<"createContentMap: mContentVectorSize = "<<mContentVector->size()<<endl;
#endif
}

void ContentParser::loadProfile(string file){
    //open file ..
    std::ifstream input(file);
    if(!input.is_open()){
        throw AlogParserException(ERROR_OPEN_FILE);
    }
    for( std::string content; getline( input, content );){
        content = Utility::splitDelim(content,DELIM_SEMICOLON);
#if (_VDEBUG)
        cout<<"loadProfile: content = "<<content<<endl;
#endif
        mContentVector->push_back(content);
    }
}
