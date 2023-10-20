class Bulb:public Stringifyable
{
private:
int wattage;
int price;
public:
void setWattage(int wattage)
{
this->wattage=wattage;
}
void setPrice(int price)
{
this->price=price;
}
int getWattage()
{
return this->wattage;
}
int getPrice()
{
return this->price;
}
string stringify()
{
return string("Wattage: ")+to_string(this->wattage)+string(", Price: ")+to_string(this->price);
}
};

int main()
{
try
{
Bro bro;
bro.setStaticResourcesFolder("static");

bro.get("/getTemplateVariableValue",[](Request &request,Response &response){
Bulb bulb;
bulb.setWattage(60);
bulb.setPrice(100);
short int a=10;
unsigned int b=20;
int c=30;
unsigned int d=40;
long int e=50;
unsigned long int f=60;
long long int g=70;
unsigned long long int h=80;
float i=763.44f;
double j=534.3423;
long double k=7734.32;
char l='A';
unsigned m='B';
bool n=true;
request.setCHTMLVariable("bulb",&bulb);
request.setCHTMLVariable("aa",a);
request.setCHTMLVariable("bb",b);
request.setCHTMLVariable("cc",c);
request.setCHTMLVariable("dd",d);
request.setCHTMLVariable("ee",e);
request.setCHTMLVariable("ff",f);
request.setCHTMLVariable("gg",g);
request.setCHTMLVariable("hh",h);
request.setCHTMLVariable("ii",i);
request.setCHTMLVariable("jj",j);
request.setCHTMLVariable("kk",k);
request.setCHTMLVariable("ll",l);
request.setCHTMLVariable("mm",m);
request.setCHTMLVariable("nn",n);
_forward_to(request,"/TemplateVariableTest.chtml");
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
