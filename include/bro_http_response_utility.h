#ifndef __BRO_HTTP_RESPONSE_UTILITY
#define __BRO_HTTP_RESPONSE_UTILITY 16

#include <bro_global.h>
#include <bro_response.h>
class HttpResponseUtility
{
private:
    HttpResponseUtility();

public:
    static void sendResponse(int, Response &);
};

#endif
