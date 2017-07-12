#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <set>
#include "ConstantsDef.h"
#include "AlogParser.h"
#include "AlogExport.h"
#include "Utility.h"
#include "TypeDef.h"
#include "Constants.h"
#include "ArgsManager.h"
#include "ParserCondition.h"
#include "AlogParserException.h"

using namespace std;

//parameter
string INPUT_FILE="";


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
        }else if(sArgv==TAG_VER){
            return VERSION;
        }

        //compose arguments
        ArgsManager *pArgs = ArgsManager::getArgsManager();
        pArgs->GenParser(argv, argc);

        //load file
        INPUT_FILE = pArgs->getContent(TAG_FILE);
#if (_DEBUG)
        cout<<"INPUT_FILE = "<<INPUT_FILE<<endl;
#endif
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
        ParserCondition *condtion = ParserCondition::getParserCondtion(pArgs);
        int index = 0;
        string _line, tag;
#if (_DEBUG)
        cout<<"---------------------------------------------------------------"<<endl<<endl;
#endif
        for( std::string line; getline( input, line );)
        {
            index = 0;
            _line = line;
            condtion->reset();
            while(pArgs->hasParser(&parser,ArgsManager::TAG_ARRAY[index])){
                tag = ArgsManager::TAG_ARRAY[index];
                if(parser!=NULL) {
                    //cout<<"line = "<<line<<endl;
                    line = parser->parserLine(line);
                    //cout<<"tag = "<<tag<<", line = "<<line<<endl;
                    condtion->update(tag, line==EMPTY_STRING?false:true);//update condition

                    if(line==EMPTY_STRING && condtion->checkCondtion(tag)){//and
                        break;
                    }
                    else line = _line;
                }
                else condtion->update(tag, false);//update condition
                ++index;
                if(index >= ArgsManager::TAG_ARRAY_SIZE)break;
            }
            if(line!=EMPTY_STRING){//match all conditions
#if (_VDEBUG)
                cout<<"save line = "<<line<<endl;
#endif
                writer->saveLine(line);
            }
        }
#if (_DEBUG)
        cout<<"---------------------------------------------------------------"<<endl<<endl;
#endif
        //writer->printLine();
        //write parser file ...
        writer->writeFile();
        input.close();
    }catch(AlogParserException &ex){
        cerr<<"[Exception] code:"<<ex.code()<<", what:"<<ex.what()<<endl;
        return ex.code();
    }catch(exception e){
        cerr<<"[Exception] what:"<<e.what()<<endl;
        return ERROR_GENERIC;
    }
    return SUCCESS;
}

