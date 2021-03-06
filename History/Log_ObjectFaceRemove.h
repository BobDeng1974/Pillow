#pragma once
#include "HistoryLog.h"
#include "../Core/Face.h"

class Log_ObjectFaceRemove :
    public HistoryLog
{
public:
    const unsigned int m_index;
public:
    Face *o;
public:
    Log_ObjectFaceRemove(unsigned int theTarget,unsigned int theIndex,Face *theO);
    std::string toString()
    {
        char temp[256];
        //sprintf(temp,"\t\t\t<Log Type=\"ObjectFaceRemove\" Target=\"%d\" Index=\"%d\" />\n",target,index);
        std::string out(temp);
        return out;
    }
        void clear()
    {
        delete o;
    }

                        void operator=(const Log_ObjectFaceRemove& in)
    {
        in;
    }
public:
    ~Log_ObjectFaceRemove(void);
};
