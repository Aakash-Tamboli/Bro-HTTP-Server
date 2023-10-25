#ifndef __BRO_TEMPLATE_ENGINE__
#define __BRO_TEMPLATE_ENGINE__ 40

#include <bro_global.h>
#include <bro_request.h>
#include <bro_file_system_utility.h>
class TemplateEngine
{
private:
    struct VMD
    {
        long start_position;
        long end_position;
        char var_name[256];
    };
    static void createVMDFileName(const char *, char *);
    static void createVMDFile(const char *, const char *);

public:
    static void processCHTMLFile(const char *, Request &, int);
};

#endif
