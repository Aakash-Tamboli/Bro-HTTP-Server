#ifndef __BRO_THREAD_WRAPPER__
#define __BRO_THREAD_WRAPPER__ 600

#include<bro_global.h>
class BroThreadWrapper
{
public:
thread *th;
bool hasCompleted;
BroThreadWrapper *next;
};

#endif
