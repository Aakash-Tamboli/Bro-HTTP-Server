#include<bro_startup_function_comparator.h>

int StartupFunctionComparator::operator()(StartupFunction *left,StartupFunction *right)
{
return left->getPriorityNumber()>right->getPriorityNumber();
}

