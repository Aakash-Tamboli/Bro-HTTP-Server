#ifndef __BRO_FILE_SYSTEM_UTILITY__
#define __BRO_FILE_SYSTEM_UTILITY__ 7
#include<bro_global.h>

class FileSystemUtility
{
private:
FileSystemUtility();
public:
static bool createDirectory(const char *);
static unsigned int getLastUpdatedTime(const char *);
static bool fileExists(const char *);
static bool directoryExists(const char *);
static string getFileExtension(const char *);
};

#endif
