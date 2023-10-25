#include "bro_v1.6.cpp"
int main()
{
try
{
Bro bro;
bro.setStaticResourcesFolder("static");

bro.get("/",[](Request &request,Response &response){
const char *html=R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title> Welcome </title>
</head>
<body>
<a href='abcd.html'>Begin</a>
</body>
</html>
)"""";
response<<html;
response.setContentType("text/html");
});

bro.get("/aaa",[](Request &request,Response &response){
string name=request["name"];
char line[201];
cout<<"Data Arrived"<<endl;
cout<<name<<endl;
const char *html=R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title> Form 2</title>
</head>
<body>
<form action='/bbb'>
City:
&nbsp;
<input type='text' id='city' name='city'>
)"""";
response<<html;
sprintf(line,"<input type='hidden' id='name' name='name' value='%s'>",name.c_str());
response<<line;
response<<"<button type='submit'>Save It</button>";
response<<"</form>";
response<<"</body>";
response<<"</html>";
response.setContentType("text/html");
});

bro.get("/bbb",[](Request &request,Response &response){
string name=request["name"];
string city=request["city"];
cout<<"Data Arrived and Saved"<<endl;
cout<<name<<"  ,    "<<city<<endl;

response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title> Data Saved </title>
</head>
<body>
<form action='/'>
<h1>Data Saved</h1>
)"""";

char line[201];

sprintf(line,"Name: %s <br>City: %s <br>",name.c_str(),city.c_str());

response<<line;

response<<R""""(
<button type='submit'> Finish</button>
</form>
</body>
</html>
)"""";
response.setContentType("text/html");
});

bro.listen(5050,[](Error &error){
if(error.hasError())
{
cout<<"Unable to listen at: 5050"<<endl;
return;
}
cout<<"Bro Server Listening at 5050"<<endl;
});
}catch(string &exception)
{
cout<<exception<<endl;
}
return 0;
}
