#ifndef __BRO_APPLICATION_LEVEL_CONTAINER_DEPENDENT_STARTUP_FUNCTION__
#define __BRO_APPLICATION_LEVEL_CONTAINER_DEPENDENT_STARTUP_FUNCTION__ 25

#include <bro_global.h>
#include <bro_application_level_container.h>
#include <bro_startup_function.h>

class ApplicationLevelContainerDependentStartupFunction : public StartupFunction
{
private:
    int priorityNumber;
    void (*startupFunction)(ApplicationLevelContainer &);
    ApplicationLevelContainer *p2ApplicationLevelContainer;

public:
    ApplicationLevelContainerDependentStartupFunction(int, void (*startupFunction)(ApplicationLevelContainer &), ApplicationLevelContainer *);
    void run();
    int getPriorityNumber();
};

#endif
