#include <bro.h>
#include <bro_request_processor.h>

bool Bro::isCHTML(const char *requestURI)
{
    // a.chtml I will check in-case sensitive
    int len = strlen(requestURI);
    if (len < 7)
        return false;
    const char *ptr1 = requestURI + len - 6;
    char lastPart[7] = {".chtml"};
    const char *ptr2 = lastPart;
    char a, b;
    while (*ptr1 && *ptr2)
    {
        a = *ptr1;
        b = *ptr2;
        if (a >= 97 && a <= 122)
            a = a - 32;
        if (b >= 97 && b <= 122)
            b = b - 32;
        if (a != b)
            return false;
        ptr1++;
        ptr2++;
    }
    return true;
}
Bro::Bro()
{
    BroUtilities::loadMIMETypes(mimeTypes);
    if (mimeTypes.size() == 0)
        throw string("bro-data folder has been tempared with");
}
Bro::~Bro()
{
}
void Bro::setStaticResourcesFolder(string staticResourcesFolder)
{
    if (Validator::isValidPath(staticResourcesFolder))
    {
        this->staticResourcesFolder = staticResourcesFolder;
    }
    else
    {
        string exception = string("Invalid static Resource Folder Path: ") + string(staticResourcesFolder);
        throw exception;
    }
}

void Bro::addStartupService(int priorityNumber, void (*startupFunction)(void))
{
    StartupFunction *sf;
    sf = new SimpleStartupFunction(priorityNumber, startupFunction);
    startupFunctions.push(sf);
}

void Bro::addStartupService(int priorityNumber, void (*startupFunction)(ApplicationLevelContainer &))
{
    StartupFunction *sf;
    sf = new ApplicationLevelContainerDependentStartupFunction(priorityNumber, startupFunction, &(this->applicationLevelContainer));
    startupFunctions.push(sf);
}

void Bro::get(string url, void (*callBack)(Request &, Response &))
{
    if (Validator::isValidURLFormat(url))
    {
        ServiceFunction *serviceFunction;
        URLMapping u;
        u.requestMethod = __GET__;
        serviceFunction = new SimpleFunction(callBack);
        u.function = serviceFunction;
        this->urlMappings.insert(pair<string, URLMapping>(url, u));
    }
}

void Bro::get(string url, void (*callBack)(Request &, Response &, ApplicationLevelContainer &))
{
    if (Validator::isValidURLFormat(url))
    {
        ServiceFunction *serviceFunction;
        URLMapping u;
        u.requestMethod = __GET__;
        serviceFunction = new ApplicationLevelContainerDependentFunction(callBack, &(this->applicationLevelContainer));
        u.function = serviceFunction;
        this->urlMappings.insert(pair<string, URLMapping>(url, u));
    }
}

void Bro::processCHTMLResource(int clientSocketDescriptor, const char *requestURI, Request &request)
{
    if (this->staticResourcesFolder.length() == 0)
    {
        HttpErrorStatusUtility::sendNotFoundError(clientSocketDescriptor,requestURI);
        return;
    }
    if (!FileSystemUtility::directoryExists(this->staticResourcesFolder.c_str()))
    {
        HttpErrorStatusUtility::sendNotFoundError(clientSocketDescriptor,requestURI);
        return;
    }
    string resourcePath = this->staticResourcesFolder + string(requestURI);
    if (!FileSystemUtility::fileExists(resourcePath.c_str()))
    {
        HttpErrorStatusUtility::sendNotFoundError(clientSocketDescriptor,requestURI);
        return;
    }
    TemplateEngine::processCHTMLFile(resourcePath.c_str(), request, clientSocketDescriptor);
}

bool Bro::serveStaticResourcesFolder(int clientSocketDescriptor, const char *requestURI)
{
    if (this->staticResourcesFolder.length() == 0)
        return false;
    if (!FileSystemUtility::directoryExists(this->staticResourcesFolder.c_str()))
        return false;

    string resourcePath = this->staticResourcesFolder + string(requestURI);
    if (!FileSystemUtility::fileExists(resourcePath.c_str()))
        return false;
    cout << "Looking is Resources Folder: " << resourcePath << endl;
    FILE *file = fopen(resourcePath.c_str(), "rb");
    if (file == NULL)
        return false; // if OS does'nt allow to access file for security reasons

    long fileSize;

    fseek(file, 0, SEEK_END);

    fileSize = ftell(file);

    if (fileSize == 0)
    {
        fclose(file);
        return false;
    }

    rewind(file); // to move the internal pointer to start of the file

    string extension, mimeType;
    extension = FileSystemUtility::getFileExtension(resourcePath.c_str());
    if (extension.length() > 0)
    {
        transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
        auto mimeTypesIterator = mimeTypes.find(extension);
        if (mimeTypesIterator != mimeTypes.end())
        {
            mimeType = mimeTypesIterator->second;
        }
        else
        {
            mimeType = string("text/html");
        }
    }
    else
    {
        mimeType = string("text/html");
    }

    char header[200];
    sprintf(header, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %ld\r\nConnection: close\r\n\r\n", mimeType.c_str(), fileSize);

    send(clientSocketDescriptor, header, strlen(header), 0);

    long bytesLeftToRead;
    int bytesToRead;

    char buffer[4096];

    bytesToRead = 4096;

    bytesLeftToRead = fileSize;

    while (bytesLeftToRead > 0)
    {
        if (bytesLeftToRead < bytesToRead)
            bytesToRead = bytesLeftToRead;
        fread(buffer, bytesToRead, 1, file);
        if (feof(file))
            break; // it won't happen in our case but its good practice
        send(clientSocketDescriptor, buffer, bytesToRead, 0);
        bytesLeftToRead = bytesLeftToRead - bytesToRead;
    } // loop ends
    fclose(file);
    return true;
}
void Bro::listen(int portNumber, void (*callBack)(Error &))
{
#ifdef _WIN32
    WSADATA wsaData;
    Word ver;
    ver = MAKEWORD(1, 1);
    WSAStartup(ver, &wsaData);
#endif
    int serverSocketDescriptor;
    char requestBuffer[4097];
    int requestLength;
    int i;

    serverSocketDescriptor = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocketDescriptor < 0)
    {
#ifdef _WIN32
        WSACleanup();
#endif
        Error error("Unable to create Socket");
        callBack(error);
        return;
    }

    struct sockaddr_in serverSocketInformation;
    serverSocketInformation.sin_family = AF_INET;
    serverSocketInformation.sin_port = htons(portNumber);
    serverSocketInformation.sin_addr.s_addr = htonl(INADDR_ANY);
    int successCode = bind(serverSocketDescriptor, (struct sockaddr *)&serverSocketInformation, sizeof(serverSocketInformation));
    if (successCode < 0)
    {
        close(serverSocketDescriptor);
#ifdef _WIN32
        WSACleanup();
#endif
        char a[101];
        sprintf(a, "Unable to bind socket to port: %d", portNumber);
        Error error(a);
        callBack(error);
        return;
    }

    successCode = ::listen(serverSocketDescriptor, 10);
    if (successCode < 0)
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
    while (!this->startupFunctions.empty())
    {
        startupFunction = this->startupFunctions.top();
        startupFunctions.pop();
        startupFunction->run();
    } // loop ends
    // code to call all startup Services ends here

    Error error("");
    callBack(error);
    struct sockaddr_in clientSocketInformation;
#ifdef linux
    socklen_t len = sizeof(clientSocketInformation);
#endif
#ifdef _WIN32
    int len = sizeof(clientSocketInformation);
#endif

    int clientSocketDescriptor;
    BroThreadWrapper *p;
    BroThreadWrapper *p1, *p2;
    BroThreadWrapper *head = NULL;
    while (true)
    {
        clientSocketDescriptor = accept(serverSocketDescriptor, (struct sockaddr *)&clientSocketInformation, &len);
        p = new BroThreadWrapper;
        p->hasCompleted = false;
        p->th = new thread(requestProcessor, clientSocketDescriptor, this, p);
        p->next = head;
        head = p;
        p1 = head;
        while (p1 != NULL)
        {
            if (p1->hasCompleted)
            {
                p1->th->join(); // if minute execute is remain then it will be executed
                if (p1 == head)
                {
                    head = head->next;
                    delete p1->th;
                    delete p1;
                    p1 = head;
                    continue;
                }
                else
                {
                    p2->next = p1->next;
                    delete p1->th;
                    delete p1;
                    p1 = p2->next;
                    continue;
                }
            }
            p2 = p1;
            p1 = p1->next;
        } // loop to scan completed thread ends
        // lot of code will be written here later on
    } // infinit loop ends

    // When Bro Server gets shutdown then

    while (true)
    {
        p1 = head;
        while (p1 != NULL)
        {
            if (p1->hasCompleted)
            {
                p1->th->join(); // if minute execute is remain then it will be executed
                if (p1 == head)
                {
                    head = head->next;
                    delete p1->th;
                    delete p1;
                    p1 = head;
                    continue;
                }
                else
                {
                    p2->next = p1->next;
                    delete p1->th;
                    delete p1;
                    p1 = p2->next;
                    continue;
                }
            }
            p2 = p1;
            p1 = p1->next;
        }
    } // releasing memory

#ifdef _WIN32
    WSACleanup();
#endif
}
