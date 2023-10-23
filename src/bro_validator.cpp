#include<bro_validator.h>
#include<bro_file_system_utility.h>

Validator::Validator()
{
}
bool Validator::isValidMIMEType(string &mimeType)
{
// do nothing, right now
return true;
}
bool Validator::isValidPath(string &path)
{
return FileSystemUtility::directoryExists(path.c_str());
}
bool Validator::isValidURLFormat(string &url)
{
// do nothing, right now
return true;
}
