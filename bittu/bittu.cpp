#include<bro.h>
// Bittu [ The Web Application Developer User of Bro Web Server ]
int main()
{
try
{
Bro bro;
bro.setStaticResourcesFolder("static");
bro.get("/",[](Request &request,Response &response){
const char *html=R""""(
<!DOCTYPE HTML>
<html lan='en'>
<head>
<meta charset='utf-8'>
<title>Bro Server Home Page</title>
</head>
<body>
<h1>>Bro Server Home Page</h1>
<a href='/formWithGetType'>Form (Get Type)</a>
<a href='/formWithPostType'>From (Post Type)</a>
</body>
</html>
)"""";
response.setContentType("text/html");
response<<html;
});


bro.get("/formWithGetType",[](Request &request,Response &response){
const char *html=R""""(
<!DOCTYPE HTML>
<html lan='en'>
<head>
<meta charset='utf-8'>
<title>Form with Get</title>
</head>
<body>
<h1>coming Soon</h1>
<a href='/'>Coming Soon</a>
</body>
</html>
)"""";
response.setContentType("text/html");
response<<html;
});

bro.post("/formWithPostType",[](Request &request,Response &response){
response.setContentType("text/html");
const char *html=R""""(
<!DOCTYPE HTML>
<html lan='en'>
<head>
<meta charset='utf-8'>
<title></title>
</head>
<body>
<h1>Coming Soon</h1>
<a href='/'>Coming Soon</a>
</body>
</html>
)"""";
response.setContentType("text/html");
response<<html;
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
