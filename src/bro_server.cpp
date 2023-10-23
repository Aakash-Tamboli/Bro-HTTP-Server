#include<bro_server.h>

bool Bro::isCHTML(const char *requestURI)
{
// a.chtml I will check in-case sensitive
int len=strlen(requestURI);
if(len<7) return false;
const char *ptr1=requestURI+len-6;
char lastPart[7]={".chtml"};
const char *ptr2=lastPart;
char a,b;
while(*ptr1 && *ptr2)
{
a=*ptr1;
b=*ptr2;
if(a>=97 && a<=122) a=a-32;
if(b>=97 && b<=122) b=b-32;
if(a!=b) return false;
ptr1++;
ptr2++;
}
return true;
}
Bro::Bro()
{
BroUtilities::loadMIMETypes(mimeTypes);
if(mimeTypes.size()==0) throw string("bro-data folder has been temperaed with");
}
Bro::~Bro()
{
// not yet, implemented
}
void Bro::setStaticResourcesFolder(string staticResourcesFolder)
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

void Bro::addStartupService(int priorityNumber,void (*startupFunction)(void))
{
StartupFunction *sf;
sf=new SimpleStartupFunction(priorityNumber,startupFunction);
startupFunctions.push(sf);
}

void Bro::addStartupService(int priorityNumber,void (*startupFunction)(ApplicationLevelContainer &))
{
StartupFunction *sf;
sf=new ApplicationLevelContainerDependentStartupFunction(priorityNumber,startupFunction,&(this->applicationLevelContainer));
startupFunctions.push(sf);
}


void Bro::get(string url,void (*callBack)(Request &,Response &))
{
if(Validator::isValidURLFormat(url))
{
ServiceFunction *serviceFunction;
URLMapping u;
u.requestMethod=__GET__;
serviceFunction=new SimpleFunction(callBack);
u.function=serviceFunction;
this->urlMappings.insert(pair<string,URLMapping>(url,u));
}
}

void Bro::get(string url,void (*callBack)(Request &,Response &,ApplicationLevelContainer &))
{
if(Validator::isValidURLFormat(url))
{
ServiceFunction *serviceFunction;
URLMapping u;
u.requestMethod=__GET__;
serviceFunction=new ApplicationLevelContainerDependentFunction(callBack,&(this->applicationLevelContainer));
u.function=serviceFunction;
this->urlMappings.insert(pair<string,URLMapping>(url,u));
}
}

void Bro::post(string url,void (*callBack)(Request &,Response &))
{
if(Validator::isValidURLFormat(url))
{
ServiceFunction *serviceFunction;
URLMapping u;
u.requestMethod=__POST__;
serviceFunction=new SimpleFunction(callBack);
u.function=serviceFunction;
this->urlMappings.insert(pair<string,URLMapping>(url,u));
}
}

void Bro::processCHTMLResource(int clientSocketDescriptor,const char *requestURI,Request &request)
{
if(this->staticResourcesFolder.length()==0)
{
// send Back 404
return;
}
if(!FileSystemUtility::directoryExists(this->staticResourcesFolder.c_str()))
{
// send Back 404
return;
}
string resourcePath=this->staticResourcesFolder+string(requestURI);
if(!FileSystemUtility::fileExists(resourcePath.c_str()))
{
// send Back 404
return;
}
TemplateEngine::processCHTMLFile(resourcePath.c_str(),request,clientSocketDescriptor);
}

bool Bro::serveStaticResourcesFolder(int clientSocketDescriptor,const char *requestURI)
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

void Bro::listen(int portNumber,void (*callBack)(Error &))
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
// code to call all startup Services starts here
StartupFunction *startupFunction;
while(!startupFunctions.empty())
{
startupFunction=startupFunctions.top();
startupFunctions.pop();
startupFunction->run();
} // loop ends
// code to call all startup Services ends here



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
// cout<<"DEBUGING: "<<endl;
// cout<<requestBuffer<<endl;
// cout<<"DEBUGING: "<<endl;
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
int headerStartIndex=i;
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
if(isCHTML(requestURI))
{
map<string,string> headerFieldsMap;
HeaderUtility::parseHeader(requestBuffer+headerStartIndex,headerFieldsMap);
Request request(method,requestURI,httpVersion,dataInRequest,headerFieldsMap);
processCHTMLResource(clientSocketDescriptor,requestURI,request);
}else if(!serveStaticResourcesFolder(clientSocketDescriptor,requestURI))
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
map<string,string> headerFieldsMap;
HeaderUtility::parseHeader(requestBuffer+headerStartIndex,headerFieldsMap);
// code to parse the header and then the payload if exist ends
Request request(method,requestURI,httpVersion,dataInRequest,headerFieldsMap);
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
if(isCHTML(forwardTo.c_str()))
{
request.forwardTo(string(""));
cout<<"forward to: "<<forwardTo<<endl;
processCHTMLResource(clientSocketDescriptor,forwardTo.c_str(),request);
}
else if(!serveStaticResourcesFolder(clientSocketDescriptor,forwardTo.c_str()))
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
