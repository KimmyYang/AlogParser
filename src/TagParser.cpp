#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include "TagParser.h"
#include "Utility.h"
#include "TagBeeHD.h"
#include "LogData.h"
#include "Constants.h"
#include "AlogParserException.h"

const string TYPE_BEEHD = "BeeHD";

TagParser::TagParser()
{
    //ctor
    mTagParser = NULL;
}
TagParser::TagParser(string tag_type, string tags)
{
    //ctor
    mTagType = tag_type;
    mTag.clear();
    mTagParser = NULL;
    //mTagVector = NULL;
    createTag(tags);
}
TagParser::~TagParser()
{
    //dtor
}

void TagParser::createTag(string tags){
#if (_DEBUG)
    cout<<"[createTag] tag_type = "<<mTagType<<", tag="<<tags<<endl;
#endif
    if(mTagType == TAG_TAG){
        if(tags.find(DELIM_COMMA) != string::npos){
            Utility::StrParser2Vector(tags,DELIM_COMMA,mTagVector);
            cout<<"mTagVector size = "<<mTagVector.size()<<endl;
        }
        else{
            mTag = tags;
        }
    }
    else if(mTagType == TAG_TAG_PROFILE){
        loadProfile(tags);
    }
}

void TagParser::loadProfile(string file){
    //open file ..
    std::ifstream input(file);
    if(!input.is_open()){
        throw AlogParserException(ERROR_OPEN_FILE);
    }

    /*if(mTagVector==NULL){
        mTagVector = new TokenVector();
        mTagVector->reserve(20);
    }*/
    for( std::string tag; getline( input, tag );){
        tag = Utility::splitDelim(tag,DELIM_SEMICOLON);
        mTagVector.push_back(tag);
    }
#if (_DEBUG)
    printTagVector();
#endif
    input.close();
}

string TagParser::parserLine(string line){

    if(mTag.empty() && mTagVector.empty()){
        if(_DEBUG)Utility::coute("mTagParser/mTagVector has not created yet!!");
        return EMPTY_STRING;
    }
    size_t pos = 0, index = 0;
    string _line = line;

    while((pos=line.find(DELIM_SPACE))!=string::npos){
        string token = line.substr(0,pos);

        if(token==DELIM_SPACE || token.empty()){
            line.erase(0,pos+1);
            continue;
        }
        if(index == CONT_TAG){//TAG
#if (_VDEBUG)
            cout<<"token = "<<token<<endl;
#endif
            if(isMatch(Utility::splitTagColon(token)))return _line;
            return EMPTY_STRING;
        }
        line.erase(0,pos+1);
        ++index;
    }
    return EMPTY_STRING;
}

bool TagParser::isMatch(string token){
    if(mTagType==TAG_TAG_PROFILE){
        return isMatchVectorTag(token);
    }
    else if(mTagType==TAG_TAG){
        return mTag.compare(token)==0?true:false;
    }
    return false;
}

bool TagParser::isMatchVectorTag(string tag){
    //if(mTagVector==NULL)return false;
    TokenVector::iterator itor;
    for(itor=mTagVector.begin(); itor!=mTagVector.end(); ++itor){
#if (_VDEBUG)
        cout<<"[isMatchVectorTag] (*itor) = "<<(*itor)<<endl;
        cout<<"[isMatchVectorTag] tag = "<<tag<<endl;
#endif
        if((*itor) == tag)return true;
    }
    return false;
}

void TagParser::printTagVector(){
    //if(mTagVector==NULL)return;
    int _size = mTagVector.size();
    cout<<"mTagVectorSize = "<<_size<<endl;
    for(int i=0; i<_size; ++i){
        cout<<"mTagVector["<<i<<"]:"<<mTagVector.at(i)<<endl;
    }
}


