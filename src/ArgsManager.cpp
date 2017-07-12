#include <stddef.h>
#include <string.h>
#include "Utility.h"
#include "TypeDef.h"
#include "TagParser.h"
#include "PIDParser.h"
#include "TIDParser.h"
#include "TimeParser.h"
#include "AlogParser.h"
#include "ContentParser.h"
#include "ArgsManager.h"

using namespace std;

ArgsManager* ArgsManager::mInstance = NULL;

string ArgsManager::TAG_ARRAY[7] = {TAG_START_TIME,TAG_PROCESS_ID,TAG_THREAD_ID,TAG_TAG,TAG_TAG_PROFILE,TAG_CONTENT,TAG_CONTENT_PROFILE};
int ArgsManager::TAG_ARRAY_SIZE = sizeof(ArgsManager::TAG_ARRAY)/sizeof(*ArgsManager::TAG_ARRAY);

ArgsManager::ArgsManager()
{
    //ctor
    mCommandMap = new CommandMap();
    mParserMap = new ParserMap();
}

ArgsManager::~ArgsManager()
{
    //dtor
}

ArgsManager* ArgsManager::getArgsManager(){
    if(mInstance == NULL){
        mInstance = new ArgsManager();
    }
    return mInstance;
}

void ArgsManager::GenParser(char* command[], int commad_size){
    setCommandMap(command,commad_size);//arrange args first
    createParserMap();
}


void ArgsManager::setCommandMap(char* command[], int commad_size){
    string type, content;
    CommandInfo* info;
    TokenVector cmdVector;
    Utility::StrParser2Vector(getCommand(command, commad_size),DELIM_SEMICOLON,cmdVector );
    int vecSize = cmdVector.size();

    for(int i=0; i<vecSize; ++i){
        type = cmdVector.at(i);
        content = cmdVector.at(++i);
        info = new CommandInfo();
        info->content = content;
#if (_VDEBUG)
        cout<<"[setCommandMap] type = "<<type<<", content = "<<content<<endl;
#endif
        mCommandMap->insert(pair<string,CommandInfo*>(type,info));
    }
#if (_VDEBUG)
    cout<<"[setCommandMap] commandMapSize = "<<mCommandMap->size()<<endl;
#endif
}

/*
compose the command with the comma
*/
string ArgsManager::getCommand(char* command[], int commad_size){
#if (_VDEBUG)
    cout<<"[getCommand]+"<<endl;
#endif
    string cmd = "", _time="";
    _time.clear();
    for(int i=1; i<commad_size; ++i){
#if (_VDEBUG)
        cout<<"command["<<i<<"] = "<<command[i]<<endl;
#endif
        if(!_time.empty()){
            _time.append(DELIM_SPACE);
            _time.append(command[i]);
            cmd.append(_time);
            cmd.append(DELIM_SEMICOLON);
            _time.clear();
            continue;
        }
        cmd.append(command[i]);
        cmd.append(DELIM_SEMICOLON);
        if(!strcmp(command[i],TAG_START_TIME) || !strcmp(command[i],TAG_END_TIME)){
            ++i;
            _time = command[i];
        }
        else if(!strcmp(command[i],TAG_OR)){
            cmd.append(TAG_OR);//content
            cmd.append(DELIM_SEMICOLON);
        }
    }
#if (_VDEBUG)
    cout<<"[getCommand] cmd:"<<cmd<<endl;
#endif
    return cmd;
}

/*
format: map(string tag, AlogParser*)
*/
void ArgsManager::createParserMap(){
    AlogParser* parser = NULL;
    string tag;
    for(int i=0; i<TAG_ARRAY_SIZE; ++i){
        tag = TAG_ARRAY[i];
        if(!getContent(tag).empty()){
            if(tag == TAG_START_TIME)parser = new TimeParser(getContent(TAG_START_TIME),getContent(TAG_END_TIME));
            else if(tag == TAG_PROCESS_ID)parser = new PIDParser(Utility::Str2Int(getContent(TAG_PROCESS_ID)));
            else if(tag == TAG_THREAD_ID)parser = new TIDParser(Utility::Str2Int(getContent(TAG_THREAD_ID)));
            else if(tag == TAG_TAG || tag == TAG_TAG_PROFILE){
                parser = new TagParser(tag, getContent(tag));
            }else if(tag == TAG_CONTENT || tag == TAG_CONTENT_PROFILE){
                parser = new ContentParser(tag, getContent(tag));
            }else{
                cerr<<"[createParserMap] unknown tag = "<<tag<<endl;
                continue;
            }
            if(mParserMap->find(tag) == mParserMap->end())
                mParserMap->insert(pair<string, AlogParser*>(tag,parser));
        }
        else{
            mParserMap->insert(pair<string, AlogParser*>(tag,NULL));
        }
    }
    //cout<<"[createParserMap] create done. size = "<<mParserMap->size()<<endl;
}

/*
input :
AlogParser parser : assign the proper parser which match the tag
string tag : tag stored in TAG_ARRAY
output :
true : find parser
false : can't find parser
*/
bool ArgsManager::hasParser(AlogParser **parser,string tag)
{
#if (_VDEBUG)
    cout<<"[hasParser]+ tag = "<<tag<<endl;
#endif
    ParserMap::iterator itor = mParserMap->find(tag);
    if(itor!=mParserMap->end() && NULL!=itor->second){
        *parser = itor->second;
    }
    else{
        *parser = NULL;
    }
    return true;
}

/*
input : tag
output : match content from the tag
*/
string ArgsManager::getContent(string tag){
    CommandMap::iterator itor = mCommandMap->find(tag);
    if(itor!=mCommandMap->end()){
        //cout<<"[getContent] tag = "<<tag<<endl;
        //cout<<"[getContent] content = "<<(itor->second)->content<<endl;
        return (itor->second)->content;
    }
    return EMPTY_STRING;
}
