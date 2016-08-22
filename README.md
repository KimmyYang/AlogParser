# AlogParser
* This parser is coded with C++, and can parser the android logcat log.
* You can input tag, content, time, process/thread id,etc.. and the AlogParser will help to filter the log you want.

# Input Format
* Eample: ./AlogParser -st 07-25 18:37:18.884 -et 07-25 18:37:18.889 -p 4514 -c E:\Kimmy\test\ContentProfile.txt -f E:\Kimmy\test\phone_crash.log
* start time : -st
* end time : -et
* process id : -p
* thread id : -t
* tag : -s
* tag profile : -sf
(example: TagProfile.txt)
* content profile: -c
(example: ContentProfile.txt)
* "Or" the tag and content condition : -or 
* input log : -f
* More information please reference to TypeDef.h
