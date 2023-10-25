#include <bro_http_error_status_utility.h>

HttpErrorStatusUtility::HttpErrorStatusUtility()
{
}
void HttpErrorStatusUtility::sendBadRequestError(int clientSocketDescriptor)
{
    char header[200];
    char response[1200];
    const char *html = R""""(<!DOCTYPE HTML><html lan='en'><head><meta charset='utf-8'><title>400 Bad Request</title></head><body><h1>Bad Request</h1><b>For Info -</b> &emsp; <a href='https://httpwg.org/specs/rfc9110.html#status.400'>Docs</a></body></html>)"""";
    int contentLength = strlen(html);
    sprintf(header, "HTTP/1.1 400 Not Found\r\nContent-Type: text/html\r\nContent-Length:%d\r\nConnection: close\r\n\r\n", contentLength);
    strcpy(response, header);
    strcat(response, html);
    send(clientSocketDescriptor, response, strlen(response), 0);
}

void HttpErrorStatusUtility::sendHttpVersionNotSupportedError(int clientSocketDescriptor, const char *httpVersion)
{
    char content[1000];
    char header[200];
    char response[1200];
    sprintf(content, "<!DOCTYPE HTML><html lan='en'><head><meta charset='utf-8'><title>Not Supported HTTP Version</title></head><body>HTTP Version Not Supported [%s]</body></html>", httpVersion);
    int contentLength = strlen(content);
    sprintf(header, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length:%d\r\nConnection: close\r\n\r\n", contentLength);
    strcpy(response, header);
    strcat(response, content);
    send(clientSocketDescriptor, response, strlen(response), 0);
}

void HttpErrorStatusUtility::sendNotFoundError(int clientSocketDescriptor, const char *requestURI)
{
    // we will optmize this code later on
    char content[1000];
    char header[200];
    char response[1200];
    sprintf(content, "<!DOCTYPE HTML><html lan='en'><head><meta charset='utf-8'><title>404 Not Found</title></head><body>Requested Resourse [%s] Not Found</body></html>", requestURI);
    int contentLength = strlen(content);
    sprintf(header, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length:%d\r\nConnection: close\r\n\r\n", contentLength);
    strcpy(response, header);
    strcat(response, content);
    send(clientSocketDescriptor, response, strlen(response), 0);
}

void HttpErrorStatusUtility::sendMethodNotAllowedError(int clientSocketDescriptor, const char *method)
{
    char content[1000];
    char header[200];
    char response[1200];
    sprintf(content, "<!DOCTYPE HTML><html lan='en'><head><meta charset='utf-8'><title>Method Not Allowed</title></head><body><h1>Only GET type</h1>May be in future [%s] will supported</body></html>", method);
    int contentLength = strlen(content);
    sprintf(header, "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\nContent-Length:%d\r\nConnection: close\r\n\r\n", contentLength);
    strcpy(response, header);
    strcat(response, content);
    send(clientSocketDescriptor, response, strlen(response), 0);
}


void HttpErrorStatusUtility::sendInternalError(int clientSocketDescriptor,const char *resourceName)
{
    char content[1000];
    char header[200];
    char response[1200];
    sprintf(content, "<!DOCTYPE HTML><html lan='en'><head><meta charset='utf-8'><title>Internal Error</title></head><body><h1>Try After Some Time Internal Error Occured</h1>For [%s]</body></html>", resourceName);
    int contentLength = strlen(content);
    sprintf(header, "HTTP/1.1 500 Internal Error\r\nContent-Type: text/html\r\nContent-Length:%d\r\nConnection: close\r\n\r\n", contentLength);
    strcpy(response, header);
    strcat(response, content);
    send(clientSocketDescriptor, response, strlen(response), 0);
}
