#include <bro_application_level_container_dependent_function.h>

ApplicationLevelContainerDependentFunction::ApplicationLevelContainerDependentFunction(void (*mappedFunction)(Request &, Response &, ApplicationLevelContainer &), ApplicationLevelContainer *applicationLevelContainer)
{
    this->mappedFunction = mappedFunction;
    this->applicationLevelContainer = applicationLevelContainer;
}
void ApplicationLevelContainerDependentFunction::doService(Request &request, Response &response)
{
    this->mappedFunction(request, response, *this->applicationLevelContainer);
}
