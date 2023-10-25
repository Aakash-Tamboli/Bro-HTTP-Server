#ifndef __BRO_HTTP_ERROR_STATUS_UTILITY__
#define __BRO_HTTP_ERROR_STATUS_UTILITY__ 9
#include <bro_global.h>

class HttpErrorStatusUtility
{
private:
    HttpErrorStatusUtility();

public:
    static void sendBadRequestError(int);
    static void sendHttpVersionNotSupportedError(int,const char *);
    static void sendNotFoundError(int,const  char *);
    static void sendMethodNotAllowedError(int,const char *);
    static void sendInternalError(int,const char *);
};

#endif
