int main()
{
try
{
Bro bro;
bro.setStaticResourcesFolder("static");

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

bro.get("/saveData",[](Request &request,Response &response){
string name=request["name"];
string city=request["city"];
cout<<"Name: "<<name<<endl;
cout<<"City: "<<city<<endl;
request.set("name",name);
request.set("city",city);
_forward_to(request,string("/displayData.chtml"));
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
