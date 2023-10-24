#ifndef __BRO__
#define __BRO__ 40

#include<bro_application_level_container_dependent_function.h>
#include<bro_application_level_container_dependent_startup_function.h>
#include<bro_application_level_container.h>
#include<bro_container.h>
#include<bro_cookie.h>
#include<bro_error.h>
#include<bro_file_system_utility.h>
#include<bro_gmt_date_time.h>
#include<bro.h>
#include<bro_header_utility.h>
#include<bro_http_error_status_utility.h>
#include<bro_http_response_utility.h>
#include<bro_request.h>
#include<bro_response.h>
#include<bro_service_function.h>
#include<bro_simple_function.h>
#include<bro_simple_startup_function.h>
#include<bro_startup_function_comparator.h>
#include<bro_startup_function.h>
#include<bro_stringifyable.h>
#include<bro_string_utility.h>
#include<bro_template_engine.h>
#include<bro_utilities.h>
#include<bro_validator.h>


class Bro
{
private:
string staticResourcesFolder;
map<string,URLMapping> urlMappings;
map<string,string> mimeTypes;
ApplicationLevelContainer applicationLevelContainer;
priority_queue<StartupFunction *,vector<StartupFunction *>,StartupFunctionComparator> startupFunctions;
bool isCHTML(const char *);
public:
Bro();
~Bro();
void setStaticResourcesFolder(string);
void addStartupService(int,void (*startupFunction)(void));
void addStartupService(int,void (*startupFunction)(ApplicationLevelContainer &));
void get(string,void (*callBack)(Request &,Response &));
void get(string,void (*callBack)(Request &,Response &,ApplicationLevelContainer &));
void post(string,void (*callBack)(Request &,Response &));
void processCHTMLResource(int,const char *,Request &);
bool serveStaticResourcesFolder(int,const char *);
void listen(int,void (*callBack)(Error &));
};

#endif
