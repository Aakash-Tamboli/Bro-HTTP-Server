#include <bro_application_level_container_dependent_startup_function.h>

ApplicationLevelContainerDependentStartupFunction::ApplicationLevelContainerDependentStartupFunction(int priorityNumber, void (*startupFunction)(ApplicationLevelContainer &), ApplicationLevelContainer *p2ApplicationLevelContainer)
{
    this->priorityNumber = priorityNumber;
    this->startupFunction = startupFunction;
    this->p2ApplicationLevelContainer = p2ApplicationLevelContainer;
}
void ApplicationLevelContainerDependentStartupFunction::run()
{
    startupFunction(*p2ApplicationLevelContainer);
}
int ApplicationLevelContainerDependentStartupFunction::getPriorityNumber()
{
    return this->priorityNumber;
}
