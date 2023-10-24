#ifndef __BRO_APPLICATION_LEVEL_CONTAINER_DEPENDENT_FUNCTION
#define __BRO_APPLICATION_LEVEL_CONTAINER_DEPENDENT_FUNCTION 21

#include<bro.h>
#include<bro_request.h>
#include<bro_response.h>
#include<bro_application_level_container.h>
#include<bro_service_function.h>

class ApplicationLevelContainerDependentFunction:public ServiceFunction
{
private:
void (*mappedFunction)(Request &,Response &,ApplicationLevelContainer &);
ApplicationLevelContainer *applicationLevelContainer;
public:
ApplicationLevelContainerDependentFunction(void (*mappedFunction)(Request &,Response &,ApplicationLevelContainer &),ApplicationLevelContainer *applicationLevelContainer);
void doService(Request &,Response &);
};

#endif
