#include<iostream>
using namespace std;
// Aakash Who Creat web server
class Error
{
public:
bool hasError()
{
return false;
}
string getError()
{
return "";
}
};
class Request
{
};

class Response
{
public:
void setContentType(string contentType)
{
// do nothing right now
}
Response & operator<<(string content)
{
return *this;
}
};

class Bro
{
public:
void setStaticResourcesFolder(string staticResourcesFolder)
{
// do nothing right now
}
void get(string url,void (*callBack)(Request &,Response &))
{
// do nothing right now
}
void listen(int portNumber,void (*callBack)(Error &))
{
// do nothing right now
}
};

// Bittu [ The Web Application Developer User of Bro Web Server ]

int main()
{
Bro bro;
bro.setStaticResourcesFolder("Whatever");
bro.get("/",[](Request &request,Response &response){
const char *html=R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Whatever</title>
</head>
<body>
<h1>Welcome</h1>
<h3>Adminstartor</h3>
<a hreff='getCustomers'>Customer List</a>
</body>
</html>
)"""";
response.setContentType("text/html");
response<<html;
});

bro.get("/getCustomers",[](Request &request,Response &response){
const char *html=R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Customer List</title>
</head>
<body>
<h1>List Of Customers</h1>
<ul>
<li>Immanual</li>
<li>Beena</li>
<li>Sanjay</li>
</ul>
<a hreff='/'>home</a>
</body>
</html>
response.setContentType("text/html"); // setting MIME Type
response<<html;
)"""";
});

bro.listen(5050,[](Error &error){
if(error.hasError())
{
cout<<error.getError()<<endl;
return;
}
cout<<"Bro HTTO Server is Ready to accept Request on port 5050"<<endl;
});
return 0;
}
