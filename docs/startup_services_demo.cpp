int main()
{
try
{
Bro bro;

bro.addStartupService(1,[](){
cout<<"---------------------------------------------"<<endl;
cout<<"A great function got called at server startup"<<endl;
cout<<"Its Priority Number is 1"<<endl;
cout<<"---------------------------------------------"<<endl;
});

bro.addStartupService(1,[](){
cout<<"---------------------------------------------"<<endl;
cout<<"A another great function got called at server startup"<<endl;
cout<<"Its Priority Number is 1"<<endl;
cout<<"---------------------------------------------"<<endl;
});

bro.addStartupService(2,[](){
cout<<"---------------------------------------------"<<endl;
cout<<"A good function got called at server startup"<<endl;
cout<<"Its Priority Number is 2"<<endl;
cout<<"---------------------------------------------"<<endl;
});


bro.addStartupService(3,[](ApplicationLevelContainer &applicationLevelContainer){
cout<<"---------------------------------------------"<<endl;
cout<<"A best function got called at server startup whose requirement is Dependencies Injection"<<endl;
cout<<"Its Priority Number is 3"<<endl;
cout<<"---------------------------------------------"<<endl;
});

bro.get("/",[](Request &request,Response &response){
response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>HOME</title>
</head>
<body>
<h1>God is Great</h1>
<a href='/begin'>Begin</a>
</body>
</html>
)"""";
response.setContentType("text/html");
});

bro.get("/begin",[](Request &request,Response &response){
response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title>Form</title>
</head>
<body>
<form action='/saveData'>
Name:&nbsp;
<input type='text' name='name' id='name'>
City:&nbsp;
<input type='text' name='city' id='city'>
<button type='submit'>Save</button>
</form>
</body>
</html>
)"""";
response.setContentType("text/html");
});

bro.get("/saveData",[](Request &request,Response &response,ApplicationLevelContainer &container){
cout<<"Data is Processing"<<endl;
string *name,*city;
name=new string(request["name"]);
city=new string(request["city"]);
container.set("name",&name,NULL,NULL);
container.set("city",&city,NULL,NULL);
// request Forwarded
_forward_to(request,"/saveData2");
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
