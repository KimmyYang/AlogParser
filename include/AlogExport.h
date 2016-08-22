#ifndef ALOGEXPORT_H
#define ALOGEXPORT_H
#include <string>
#include "TypeDef.h"
#include "Utility.h"

using namespace std;

class AlogExport
{
    public:
        AlogExport(string file);
        virtual ~AlogExport();
        void writeFile();
        void saveLine(string);
        void printLine();

    protected:
    private:
        void writeLine();
        string getOutputFile();
        string mInputFile;
        LogDataVector *mLogDataVector;
        LogLineVector *mLogLineVector;//raw data

};

#endif // ALOGEXPORT_H
