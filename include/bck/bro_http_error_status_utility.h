#ifndef __BRO_HTTP_ERROR_STATUS_UTILITY__
#define __BRO_HTTP_ERROR_STATUS_UTILITY__ 9
#include<bro.h>

class HttpErrorStatusUtility
{
private:
HttpErrorStatusUtility();
public:
static void sendBadRequestError(int);
static void sendHttpVersionNotSupportedError(int,char *);
static void sendNotFoundError(int,char *);
static void sendMethodNotAllowedError(int,char *);
};

#endif

