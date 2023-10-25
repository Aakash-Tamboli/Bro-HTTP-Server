#ifndef __BRO_ERROR__
#define __BRO_ERROR__ 11

#include <bro_global.h>

class Error
{
private:
    string error;

public:
    Error(string);
    bool hasError();
    string getError();
};

#endif
