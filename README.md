# Bro Server DOCUMENTATION

## Overview
here you get to know about `Bro HTTP Server`, which is built on `c++` programming language.

## Why Bro HTTP Server In C++ ?
So In My view Engineeing is about to build, But Before Building First we have to understand How Existing things work internally, So That In future we can build on top of that Technology,In this project I Implemeted Network Programming or Socket Programming in C++ and Provide Ready Bro-Server for Web Application Developer, trying to mimic the behaviour of Tomcat like server.
## Deployment

To deploy your Web-App using Bro-Server then folder structure must be followed like:

* Your web_app should contains bro-data and vmd_files folder which is already provided.

```
Bro-HTTP-Server -- > Web_Developer_Docs
                        |---> bro-data (Dependencies)
			|---> vmd_files (Dependecies)
```


## Demo

```c
#include<bro.h>
using namespace std;
int main()
{
    try
    {
        Bro bro;
        bro.setStaticResourcesFolder("static");
	bro.get("/url_pattern",[](Request &request,Response &response){
		

	});
	bro.get("/url_pattern",[](Request &request,Response &response,ApplicationLevelContainer &container){
		
		
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
        cout<<exception;
    }
    return 0;
}
```
## To Compile
I Assume You are in Web_Developer_Docs Folder, over-there bro-data and vmd_files is considered as dependencies folder so don't tempared or delete.
the 
`g++ fileName.cpp -o fileName.out -I ../include -L ../lib -l bro`

## Feature
Currenly Our Bro Server Provides Cookies,Dependieces Injection (Application Level container), Request Scope level conatiner,GET type request,... later on Will add more features


## Examples
Kindly Reffer Docs Folder, for specfic feature


## Tool I've Used to Develop Bro Server
1. Vim Text Editor
2. G++ (7.5.0) (above C++17) Or Greater
3. Ubuntu Operating System
4. Windows 10

## Credit
Thanks to God. Thanks to All the Creator That I've Used his/her Application Like vim,g++,ubuntu OS,Tomcat and Windows 10 OS.

