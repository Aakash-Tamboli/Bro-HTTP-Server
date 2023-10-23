#include<bro_simple_startup_function.h>

SimpleStartupFunction::SimpleStartupFunction(int priorityNumber,void (*startupFunction)(void))
{
this->startupFunction=startupFunction;
this->priorityNumber=priorityNumber;
}
void SimpleStartupFunction::run()
{
startupFunction();
}
int SimpleStartupFunction::getPriorityNumber()
{
return this->priorityNumber;
}
