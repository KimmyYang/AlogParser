#ifndef ARGSMANAGER_H
#define ARGSMANAGER_H


class ArgsManager
{
    public:
        virtual ~ArgsManager();
        static string TAG_ARRAY[];
        static int TAG_ARRAY_SIZE;

        static ArgsManager* getArgsManager();
        void GenParser(char* command[], int commad_size);
        bool hasParser(AlogParser **parser, string tag);
        string getContent(string tag);
    protected:
    private:
        ArgsManager();
        static ArgsManager *mInstance;
        void setCommandMap(char* command[], int commad_size);
        string getCommand(char* command[], int commad_size);
        void createParserMap();
        CommandMap* mCommandMap;
        ParserMap* mParserMap;
};

#endif // ARGSMANAGER_H
