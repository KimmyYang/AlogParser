#include "AlogExport.h"
#include "LogData.h"
#include <vector>
#include <fstream>
#include <iostream>

const int RESERVE_SIZE = 1000;

AlogExport::AlogExport(string file)
{
    //ctor
    mInputFile = file;
    mLogLineVector = new LogLineVector();
    mLogDataVector = new LogDataVector();
}

AlogExport::~AlogExport()
{
    //dtor
}

void AlogExport::saveLine(string line){

    int vectorSize = mLogLineVector->size();

    if(vectorSize%RESERVE_SIZE == 0){
        mLogLineVector->reserve(vectorSize+RESERVE_SIZE);
    }
    mLogLineVector->push_back(line);
}

void AlogExport::printLine(){
    int vectorSize = mLogLineVector->size();
    for(int i=0; i<vectorSize; ++i){
        cout<<"printLine: "<<mLogLineVector->at(i)<<endl;
    }
}

void AlogExport::writeLine(){

    string file = getOutputFile();
#if (_OUTPUT_STREAM)
    cout<<"Output File : "<<file<<endl;
#endif
    ofstream  outFile(file,ios::out);
    if(!outFile.is_open()){
        Utility::coute("Fail to open the file ...");
        return;
    }
    int LogLineVectorSize = mLogLineVector->size();
    for(int i=0; i<LogLineVectorSize; ++i){
        outFile<<mLogLineVector->at(i)<<endl;
    }
    outFile.close();
}

void AlogExport::writeFile(){
    if(mLogDataVector==NULL || mLogDataVector->empty()){
        writeLine();
        return;
    }

    string file = getOutputFile();
    ofstream  outFile(file,ios::out);
    if(!outFile.is_open()){
        cout<<"Fail to open the file ..."<<endl;
        return;
    }
#if (_OUTPUT_STREAM)
    cout<<"writeFile: starting to write file : "<<file<<endl;
#endif
    int logDataVectorSize = mLogDataVector->size();
    for(int i=0;i<logDataVectorSize;++i){
#if (_VDEBUG)
        cout<<mLogDataVector->at(i)->toString()<<endl;
#endif
        outFile<<mLogDataVector->at(i)->toString()<<endl;
    }
    outFile.close();
#if (_OUTPUT_STREAM)
    cout<<"writeFile: write file done"<<endl;
#endif
}
string AlogExport::getOutputFile(){

    string outPath;
    outPath.append(mInputFile+"_"+Utility::getNowTime2Str());

#if (_VDEBUG)
    cout<<"getOutputFile: path="<<outPath<<endl;
#endif
    return outPath;
}


