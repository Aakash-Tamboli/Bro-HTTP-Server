#include <bro_response.h>
Response::Response()
{
    this->contentLength = 0;
    this->contentIterator = this->content.before_begin();
    this->cookiesDataLength = 0;
}
Response::~Response()
{
}
void Response::setContentType(string contentType)
{
    if (Validator::isValidMIMEType(contentType))
    {
        this->contentType = contentType;
    }
}
void Response::addCookie(Cookie &cookie)
{
    string name = cookie.getName();
    if (name.length() == 0)
        return;
    string value = cookie.getValue();
    if (value.length() == 0)
        return;
    string cookieString = name + string("=") + value;
    if (cookies.find(cookieString) != cookies.end())
        return;
    this->cookiesDataLength += cookieString.length();
    this->cookiesDataLength += 12; // According to MDN Docs 12 is for "Set-Cookie: " which we have to set cookie in header
    this->cookiesDataLength += 1;
    cookies.insert(cookieString);
}

Response &Response::operator<<(Cookie &cookie)
{
    addCookie(cookie);
    return *this;
}

Response &Response::operator<<(string content)
{
    this->contentLength += content.length();
    this->contentIterator = this->content.insert_after(this->contentIterator, content);
    return *this;
}
