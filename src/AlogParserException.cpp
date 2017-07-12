#include <iostream>
#include <string>
#include "AlogParserException.h"
#include "Constants.h"

using namespace std;
pair<int, char*> array_pool[ERROR_SIZE] = { {ERROR_GENERIC, "internal generic fail"},
                                            {ERROR_OPEN_FILE, "open file error"},
                                            {ERROR_PARAMETER, "input parameter number/format error"}};
AlogParserException::AlogParserException(int code)
{
    //ctor
    mCode = code;
}
AlogParserException::~AlogParserException()
{
    //dtor
}
char const *AlogParserException::what()
{
    pair<int, char*> pair_pool;
    for(int i=0; i<ERROR_SIZE; ++i){
        pair_pool = array_pool[i];
        if(pair_pool.first == mCode){
            return pair_pool.second;
        }
    }
    return exception::what();
}
const int AlogParserException::code(){
    return mCode;
}
