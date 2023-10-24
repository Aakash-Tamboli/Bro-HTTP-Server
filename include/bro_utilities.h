#ifndef __BRO_UTILITIES__
#define __BRO_UTILITIES__ 6

#include<bro_global.h>

class BroUtilities
{
private:
BroUtilities();
public:
static bool isHexChar(char);
static void decodePercentEncoding(char *,char *);
static void loadMIMETypes(map<string,string> &);
};


#endif
