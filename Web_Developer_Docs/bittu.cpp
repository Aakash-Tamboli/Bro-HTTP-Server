#include<bro.h>
// Bittu [ The Web Application Developer User of Bro Web Server ]
int main()
{
try
{
Bro bro;
bro.setStaticResourcesFolder("static");

bro.get("/",[](Request &request,Response &response){
response.setContentType("text/html");
response<<R""""(
<!DOCTYPE HTML>
<html lan='en'>
<head>
<meta charset='utf-8'>
<title>Get Started</title>
</head>
<body>
<a href='/start'>Begin</a>
</body>
</html>
)"""";
});


bro.get("/start",[](Request &request,Response &response){
response<<R""""(
<!DOCTYPE HTML>
<html lan='en>
<head>
<meta charset='utf-8'>
<title>Form</title>
</head>
<body>
<form method='post' action='/saveData'>
Name: &emsp;
<input type='text' id='name' name='name'>
City: &emsp;
<input type='text' id='city' name='city'>
<button type='submit'>Save</button>
</form>
</body>
</html>
)"""";
response.setContentType("text/html");
});

bro.get("/saveData",[](Request &request,Response &response){
cout<<request["name"]<<endl;
cout<<request["city"]<<endl;
response<<R""""(
<!DOCTYPE HTML>
<html lan='en'>
<head>
<meta charset='utf-8'>
<title>Get Started</title>
</head>
<body>
<a href='/'>Ok</a>
</body>
</html>
)"""";
response.setContentType("text/html");
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
