int main()
{
try
{
Bro bro;

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

// If User Direct call forward method of  request class then they should not do anything after that call other wise request forwarding feature will broke and their intension to forward will fail.

bro.get("/saveData",[](Request &request,Response &response,ApplicationLevelContainer &container){
cout<<"Data is Processing"<<endl;
string *name,*city;
name=new string(request["name"]);
city=new string(request["city"]);
container.set("name",&name,NULL,NULL);
container.set("city",&city,NULL,NULL);
// request Forwarded
request.forward("/saveData2");
// after forwarding any code will not placed here Clear Warning.
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
