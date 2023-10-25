#include <bro_validator.h>
#include <bro_file_system_utility.h>
#include <bro.h>

Validator::Validator()
{
}
bool Validator::isValidPath(string &path)
{
    return FileSystemUtility::directoryExists(path.c_str());
}
bool Validator::isValidURLFormat(string &url)
{
	if(url[0]!='/' || url[1]=='/')
	{
		return false;
	}
    return true;
}
