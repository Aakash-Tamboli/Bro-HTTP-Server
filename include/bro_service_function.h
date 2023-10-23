#ifndef __BRO_SERVICE_FUNCTION
#define __BRO_SERVICE_FUNCTION 17

#include<bro.h>
#include<bro_request.h>
#include<bro_response.h>

class ServiceFunction
{
public:
virtual void doService(Request &,Response &)=0;
};

typedef struct __url__mapping
{
__request_method__ requestMethod;
ServiceFunction *function;
}URLMapping;

#endif
