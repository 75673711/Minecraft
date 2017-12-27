#include "commondefine.h"

#include <QDateTime>

static __int64 delta_time = 0;
static __int64 last_time = 0;

__int64 GetDeltaTime()
{
    return delta_time;
}

void UpdateDeltaTime(bool reset)
{
    if (reset)
    {
        delta_time = 0;
        last_time = QDateTime::currentMSecsSinceEpoch();
    }
    else
    {
        __int64 temp = QDateTime::currentMSecsSinceEpoch();
        delta_time = temp - last_time;
        last_time = temp;
    }
}
