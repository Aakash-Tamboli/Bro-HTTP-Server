#ifndef __BRO_HEADER_UTILITY__
#define __BRO_HEADER_UTILITY__ 13

#include<bro.h>

class HeaderUtility
{
private:
HeaderUtility();
public:
static void parseHeader(const char *,map<string,string> &);
};

#endif
