#include "ParserCondition.h"
#include "ArgsManager.h"

ParserCondition* ParserCondition::mInstance = NULL;

ParserCondition::ParserCondition(ArgsManager* pArgs)
{
    //ctor
    mArgs = pArgs;
    initCondition();
}

ParserCondition::~ParserCondition()
{
    //dtor
}

ParserCondition* ParserCondition::getParserCondtion(ArgsManager* pArgs){
    if(mInstance == NULL)mInstance = new ParserCondition(pArgs);
    return mInstance;
}

/*
Or condition : 4bits
1st bit : or condition setup or not
2st bit : match user parser or not
3st bit : parser yet or not
4st bit : reserve
*/
void ParserCondition::initCondition(){
    mIsOrCondition = (mArgs->getContent(TAG_OR)).empty()?false:true;
    mCondMap = new ConditionMap();//<string,int>
    string tag = "";int condition = 0x0;

    for(int i=0; i<ArgsManager::TAG_ARRAY_SIZE; ++i){
        tag = ArgsManager::TAG_ARRAY[i];
        if(tag == TAG_TAG || tag == TAG_TAG_PROFILE || tag == TAG_CONTENT || tag == TAG_CONTENT_PROFILE){
            condition = 0x1;
        }
        else{
            condition = 0x0;
        }
        mCondMap->insert(pair<string,int>(tag,condition));
    }
}

void ParserCondition::update(string tag, bool isMatch){
    ConditionMap::iterator itor = mCondMap->find(tag) ;
    if(itor != mCondMap->end()){
        int condition = itor->second;
        condition = isMatch?condition|0x06:condition|0x04;
        itor->second = condition;
#if (_VDEBUG)
        cout<<"tag = "<<tag<<endl;
        printf("[update] condition = %x\n",itor->second);
#endif
    }
}

void ParserCondition::reset(){
    string tag = "";int condition = 0x0;
    for(int i=0; i<ArgsManager::TAG_ARRAY_SIZE; ++i){
        tag = ArgsManager::TAG_ARRAY[i];
        ConditionMap::iterator itor = mCondMap->find(tag);
        if(tag == TAG_TAG || tag == TAG_TAG_PROFILE || tag == TAG_CONTENT || tag == TAG_CONTENT_PROFILE){
            condition = 0x1;
        }
        else{
            condition = 0x0;
        }
        itor->second = condition;
    }
}

bool ParserCondition::checkCondtion(string tag){
    if((tag==TAG_TAG || tag==TAG_TAG_PROFILE || tag==TAG_CONTENT || tag==TAG_CONTENT_PROFILE) && mIsOrCondition)return isOrCondtion();
    return true; //always true if no any condition
}

bool ParserCondition::isOrCondtion(){
    int tag_condition = mCondMap->find(TAG_TAG)->second | mCondMap->find(TAG_TAG_PROFILE)->second;
    int content_condtion = mCondMap->find(TAG_CONTENT)->second | mCondMap->find(TAG_CONTENT_PROFILE)->second;
#if (_VDEBUG)
        printf("[isOrCondtion] tag_condition:%x , tag_profile_condition:%x , content_condtion:%x\n",tag_condition,tag_profile_condition,content_condtion);
#endif
    bool isMatch = false;
    if(tag_condition>>0x2 & content_condtion>>0x2){
        if((tag_condition | content_condtion) == 0x05)isMatch = true;
    }
#if (_VDEBUG)
    cout<<"[isOrCondtion] isMatch = "<<isMatch<<endl;
#endif
    return isMatch;
}
