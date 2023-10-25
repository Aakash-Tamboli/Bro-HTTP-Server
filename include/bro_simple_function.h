#ifndef __BRO_SIMPLE_FUNCTION__
#define __BRO_SIMPLE_FUNCTION__ 20

#include <bro_global.h>
#include <bro_service_function.h>
#include <bro_request.h>
#include <bro_response.h>

class SimpleFunction : public ServiceFunction
{
private:
    void (*mappedFunction)(Request &, Response &);

public:
    SimpleFunction(void (*mappedFunction)(Request &, Response &));
    void doService(Request &, Response &);
};

#endif
