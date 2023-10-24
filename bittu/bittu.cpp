#include<bro.h>
// Bittu [ The Web Application Developer User of Bro Web Server ]
int main()
{
try
{
Bro bro;
bro.setStaticResourcesFolder("static");
bro.get("/",[](Request &request,Response &response){
Cookie c1("name","Aakash");
Cookie c2("RollNo","202");
Cookie c3("City","Ujjain");
response<<c1<<c2;
response.addCookie(c3);
response.setContentType("text/html");
response<<R""""(
<!DOCTYPE HTML>
<html lan='en'>
<head>
<meta charset='utf-8'>
<title>Get Started</title>
</head>
<body>
<a href='/aRequest'>Begin</a>
</body>
</html>
)"""";
});


bro.get("/aRequest",[](Request &request,Response &response){
cout<<"Function got called for /aRequest"<<endl;
int score=100;
request.set("score",score,NULL,NULL);
_forward_to(request,"/bRequest");
});

bro.get("/bRequest",[](Request &request,Response &response){
cout<<"Function got called for /bRequest"<<endl;
int score;
request.get("score",&score,NULL,NULL);
cout<<"-------------------------------------------------"<<endl;
string name=request.getCookieValue("name");
string rollNo=request.getCookieValue("RollNo");
string city=request.getCookieValue("city");
cout<<name<<","<<rollNo<<","<<city<<endl;
cout<<"--------------------------------------------------"<<endl;

response.setContentType("text/html");
const char *html=R""""(
<!DOCTYPE HTML>
<html lan='en'>
<head>
<meta charset='utf-8'>
<title>Score</title>
</head>
<body>
<h1>Score: 
)"""";
response<<html;
response<<to_string(score);
response<<R""""(
</h1>
<a href='/'>See Cookie</a>
</body>
</html>
)"""";
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
