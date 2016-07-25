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

using namespace std;

//parameter
string INPUT_FILE="";
CommandMap* commandMap = NULL;
ParserMap* parserMap = NULL;
string TAG_ARRAY[4] = {TAG_START_TIME,TAG_PROCESS_ID,TAG_THREAD_ID,TAG_TAG};
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
    if(argc <= 1){
        Utility::coute("Please input the parameter ..");
        return ERROR_PARAMETER;
    }

    string sArgv = argv[1];
    if(sArgv==TAG_HELP){
        Utility::couti("Print help ..");
        return SUCCESS;
    }
    try{
        //compose arguments
        setCommandMap(argv, argc);
    }
    catch(int error){
        cerr<<"error  = "<<error<<endl;
        return error;
    }
    INPUT_FILE = getContent(TAG_FILE);

    if(INPUT_FILE.empty()){
        Utility::coute("File is null !!");
        return ERROR_PARAMETER;
    }
    cout<<"INPUT_FILE = "<<INPUT_FILE<<endl;
    cout<<"TAG_ARRAY_SIZE = "<<TAG_ARRAY_SIZE<<endl;

    //open file ..
    std::ifstream input(INPUT_FILE);
    if(!input.is_open()){
        Utility::coutw("Can't open file : "+INPUT_FILE);
        return ERROR_OPEN_FILE;
    }

    try{
        //start parser file ...
        AlogParser *parser = NULL;
        AlogExport *writer = new AlogExport(INPUT_FILE);
        int index = 0;
        bool isAbandon = true;
        string _line;
        createParserMap();
        cout<<"---------------------------------------------------------------"<<endl<<endl;
        for( std::string line; getline( input, line );)
        {
            index = 0;
            _line = line;
            isAbandon = true;

            while(index<TAG_ARRAY_SIZE | getParser(&parser,TAG_ARRAY[index])){

                if(parser!=NULL) {

                    line = parser->parserLine(line);
                    if(line == EMPTY_STRING){
                        break;
                        //isAbandon = true;
                        //line = _line;
                    }
                    //else isAbandon = false;
                }
                ++index;
                if(index == TAG_ARRAY_SIZE)break;
            }
    #if (_DEBUG)
                //cout<<"line = "<<line<<endl;
    #endif

            if(line!=EMPTY_STRING){//match all conditions
                cout<<"save line = "<<line<<endl;
                writer->saveLine(line);
            }
        }
        //writer->printLine();

        //write parser file ...
        writer->writeFile();
        input.close();
    }catch(int error){
        cerr<<"error = "<<error<<endl;
        return error;
    }catch(exception e){
        cerr<<"Exception : "<<e.what()<<endl;
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
            else if(tag == TAG_TAG)parser = new TagParser(getContent(TAG_TAG));
            else{
                cerr<<"[createParserMap] unknown tag = "<<tag<<endl;
                continue;
            }
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
    //cout<<"tag = "<<tag<<endl;
    ParserMap::iterator itor = parserMap->find(tag);
    if(itor!=parserMap->end() && NULL!=itor->second){
        *parser = itor->second;
        //cout<<"tag(itor->first) = "<<itor->first<<endl;
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
    if(commandMap==NULL)Utility::coute("[getContent] commandMap is null");
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

    if(commandMap==NULL)commandMap = new CommandMap();
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


