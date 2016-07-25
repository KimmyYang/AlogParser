# AlogParser
* This parser is coded with C++, and can parser the android logcat log.
* You can input tag, time, process/thread id, and the AlogParser will help to filter the log you want.

# Input Format
* Eample: ./AlogParser -st 07-25 18:37:18.884 -et 07-25 18:37:18.889 -p 4514 -f E:\Kimmy\test\phone_crash.log
* tag : -s
* start time : -st
* end time : -et
* process id : -p
* thread id : -t
* input log : -f
* More information please reference to TypeDef.h
