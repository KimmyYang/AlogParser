#ifndef PARSERCONDITION_H
#define PARSERCONDITION_H
#include "TypeDef.h"
class ArgsManager;

class ParserCondition
{
    public:
        ParserCondition(ArgsManager*);
        virtual ~ParserCondition();
        static ParserCondition* getParserCondtion(ArgsManager* pArgs);
        bool checkCondtion(string);
        void update(string tag, bool isMatch);
        void reset();

    protected:
    private:
        void initCondition();
        bool isOrCondtion();

        static ParserCondition *mInstance;
        bool mIsOrCondition;
        ConditionMap *mCondMap;
        ArgsManager *mArgs;
};

#endif // PARSERCONDITION_H
