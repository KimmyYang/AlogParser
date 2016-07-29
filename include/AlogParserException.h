#ifndef ALOGPARSEREXCEPTION_H
#define ALOGPARSEREXCEPTION_H
#include "TypeDef.h"

class AlogParserException: public std::exception
{
    public:
        AlogParserException(int code);
        virtual ~AlogParserException();
        virtual char const *what();
        const int code();
    protected:
    private:
        int mCode;
};

#endif // ALOGPARSEREXCEPTION_H
