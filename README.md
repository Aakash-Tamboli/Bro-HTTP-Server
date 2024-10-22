# Bro Server Documentation

## Overview
This document introduces the Bro HTTP Server, developed in C++.

## Why Bro HTTP Server in C++?
In my view Engineering is about building things on existing knowledge. Understanding how current technologies work allows us to innovate in the future. This project implements network programming (socket programming) in C++, providing a Bro Server that mimics the behavior of Tomcat for web application developers.

## Deployment
To deploy your web app using Bro Server, follow this folder structure:

```
Bro-HTTP-Server
│
├── Web_Developer_Docs
│   ├── bro-data (Dependencies)
│   └── vmd_files (Dependencies)
```

Your `web_app` should include the `bro-data` and `vmd_files` folders.

## Demo

Here’s a basic example of how to use the Bro HTTP Server:

```cpp
#include <bro.h>
using namespace std;

int main() {
    try {
        Bro bro;
        bro.setStaticResourcesFolder("static");
        
        bro.get("/url_pattern", [](Request &request, Response &response) {
            // Handle request
        });
        
        bro.get("/url_pattern", [](Request &request, Response &response, ApplicationLevelContainer &container) {
            // Handle request with container
        });

        bro.listen(5050, [](Error &error) {
            if (error.hasError()) {
                cout << error.getError() << endl;
                return;
            }
            cout << "Bro HTTP Server is ready to accept requests on port 5050" << endl;
        });
    } catch (string &exception) {
        cout << exception;
    }
    return 0;
}
```

## Compilation

Assuming you are in the `Web_Developer_Docs` folder, where `bro-data` and `vmd_files` are located, compile with:

```bash
g++ fileName.cpp -o fileName.out -I ../include -L ../lib -l bro
```

## Features

Currently, the Bro Server supports:
- Cookies
- Dependency Injection (Application Level Container)
- Request Scope Level Container
- GET requests

More features will be added in the future.

## Examples

Refer to the `Docs` folder for specific feature examples.

## Development Tools

- Vim Text Editor
- G++ (7.5.0 or higher, C++17+)
- Ubuntu Operating System
- Windows 10

## Credit

Thanks to God, Mom and kelkar Sir and Thanks to All the Creator That I've Used his/her Application Like vim,g++,ubuntu OS,Tomcat and Windows 10 OS.
