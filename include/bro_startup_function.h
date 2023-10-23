#ifndef __BRO_STARTUP_FUNCTION__
#define __BRO_STARTUP_FUNCTION__ 18
#include<bro.h>
class StartupFunction
{
public:
virtual void run()=0;
virtual int getPriorityNumber()=0;
};

#endif
