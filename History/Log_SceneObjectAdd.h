#pragma once
#include "HistoryLog.h"

class Log_SceneObjectAdd :
    public HistoryLog
{
public:
    Log_SceneObjectAdd(unsigned int theTarget);
    std::string toString()
    {
        char temp[256];
        sprintf(temp,"\t\t\t<Log Type=\"SceneObjectAdd\" Target=\"%d\" />\n",m_target);
        std::string out(temp);
        return out;
    }
public:
    ~Log_SceneObjectAdd(void);
};
