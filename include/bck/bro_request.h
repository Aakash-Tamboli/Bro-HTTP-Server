#ifndef __BRO_REQUEST__
#define __BRO_REQUEST__ 14

#include<bro.h>
#include<bro_container.h>
#include<bro_stringifyable.h>
#include<bro_cookie.h>
#include<bro_utilities.h>
class Request:public Container
{
private:
map<string,string> dataMap;
string _forwardTo;
char *method;
char *requestURI;
char *httpVersion;
map<string,string> &headerFieldsMap;
Request(char *,char *,char *,char *,map<string,string> &);
string forwardToWhichResource();
bool isToBeForwarded();
void createDataMap(char *,map<string,string> &);
map<string,string> varMap;
public:
void setCHTMLVariable(string,string);
void setCHTMLVariable(string,Stringifyable *);
void setCHTMLVariable(string,const char *);
void setCHTMLVariable(string,short);
void setCHTMLVariable(string,unsigned short int);
void setCHTMLVariable(string,int);
void setCHTMLVariable(string,unsigned int);
void setCHTMLVariable(string,long int);
void setCHTMLVariable(string,unsigned long int);
void setCHTMLVariable(string,long long int);
void setCHTMLVariable(string,unsigned long long int);
void setCHTMLVariable(string,float);
void setCHTMLVariable(string,double);
void setCHTMLVariable(string,long double);
void setCHTMLVariable(string,char);
void setCHTMLVariable(string,unsigned char);
void setCHTMLVariable(string,bool);
string getCHTMLVariable(string);
bool isCHTMLVariablecontains(string);
string operator[](string);
void forwardTo(string);
string getCookieValue(string);
void getCookies(list<Cookie> &);
void getCookieNames(list<string> &);
friend class Bro;
};
#endif
