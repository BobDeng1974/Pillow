#include "Log_EdgeStartChange.h"

Log_EdgeStartChange::Log_EdgeStartChange(unsigned int target,unsigned int theIndex,int theStart)
    :HistoryLog(LogType::Edge_Start_Change,target),
      m_index(theIndex),
      start(theStart)
{
}

Log_EdgeStartChange::~Log_EdgeStartChange(void)
{
}
