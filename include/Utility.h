#ifndef UTILITY_H
#define UTILITY_H
#include <set>
#include "TypeDef.h"

using namespace std;
class Utility
{
    public:
        Utility();
        virtual ~Utility();

        static TokenVector* StrParser2Vector(string str, string delim);
        static int Str2Int(string str);
        static string Int2Str(int value);
        static string getNowTime2Str();
        static TimeInfo Str2TimeInfo(string str);
        static char* Str2pChar(string str);
        static void delete_pChar(char* cstr);

        static string splitTagColon(string str);
        static string splitDelim(string str, string delim);
        static void coutw(string output);
        static void couti(string output);
        static void coute(string output);

    protected:
    private:
};

#endif // UTILITY_H
