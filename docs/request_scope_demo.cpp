int main()
{
try
{
Bro bro;
bro.setStaticResourcesFolder("static");

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
