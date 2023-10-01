# Bro Server DOCUMENTATION

## Overview
here you get to know about `Bro HTTP Server`, which is built on `c++` programming language.

## Why Bro HTTP Server In C++ ?
So In My view Engineeing is about to build, But Before Building First we have to understand How Existing things work internally, So That In future we can build on top of that, this project I Implemeted Network Programming or Socket Programming in C++ and Provide Ready Bro-Server for Web Application Developer, trying to mimic the behaviour of Tomcat like server.
## Deployment

To deploy your Web-App using Bro-Server then folder structure must be followed like:

1) Your web_app should be reside in apps folder.
2) your web_app should contains bro-data folder which is already provided.

```
Bro-HTTP-Server -- > apps/your_web_app
                        |---> bro-data (Dependencies)
```


## Demo


```c
#include<iostream>
using namespace std;
int main()
{
    try
    {
        Bro bro;
        bro.setStaticResourcesFolder("static");
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
        cout<<exception;
    }
    return 0;
}
```
## Examples
later on I will add link to use each feature of Bro Server.


## Tool I've Used to Develop Bro Server
1. Vim Text Editor
2. G++ (7.5.0) (above C++17) Or Greater
3. Ubuntu Operating System
4. Windows 10


## Guidance
This Project is developed under the guidence of Prafull Kelkar Sir


## Credit
Thanks to God. Thanks to All the Creator That I've Used his/her Application Like vim,g++,ubuntu OS,Tomcat and Windows 10 OS Thanks to Prafull Sir

