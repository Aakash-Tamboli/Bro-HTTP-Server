#ifndef __BRO_RESPONSE__
#define __BRO_RESPONSE__ 15

#include<bro.h>
#include<bro_cookie.h>
#include<bro_validator.h>
class Response
{
private:
set<string> cookies;
unsigned int cookiesDataLength;
string contentType;
forward_list<string> content;
forward_list<string>::iterator contentIterator;
unsigned long contentLength;
public:
Response();
~Response();
void setContentType(string);
void addCookie(Cookie &);
Response & operator<<(Cookie &);
Response & operator<<(string);
friend class HttpResponseUtility;
};

#endif
