#ifndef __BRO_STARTUP_FUNCTION_COMPARATOR__
#define __BRO_STARTUP_FUNCTION_COMPARATOR__ 35

#include<bro_global.h>
#include<bro_startup_function.h>

class StartupFunctionComparator
{
public:
int operator()(StartupFunction *,StartupFunction *);
};

#endif
