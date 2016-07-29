#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <set>
#include "ConstantsDef.h"
#include "AlogParser.h"
#include "AlogExport.h"
#include "TagParser.h"
#include "PIDParser.h"
#include "TIDParser.h"
#include "TimeParser.h"
#include "Utility.h"
#include "TypeDef.h"
#include "Constants.h"
#include "AlogParserException.h"

using namespace std;

//parameter
string INPUT_FILE="";
CommandMap* commandMap = new CommandMap();
ParserMap* parserMap = NULL;
string TAG_ARRAY[5] = {TAG_START_TIME,TAG_PROCESS_ID,TAG_THREAD_ID,TAG_TAG,TAG_TAG_PROFILE};
int TAG_ARRAY_SIZE = sizeof(TAG_ARRAY)/sizeof(*TAG_ARRAY);

//function
string getCommand(char* command[], int commad_size);
string getContent(string tag);
void setCommandMap(char* command[], int commad_size);
bool getParser(AlogParser **parser,string tag);
bool isValidTag(string tag);
void createParserMap();

int main(int argc, char* argv[])
{
    try{
        if(argc <= 1){
            throw AlogParserException(ERROR_PARAMETER);
        }

        string sArgv = argv[1];
        if(sArgv==TAG_HELP){
            //has not implement yet ..
            return SUCCESS;
        }
        //compose arguments
        setCommandMap(argv, argc);
        INPUT_FILE = getContent(TAG_FILE);
        cout<<"INPUT_FILE = "<<INPUT_FILE<<endl;
        if(INPUT_FILE.empty()){
            throw AlogParserException(ERROR_PARAMETER);
        }

        //open file ..
        std::ifstream input(INPUT_FILE);
        if(!input.is_open()){
            throw AlogParserException(ERROR_OPEN_FILE);
        }

        //start parser file ...
        AlogParser *parser = NULL;
        AlogExport *writer = new AlogExport(INPUT_FILE);
        int index = 0;
        string _line;
        createParserMap();
        cout<<"---------------------------------------------------------------"<<endl<<endl;
        for( std::string line; getline( input, line );)
        {
            index = 0;
            _line = line;

            while(index<TAG_ARRAY_SIZE | getParser(&parser,TAG_ARRAY[index])){

                if(parser!=NULL) {
                    line = parser->parserLine(line);
                    if(line == EMPTY_STRING){
                        break;
                    }
                }
                ++index;
                if(index == TAG_ARRAY_SIZE)break;
            }
            if(line!=EMPTY_STRING){//match all conditions
#if (_VDEBUG)
                cout<<"save line = "<<line<<endl;
#endif
                writer->saveLine(line);
            }
        }
#if (_VDEBUG)
        //writer->printLine();
#endif
        //write parser file ...
        writer->writeFile();
        input.close();
    }catch(AlogParserException &ex){//AlogParserException
        cerr<<"[Exception] code:"<<ex.code()<<", what:"<<ex.what()<<endl;
        return ex.code();
    }catch(exception e){
        cerr<<"[Exception] what:"<<e.what()<<endl;
        return ERROR_GENERIC;
    }
    return SUCCESS;
}

/*
format: map(string tag, AlogParser*)
*/
void createParserMap(){
    AlogParser* parser = NULL;
    parserMap = new ParserMap;
    string tag;
    for(int i=0; i<TAG_ARRAY_SIZE; ++i){
        tag = TAG_ARRAY[i];
        if(!getContent(tag).empty()){
            if(tag == TAG_START_TIME)parser = new TimeParser(getContent(TAG_START_TIME),getContent(TAG_END_TIME));
            else if(tag == TAG_PROCESS_ID)parser = new PIDParser(Utility::Str2Int(getContent(TAG_PROCESS_ID)));
            else if(tag == TAG_THREAD_ID)parser = new TIDParser(Utility::Str2Int(getContent(TAG_THREAD_ID)));
            else if(tag == TAG_TAG || tag == TAG_TAG_PROFILE){
                parser = new TagParser(tag, getContent(tag));
            }else{
                cerr<<"[createParserMap] unknown tag = "<<tag<<endl;
                continue;
            }
            if(parserMap->find(tag) == parserMap->end())
                parserMap->insert(pair<string, AlogParser*>(tag,parser));
        }
        else{
            parserMap->insert(pair<string, AlogParser*>(tag,NULL));
        }
    }
    cout<<"[createParserMap] create done. size = "<<parserMap->size()<<endl;
}

/*
input :
AlogParser parser : assign the proper parser which match the tag
string tag : tag stored in TAG_ARRAY
output :
true : find parser
false : can't find parser
*/
bool getParser(AlogParser **parser, string tag)
{
    ParserMap::iterator itor = parserMap->find(tag);
    if(itor!=parserMap->end() && NULL!=itor->second){
        *parser = itor->second;
        return true;
    }
    else{
        *parser = NULL;
        return false;
    }
}

/*
input : tag
output : match content from the tag
*/
string getContent(string tag){
    CommandMap::iterator itor = commandMap->find(tag);
    if(itor!=commandMap->end()){
        return (itor->second)->content;
    }
    return EMPTY_STRING;
}

bool isValidTag(string tag){
    for(int i=0; i<TAG_ARRAY_SIZE; ++i){
        if(tag == TAG_ARRAY[i])return true;
    }
    return false;
}

void setCommandMap(char* command[], int commad_size){
    string type;
    string content;
    CommandInfo* info;
    TokenVector *cmdVector = Utility::StrParser2Vector(getCommand(command, commad_size),DELIM_SEMICOLON);

    int vecSize = cmdVector->size();
    for(int i=0; i<vecSize; ++i){
        type = cmdVector->at(i);
        content = cmdVector->at(++i);
        info = new CommandInfo();
        info->content = content;
        commandMap->insert(pair<string,CommandInfo*>(type,info));
    }
    delete cmdVector;
}

/*
compose the command with the comma
*/
string getCommand(char* command[], int commad_size){
    Utility::couti("[getCommand]+");
    string cmd = "";
    string _time;
    _time.clear();
    for(int i=1; i<commad_size; ++i){
        cout<<"command["<<i<<"] = "<<command[i]<<endl;
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
    }
    Utility::couti("[getCommand] cmd:"+cmd);
    return cmd;
}


