#ifndef __BRO_COOKIE__
#define __BRO_COOKIE__ 12

#include <bro_global.h>
#include <bro_gmt_date_time.h>

typedef enum _cookie_sam_site_flag
{
    COOKIE_SAME_SITE_FLAG_NONE,
    COOKIE_SAME_SITE_FLAG_LAX,
    COOKIE_SAME_SITE_FLAG_STRICT
} COOKIE_SAME_SITE_FLAG;

class Cookie
{
private:
    string name;
    string value;
    string expiresOn;
    long maxAge;
    string domain;
    string path;
    bool isSecure;
    bool isHttpOnly;
    COOKIE_SAME_SITE_FLAG sameSiteFlag;

public:
    Cookie(string, string);
    string getName();
    string getValue();
    void setExpiresOn(GMTDateTime &);
    string getExpiresOn();
    void setMaxAgeInSeconds(int);
    void setMaxAgeInMinutes(int);
    void setMaxAgeInHours(int);
    void setDomain(string);
    string getDomain();
    void setPath(string);
    string getPath();
    void setSecure(bool);
    bool getSecure();
    void setHttpOnly(bool);
    bool getHttpOnly();
};

#endif
