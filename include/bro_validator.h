#ifndef __BRO_VALIDATOR__
#define __BRO_VALIDATOR__ 10

#include <bro_global.h>

class Validator
{
private:
    Validator();

public:
    static bool isValidPath(string &);
    static bool isValidURLFormat(string &);
};

#endif
