#include<iostream>
#include<map>
#include<forward_list>
#include<unistd.h>
#include<string.h>
#include<sys/stat.h>
#include<bits/stdc++.h>

#ifdef _WIN32
#include<windows.h>
#endif

#ifdef linux
#include<arpa/inet.h>
#include<sys/socket.h>
#endif
using namespace std;

#define _forward_to(request,url) \
request.forwardTo(url); \
return;

// Aakash Who Create web server

enum __container_operation_failure_reason__ {__KEY_EXISTS__,__KEY_DOES_NOT_EXIST__,__OUT_OF_MEMORY__,__VALUE_SIZE_MISMATCH__};

class Container
{
private:
typedef struct _bag
{
void *ptr;
int size;
}Bag;
map<string,Bag> dataSet;
public:
template<class T>
void set(string keyName,T something,bool *success,__container_operation_failure_reason__ *reason)
{
auto iterator=dataSet.find(keyName);
if(iterator!=dataSet.end())
{
if(reason) *reason=__KEY_EXISTS__;
if(success) *success=false;
return;
}
void *ptr;
ptr=malloc(sizeof(something));
if(ptr==NULL)
{
if(reason) *reason=__OUT_OF_MEMORY__;
if(success) *success=false;
return;
}
memcpy(ptr,&something,sizeof(something));
Bag bag;
bag.ptr=ptr;
bag.size=sizeof(something);
dataSet.insert(pair<string,Bag>(keyName,bag));
if(success) *success=true;
}
template<class T>
void get(string keyName,T anything,bool *success,__container_operation_failure_reason__ *reason)
{
auto iterator=dataSet.find(keyName);
if(iterator==dataSet.end())
{
if(reason) *reason=__KEY_DOES_NOT_EXIST__;
if(success) *success=false;
return;
}
Bag bag;
bag=iterator->second;
if(bag.size!=sizeof(*anything))
{
if(reason) *reason=__VALUE_SIZE_MISMATCH__;
if(success) *success=false;
return;
}
memcpy(anything,bag.ptr,sizeof(*anything));
if(success) *success=true;
}
template<class T>
void remove(string keyName,T anything,bool *success,__container_operation_failure_reason__ *reason)
{
auto iterator=dataSet.find(keyName);
if(iterator==dataSet.end())
{
if(reason) *reason=__KEY_DOES_NOT_EXIST__;
if(success) *success=false;
return;
}
Bag bag;
bag=iterator->second;
if(bag.size!=sizeof(anything))
{
if(reason) *reason=__VALUE_SIZE_MISMATCH__;
if(success) *success=false;
return;
}
memcpy(anything,bag.ptr,sizeof(*anything));
free(bag.ptr);
if(success) *success=true;
}
bool contains(string keyName)
{
auto iterator=dataSet.find(keyName);
return iterator!=dataSet.end();
}
};

class ApplicationLevelContainer:public Container
{
// right now not yet decided
};


class BroUtilities
{
private:
BroUtilities(){}
public:
static bool isHexChar(char c)
{
if(c>='0' && c<='9') return true;
if(c>='a' && c<='f') return true;
if(c>='A' && c<='F') return true;
return false;
}

static void decodePercentEncoding(char *encodedString,char *decodedString)
{
int i,decodedAscii;
i=0;
while(*encodedString!='\0')
{
if(*encodedString=='+')
{
decodedString[i]=' ';
i++;
encodedString++;
continue;
}
if(*encodedString!='%')
{
decodedString[i]=*encodedString;
i++;
encodedString++;
continue;
}
encodedString++;
if(isHexChar(*encodedString) && isHexChar(*(encodedString+1)))
{
sscanf(encodedString,"%2x",&decodedAscii);
decodedString[i]=decodedAscii;
i++;
encodedString+=2;
}
else
{
i=0;
break;
}
}// loop ends
decodedString[i]='\0';
}

static void loadMIMETypes(map<string,string> &mimeTypesMap)
{
FILE *file;
file=fopen("bro-data/mime.types","r");
if(file==NULL) return;
char *mimeType;
char *extension;
char line[200];
int x;


while(true)
{
fgets(line,200,file);
if(feof(file)) break;
if(line[0]=='#') continue;
// logic to remove \r\n or \n from end of the string starts here
x=strlen(line)-1;
while(true)
{
if(line[x]=='\r' || line[x]=='\n')
{
line[x]='\0';
x--;
}
else
{
break;
}
}
// logic to remove \r\n or \n from end of the string ends here
mimeType=&line[0];
for(x=0;line[x]!='\t';x++);
line[x]='\0';
x++;
while(line[x]=='\t') x++;

while(true)
{
extension=&line[x];
while(line[x]!='\0' && line[x]!=' ') x++;
if(line[x]=='\0')
{
// add entry to map and break the loop
mimeTypesMap.insert(pair<string,string>(string(extension),string(mimeType)));
// cout<<extension<<"  , "<<mimeType<<endl;
break;
}
else
{
// placing \0 on xth index,add entry to map and increment the value of x
line[x]='\0';
mimeTypesMap.insert(pair<string,string>(string(extension),string(mimeType)));
//cout<<extension<<"  , "<<mimeType<<endl;
x++;
}
}// parsing loop ends here
}// extrating and insert in map loop ends
fclose(file);
}
};

class FileSystemUtility
{
private:
FileSystemUtility(){}
public:
static bool fileExists(const char *path)
{
struct stat s;
int x;
x=stat(path,&s);
if(x!=0) return false;
if(s.st_mode & S_IFDIR) return false;
return true;
}
static bool directoryExists(const char *path)
{
struct stat s;
int x;
x=stat(path,&s);
if(x!=0) return false;
if(s.st_mode & S_IFDIR) return true;
else return false;
}
static string getFileExtension(const char *path)
{
int x;
x=strlen(path)-1;
while(x>=0 && path[x]!='.') x--;
if(x==-1 || path[x]!='.') return string("");
return string(path+(x+1));
}
};

class StringUtility
{
private:
StringUtility(){}
public:
static void toLowerCase(char *str)
{
if(str==NULL) return;
for(;*str;str++) if(*str>=65 && *str<=90) *str+=32;
}
};

class HttpErrorStatusUtility
{
private:
HttpErrorStatusUtility(){}
public:
static void sendBadRequestError(int clientSocketDescriptor)
{
// will complete later on
}

static void sendHttpVersionNotSupportedError(int clientSocketDescriptor,char *httpVersion)
{
// will complete later on
}

static void sendNotFoundError(int clientSocketDescriptor,char *requestURI)
{
// we will optmize this code later on
char content[1000];

char header[200];

char response[1200];

sprintf(content,"<!DOCTYPE HTML><html><head><meta charset='utf-8'><title>404 Not Found</title></head><body>Requested Resourse [%s] Not Found</body></html>",requestURI);

int contentLength=strlen(content);

sprintf(header,"HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length:%d\r\nConnection: close\r\n\r\n",contentLength);

strcpy(response,header);
strcat(response,content);

send(clientSocketDescriptor,response,strlen(response),0);

}

static void sendMethodNotAllowedError(int clientSocketDescriptor,char *method)
{
// will complete later on
}

};

class Validator
{
private:
Validator(){ }
public:
static bool isValidMIMEType(string &mimeType)
{
// do nothing, right now
return true;
}
static bool isValidPath(string &path)
{
return FileSystemUtility::directoryExists(path.c_str());
}
static bool isValidURLFormat(string &url)
{
// do nothing, right now
return true;
}
};

class Error
{
private:
string error;
public:
Error(string error)
{
this->error=error;
}
bool hasError()
{
return this->error.length()>0;
}
string getError()
{
return this->error;
}
};
class Request
{
private:
map<string,string> dataMap;
string _forwardTo;
char *method;
char *requestURI;
char *httpVersion;
Request(char *method,char *requestURI,char *httpVersion,char *dataInRequest)
{
this->method=method;
this->requestURI=requestURI;
this->httpVersion=httpVersion;
if(dataInRequest!=NULL && strcmp(method,"get")==0)
{
createDataMap(dataInRequest,dataMap);
}
}

string forwardToWhichResource()
{
return this->_forwardTo;
}

bool isToBeForwarded()
{
return this->_forwardTo.length()>0;
}

void createDataMap(char *str,map<string,string> &dataMap)
{
char *ptr1,*ptr2;
char *decoded;
int keyLength,valueLength;
ptr1=str;
ptr2=str;
while(true)
{
while(*ptr2!='\0' && *ptr2!='=') ptr2++;
if(*ptr2=='\0') return;
*ptr2='\0';
keyLength=ptr2-ptr1;
decoded=new char[keyLength+1];
BroUtilities::decodePercentEncoding(ptr1,decoded);
string key=string(decoded);
delete [] decoded;
ptr1=ptr2+1;
ptr2=ptr1;
while(*ptr2!='\0' && *ptr2!='&') ptr2++;
if(*ptr2=='\0')
{
valueLength=ptr2-ptr1;
decoded=new char[valueLength+1];
BroUtilities::decodePercentEncoding(ptr1,decoded);
dataMap.insert(pair<string,string>(key,string(decoded)));
delete [] decoded;
break;
}
else
{
*ptr2='\0';
valueLength=ptr2-ptr1;
decoded=new char[valueLength+1];
BroUtilities::decodePercentEncoding(ptr1,decoded);
dataMap.insert(pair<string,string>(key,string(decoded)));
delete [] decoded;
ptr1=ptr2+1;
ptr2=ptr1;
}
}// loop closing
}


friend class Bro;

public:
string operator[](string key)
{
auto iterator=dataMap.find(key);
if(iterator==dataMap.end())
{
return string("");
}
return iterator->second;
}
void forwardTo(string _forwardTo)
{
this->_forwardTo=_forwardTo;
}
};

class Response
{
private:
string contentType;
forward_list<string> content;
forward_list<string>::iterator contentIterator;
unsigned long contentLength;
public:
Response()
{
this->contentLength=0;
this->contentIterator=this->content.before_begin();
}
~Response()
{
// not yet decided
}
void setContentType(string contentType)
{
if(Validator::isValidMIMEType(contentType))
{
this->contentType=contentType;
}
}
Response & operator<<(string content)
{
this->contentLength+=content.length();
this->contentIterator=this->content.insert_after(this->contentIterator,content);
return *this;
}

friend class HttpResponseUtility;

};

class HttpResponseUtility
{
private:
HttpResponseUtility(){}
public:
static void sendResponse(int clientSocketDescriptor,Response &response)
{
char header[200];
int contentLength=response.contentLength;
sprintf(header,"HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length: %d\r\nConnection: close\r\n\r\n",contentLength);
send(clientSocketDescriptor,header,strlen(header),0);
auto contentIterator=response.content.begin();

while(contentIterator!=response.content.end())
{
string str=*contentIterator;
send(clientSocketDescriptor,str.c_str(),str.length(),0);
++contentIterator;
}
}
};



enum __request_method__{__GET__,__POST__,__PUT__,__DELETE__,__CONNECT__,__TRACE__,__HEAD__,__OPTIONS__};

class Function
{
public:
virtual void doService(Request &,Response &)=0;
};

class SimpleFunction:public Function
{
private:
void (*mappedFunction)(Request &,Response &);
public:
SimpleFunction(void (*mappedFunction)(Request &,Response &))
{
this->mappedFunction=mappedFunction;
}
void doService(Request &request,Response &response)
{
this->mappedFunction(request,response);
}
};


class ApplicationLevelContainerDependentFunction:public Function
{
private:
void (*mappedFunction)(Request &,Response &,ApplicationLevelContainer &);
ApplicationLevelContainer *applicationLevelContainer;
public:
ApplicationLevelContainerDependentFunction(void (*mappedFunction)(Request &,Response &,ApplicationLevelContainer &),ApplicationLevelContainer *applicationLevelContainer)
{
this->mappedFunction=mappedFunction;
this->applicationLevelContainer=applicationLevelContainer;
}
void doService(Request &request,Response &response)
{
this->mappedFunction(request,response,*this->applicationLevelContainer);
}
};


typedef struct __url__mapping
{
__request_method__ requestMethod;
Function *function;
//void (*mappedFunction) (Request &,Response &);
}URLMapping;



class Bro
{
private:
string staticResourcesFolder;
map<string,URLMapping> urlMappings;
map<string,string> mimeTypes;
ApplicationLevelContainer applicationLevelContainer;
public:
Bro()
{
BroUtilities::loadMIMETypes(mimeTypes);
if(mimeTypes.size()==0) throw string("bro-data folder has been temperaed with");
}
~Bro()
{
// not yet, implemented
}
void setStaticResourcesFolder(string staticResourcesFolder)
{
if(Validator::isValidPath(staticResourcesFolder))
{
this->staticResourcesFolder=staticResourcesFolder;
}
else
{
string exception=string("Invalid static Resource Folder Path: ")+string(staticResourcesFolder);
throw exception;
}
}

void get(string url,void (*callBack)(Request &,Response &))
{
if(Validator::isValidURLFormat(url))
{
Function *function;
URLMapping u;
u.requestMethod=__GET__;
function=new SimpleFunction(callBack);
u.function=function;
this->urlMappings.insert(pair<string,URLMapping>(url,u));
}
}

void get(string url,void (*callBack)(Request &,Response &,ApplicationLevelContainer &))
{
if(Validator::isValidURLFormat(url))
{
Function *function;
URLMapping u;
u.requestMethod=__GET__;
function=new ApplicationLevelContainerDependentFunction(callBack,&(this->applicationLevelContainer));
u.function=function;
this->urlMappings.insert(pair<string,URLMapping>(url,u));
}
}

void post(string url,void (*callBack)(Request &,Response &))
{
if(Validator::isValidURLFormat(url))
{
Function *function;
URLMapping u;
u.requestMethod=__POST__;
function=new SimpleFunction(callBack);
u.function=function;
this->urlMappings.insert(pair<string,URLMapping>(url,u));
}
}


bool serveStaticResourcesFolder(int clientSocketDescriptor,const char *requestURI)
{
if(this->staticResourcesFolder.length()==0) return false;
if(!FileSystemUtility::directoryExists(this->staticResourcesFolder.c_str())) return false;

string resourcePath=this->staticResourcesFolder+string(requestURI);
if(!FileSystemUtility::fileExists(resourcePath.c_str())) return false;
cout<<"Looking is Resources Folder: "<<resourcePath<<endl;
FILE *file=fopen(resourcePath.c_str(),"rb");
if(file==NULL) return false; // if OS does'nt allow to access file for security reasons

long fileSize;

fseek(file,0,SEEK_END);

fileSize=ftell(file);

if(fileSize==0)
{
fclose(file);
return false;
}

rewind(file); // to move the internal pointer to start of the file

string extension,mimeType;
extension=FileSystemUtility::getFileExtension(resourcePath.c_str());
if(extension.length()>0)
{
transform(extension.begin(),extension.end(),extension.begin(),::tolower);
auto mimeTypesIterator=mimeTypes.find(extension);
if(mimeTypesIterator!=mimeTypes.end())
{
mimeType=mimeTypesIterator->second;
}
else
{
mimeType=string("text/html");
}
}
else
{
mimeType=string("text/html");
}

char header[200];
sprintf(header,"HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n",mimeType.c_str(),fileSize);

send(clientSocketDescriptor,header,strlen(header),0);

long bytesLeftToRead;
int bytesToRead;

char buffer[4096];

bytesToRead=4096;

bytesLeftToRead=fileSize;

while(bytesLeftToRead>0)
{
if(bytesLeftToRead<bytesToRead) bytesToRead=bytesLeftToRead;
fread(buffer,bytesToRead,1,file);
if(feof(file)) break; // it won't happen in our case but its good practice
send(clientSocketDescriptor,buffer,bytesToRead,0);
bytesLeftToRead=bytesLeftToRead-bytesToRead;
} // loop ends
fclose(file);
return true;
}

void listen(int portNumber,void (*callBack)(Error &))
{
#ifdef _WIN32
WSADATA wsaData;
Word ver;
ver=MAKEWORD(1,1);
WSAStartup(ver,&wsaData);
#endif
int serverSocketDescriptor;
char requestBuffer[4097];
int requestLength;
int i;

serverSocketDescriptor=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(serverSocketDescriptor<0)
{
#ifdef _WIN32
WSACleanup();
#endif
Error error("Unable to create Socket");
callBack(error);
return;
}

struct sockaddr_in serverSocketInformation;
serverSocketInformation.sin_family=AF_INET;
serverSocketInformation.sin_port=htons(portNumber);
serverSocketInformation.sin_addr.s_addr=htonl(INADDR_ANY);
int successCode=bind(serverSocketDescriptor,(struct sockaddr *)&serverSocketInformation,sizeof(serverSocketInformation));
if(successCode<0)
{
close(serverSocketDescriptor);
#ifdef _WIN32
WSACleanup();
#endif
char a[101];
sprintf(a,"Unable to bind socket to port: %d",portNumber);
Error error(a);
callBack(error);
return;
}

successCode=::listen(serverSocketDescriptor,10);
if(successCode<0)
{
close(serverSocketDescriptor);
#ifdef _WIN32
WSACleanup();
#endif
Error error("Unable to accept client connection");
callBack(error);
return;
}
Error error("");
callBack(error);
struct sockaddr_in clientSocketInformation;
#ifdef linux
socklen_t len=sizeof(clientSocketInformation);
#endif
#ifdef _WIN32
int len=sizeof(clientSocketInformation);
#endif

int clientSocketDescriptor;

while(true)
{
clientSocketDescriptor=accept(serverSocketDescriptor,(struct sockaddr *)&clientSocketInformation,&len);
requestLength=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer)-sizeof(char),0);
if(requestLength==0 || requestLength==-1)
{
close(clientSocketDescriptor);
continue;
}
char *method,*requestURI,*httpVersion,*dataInRequest;
requestBuffer[requestLength]='\0';
// code to parse the first line of the http request start here
// first line should be REQUOEST_METHOD SPACE URI SPACE HTTPVERSIONCRLF
method=requestBuffer;
i=0;
while(requestBuffer[i] && requestBuffer[i]!=' ') i++;
if(requestBuffer[i]=='\0')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
continue;
}
requestBuffer[i]='\0';
i++;
if(requestBuffer[i]==' ' || requestBuffer[i]=='\0')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
continue;
}
StringUtility::toLowerCase(method);
if(!(strcmp(method,"get")==0 ||
strcmp(method,"post")==0 ||
strcmp(method,"put")==0 ||
strcmp(method,"delete")==0 ||
strcmp(method,"head")==0 ||
strcmp(method,"options")==0 ||
strcmp(method,"trace")==0 ||
strcmp(method,"connect")==0))
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
continue;
}
requestURI=requestBuffer+i;
while(requestBuffer[i] && requestBuffer[i]!=' ') i++;
if(requestBuffer[i]=='\0')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
continue;
}
requestBuffer[i]='\0';
i++;
if(requestBuffer[i]==' ' || requestBuffer[i]=='\0')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
continue;
}
httpVersion=requestBuffer+i;
while(requestBuffer[i] && requestBuffer[i]!='\r' && requestBuffer[i]!='\n') i++;
if(requestBuffer[i]=='\0')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
continue;
}

if(requestBuffer[i]=='\r' && requestBuffer[i+1]!='\n')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
continue;
}

if(requestBuffer[i]=='\r')
{
requestBuffer[i]='\0';
i=i+2;
}
else
{
requestBuffer[i]='\0';
i=i+1;
}
StringUtility::toLowerCase(httpVersion);
if(strcmp(httpVersion,"http/1.1")!=0)
{
HttpErrorStatusUtility::sendHttpVersionNotSupportedError(clientSocketDescriptor,httpVersion);
close(clientSocketDescriptor);
continue;
}
dataInRequest=NULL;
i=0;
while(requestURI[i]!='\0' && requestURI[i]!='?') i++;

if(requestURI[i]=='?')
{
requestURI[i]='\0';
dataInRequest=requestURI+i+1;
}
cout<<"Request Arrived url is"<<requestURI<<endl;
auto urlMappingsIterator=urlMappings.find(requestURI);
if(urlMappingsIterator==urlMappings.end())
{
if(!serveStaticResourcesFolder(clientSocketDescriptor,requestURI))
{
HttpErrorStatusUtility::sendNotFoundError(clientSocketDescriptor,requestURI);
}
close(clientSocketDescriptor);
continue;
}

URLMapping urlMapping=urlMappingsIterator->second;

if(urlMapping.requestMethod==__GET__ && strcmp(method,"get")!=0)
{
HttpErrorStatusUtility::sendMethodNotAllowedError(clientSocketDescriptor,requestURI);
close(clientSocketDescriptor);
continue;
}
// code to parse the header and then the payload if exist starts
// code to parse the header and then the payload if exist ends
Request request(method,requestURI,httpVersion,dataInRequest);

while(true)
{
Response response;
urlMapping.function->doService(request,response);
if(request.isToBeForwarded()==false)
{
HttpResponseUtility::sendResponse(clientSocketDescriptor,response);
break;
}
string forwardTo=request.forwardToWhichResource();
urlMappingsIterator=urlMappings.find(forwardTo);
if(urlMappingsIterator==urlMappings.end())
{
if(!serveStaticResourcesFolder(clientSocketDescriptor,forwardTo.c_str()))
{
HttpErrorStatusUtility::sendNotFoundError(clientSocketDescriptor,requestURI);
}
break;
}
urlMapping=urlMappingsIterator->second;
if(urlMapping.requestMethod==__GET__ and strcmp(method,"get")!=0)
{
HttpErrorStatusUtility::sendMethodNotAllowedError(clientSocketDescriptor,method);
break;
}
// some more if condition for other type of request(s).
request.forwardTo(string("")); //resting forwardTo property.
} // loop ends 

close(clientSocketDescriptor);
// lot of code will be written here later on
} // infinit loop ends

#ifdef _WIN32
WSACleanup();
#endif
}
};

// Bittu [ The Web Application Developer User of Bro Web Server ]

int main()
{
try
{
Bro bro;

bro.get("/",[](Request &request,Response &response){
response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>HOME</title>
</head>
<body>
<h1>God is Great</h1>
<a href='/begin'>Begin</a>
</body>
</html>
)"""";
response.setContentType("text/html");
});

bro.get("/begin",[](Request &request,Response &response){
response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Form</title>
</head>
<body>
<form action='/saveData'>
Name:&nbsp;
<input type='text' name='name' id='name'>
City:&nbsp;
<input type='text' name='city' id='city'>
<button type='submit'>Save</button>
</form>
</body>
</html>
)"""";
response.setContentType("text/html");
});

bro.get("/saveData",[](Request &request,Response &response,ApplicationLevelContainer &container){
cout<<"Data is Processing"<<endl;
string *name,*city;

name=new string(request["name"]);
city=new string(request["city"]);
container.set("name",&name,NULL,NULL);
container.set("city",&city,NULL,NULL);
// request Forwarded
_forward_to(request,"/saveData2");
});


bro.get("/saveData2",[](Request &request,Response &response,ApplicationLevelContainer &container){
string *nm,*ct;
container.remove("name",&nm,NULL,NULL);
container.remove("city",&ct,NULL,NULL);
cout<<"Name: "<<*nm<<endl;
cout<<"City: "<<*ct<<endl;
// Assume here is code for saving data in db
const char *html=R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Data Saved</title>
</head>
<body>
<h1>Data Saved</h1>
<a href='/'>Home</a>
</body>
</html>
)"""";
response<<html;
response.setContentType("text/html");
});


bro.listen(5050,[](Error &error){
if(error.hasError())
{
cout<<error.getError()<<endl;
return;
}
cout<<"Bro HTTP Server is Ready to accept Request on port 5050"<<endl;
});


}catch(string &exception)
{
cout<<exception<<endl;
}
return 0;
}
