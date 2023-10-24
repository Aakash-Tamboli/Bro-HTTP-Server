#include<bro_request_processor.h>

void requestProcessor(int clientSocketDescriptor,Bro *bro,BroThreadWrapper *p)
{
char requestBuffer[4097];
int requestLength;
int i;

requestLength=recv(clientSocketDescriptor,requestBuffer,sizeof(requestBuffer)-sizeof(char),0);
if(requestLength==0 || requestLength==-1)
{
close(clientSocketDescriptor);
p->hasCompleted=true;
return;
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
p->hasCompleted=true;
return;
}
requestBuffer[i]='\0';
i++;
if(requestBuffer[i]==' ' || requestBuffer[i]=='\0')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
p->hasCompleted=true;
return;
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
p->hasCompleted=true;
return;
}
requestURI=requestBuffer+i;
while(requestBuffer[i] && requestBuffer[i]!=' ') i++;
if(requestBuffer[i]=='\0')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
p->hasCompleted=true;
return;
}
requestBuffer[i]='\0';
i++;
if(requestBuffer[i]==' ' || requestBuffer[i]=='\0')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
p->hasCompleted=true;
return;
}
httpVersion=requestBuffer+i;
while(requestBuffer[i] && requestBuffer[i]!='\r' && requestBuffer[i]!='\n') i++;
if(requestBuffer[i]=='\0')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
p->hasCompleted=true;
return;
}

if(requestBuffer[i]=='\r' && requestBuffer[i+1]!='\n')
{
HttpErrorStatusUtility::sendBadRequestError(clientSocketDescriptor);
close(clientSocketDescriptor);
p->hasCompleted=true;
return;
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
p->hasCompleted=true;
return;
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
auto urlMappingsIterator=bro->urlMappings.find(requestURI);
if(urlMappingsIterator==bro->urlMappings.end())
{
if(bro->isCHTML(requestURI))
{
map<string,string> headerFieldsMap;
HeaderUtility::parseHeader(requestBuffer+headerStartIndex,headerFieldsMap);
Request request(method,requestURI,httpVersion,dataInRequest,headerFieldsMap);
bro->processCHTMLResource(clientSocketDescriptor,requestURI,request);
}else if(!(bro->serveStaticResourcesFolder(clientSocketDescriptor,requestURI)))
{
HttpErrorStatusUtility::sendNotFoundError(clientSocketDescriptor,requestURI);
}
close(clientSocketDescriptor);
p->hasCompleted=true;
return;
}

URLMapping urlMapping=urlMappingsIterator->second;

if(urlMapping.requestMethod==__GET__ && strcmp(method,"get")!=0)
{
HttpErrorStatusUtility::sendMethodNotAllowedError(clientSocketDescriptor,requestURI);
close(clientSocketDescriptor);
p->hasCompleted=true;
return;
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
urlMappingsIterator=bro->urlMappings.find(forwardTo);
if(urlMappingsIterator==bro->urlMappings.end())
{
if(bro->isCHTML(forwardTo.c_str()))
{
request.forwardTo(string(""));
cout<<"forward to: "<<forwardTo<<endl;
bro->processCHTMLResource(clientSocketDescriptor,forwardTo.c_str(),request);
}
else if(!(bro->serveStaticResourcesFolder(clientSocketDescriptor,forwardTo.c_str())))
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
p->hasCompleted=true;
// lot of code will be written here later on
} // function ends

