#include <bro_request.h>
Request::Request(char *method, char *requestURI, char *httpVersion, char *dataInRequest, map<string, string> &headerFieldsMap) : headerFieldsMap(headerFieldsMap)
{
    this->method = method;
    this->requestURI = requestURI;
    this->httpVersion = httpVersion;
    if (dataInRequest != NULL && strcmp(method, "get") == 0)
    {
        createDataMap(dataInRequest, dataMap);
    }
}

string Request::forwardToWhichResource()
{
    return this->_forwardTo;
}

bool Request::isToBeForwarded()
{
    return this->_forwardTo.length() > 0;
}

void Request::createDataMap(char *str, map<string, string> &dataMap)
{
    char *ptr1, *ptr2;
    char *decoded;
    int keyLength, valueLength;
    ptr1 = str;
    ptr2 = str;
    while (true)
    {
        while (*ptr2 != '\0' && *ptr2 != '=')
            ptr2++;
        if (*ptr2 == '\0')
            return;
        *ptr2 = '\0';
        keyLength = ptr2 - ptr1;
        decoded = new char[keyLength + 1];
        BroUtilities::decodePercentEncoding(ptr1, decoded);
        string key = string(decoded);
        delete[] decoded;
        ptr1 = ptr2 + 1;
        ptr2 = ptr1;
        while (*ptr2 != '\0' && *ptr2 != '&')
            ptr2++;
        if (*ptr2 == '\0')
        {
            valueLength = ptr2 - ptr1;
            decoded = new char[valueLength + 1];
            BroUtilities::decodePercentEncoding(ptr1, decoded);
            dataMap.insert(pair<string, string>(key, string(decoded)));
            delete[] decoded;
            break;
        }
        else
        {
            *ptr2 = '\0';
            valueLength = ptr2 - ptr1;
            decoded = new char[valueLength + 1];
            BroUtilities::decodePercentEncoding(ptr1, decoded);
            dataMap.insert(pair<string, string>(key, string(decoded)));
            delete[] decoded;
            ptr1 = ptr2 + 1;
            ptr2 = ptr1;
        }
    } // loop closing
}
void Request::setCHTMLVariable(string key, string value)
{
    varMap.insert(pair<string, string>(key, value));
}
void Request::setCHTMLVariable(string key, Stringifyable *stringifyable)
{
    string value;
    if (stringifyable == NULL)
        value = "";
    else
        value = stringifyable->stringify();
    varMap.insert(pair<string, string>(key, value));
}
void Request::setCHTMLVariable(string key, const char *value)
{
    string data;
    if (value == NULL)
        data = "";
    else
        data = value;
    varMap.insert(pair<string, string>(key, data));
}
void Request::setCHTMLVariable(string key, short value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, unsigned short int value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, int value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, unsigned int value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, long int value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, unsigned long int value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, long long int value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, unsigned long long int value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, float value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, double value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, long double value)
{
    varMap.insert(pair<string, string>(key, to_string(value)));
}
void Request::setCHTMLVariable(string key, char value)
{
    string data;
    data += value;
    varMap.insert(pair<string, string>(key, data));
}
void Request::setCHTMLVariable(string key, unsigned char value)
{
    string data;
    data += value;
    varMap.insert(pair<string, string>(key, data));
}
void Request::setCHTMLVariable(string key, bool value)
{
    string data;
    if (value == true)
        data = "true";
    else
        data = "false";
    varMap.insert(pair<string, string>(key, data));
}

string Request::getCHTMLVariable(string name)
{
    auto a = varMap.find(name);
    if (a == varMap.end())
        return string("");
    return a->second;
}

bool Request::isCHTMLVariablecontains(string name)
{
    return varMap.find(name) != varMap.end();
}

string Request::operator[](string key)
{
    auto iterator = dataMap.find(key);
    if (iterator == dataMap.end())
    {
        return string("");
    }
    return iterator->second;
}
void Request::forwardTo(string _forwardTo)
{
    this->_forwardTo = _forwardTo;
}
string Request::getCookieValue(string name)
{
    auto fields = headerFieldsMap.find("cookie");
    if (fields == headerFieldsMap.end())
        return string("");
    string cookiesString = fields->second;
    char *ptr = (char *)cookiesString.c_str();
    char *found = strstr(ptr, name.c_str());
    char *startingPoint, *endingPoint;
    if (found == NULL)
        return string("");
    while (*found != '=')
        found++;
    found++;
    startingPoint = found;
    while (*found && *found != ';')
        found++;
    endingPoint = found - 1;
    string value(startingPoint, endingPoint - startingPoint + 1);
    return value;
}
