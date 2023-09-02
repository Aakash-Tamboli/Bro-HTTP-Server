#include<iostream>
#include<string.h>
#include<map>
#include<stdlib.h>

using namespace std;

class Container
{
private:
map<string,void *> dataSet;
public:
template<class T1>
void set(string key,T1 value)
{
cout<<sizeof(value)<<endl;
void *ptr;
ptr=malloc(sizeof(value));
memcpy(ptr,&value,sizeof(value));
dataSet.insert(pair<string,void *>(key,ptr));
}
template<class T2>
void get(string key,T2 destination,bool *success)
{
cout<<sizeof(*destination)<<endl;
auto iterator=dataSet.find(key);
if(iterator==dataSet.end())
{
if(success) *success=false;
return;
}
memcpy(destination,iterator->second,sizeof(*destination));
if(success) *success=true;
}
};


void extractAndPrint(Container c)
{
int a;
uint b;
char cc;
u_char d;
float e;
double f;
long double g;
short int h;
unsigned short int i;
long int j;
unsigned long int k;
long long int l;
unsigned long long int m;
wchar_t n;
bool A,B,C,D,E,F,G,H,I,J,K,L,M,N;

c.get("int",&a,&A);
c.get("uint",&b,&B);
c.get("char",&cc,&C);
c.get("uchar",&d,&D);
c.get("float",&e,&E);
c.get("double",&f,&F);
c.get("long double",&g,&G);
c.get("short",&h,&H);
c.get("ushort",&i,&I);
c.get("lint",&j,&J);
c.get("ulint",&k,&K);
c.get("llint",&l,&L);
c.get("ullint",&m,&M);
c.get("wchar",&n,&N);

if(A) cout<<a<<endl;
if(B) cout<<b<<endl;
if(C) cout<<cc<<endl;
if(D) cout<<d<<endl;
if(E) cout<<e<<endl;
if(F) cout<<f<<endl;
if(G) cout<<g<<endl;
if(H) cout<<h<<endl;
if(I) cout<<i<<endl;
if(J) cout<<j<<endl;
if(K) cout<<k<<endl;
if(L) cout<<l<<endl;
if(M) cout<<m<<endl;
if(N) cout<<n<<endl;


}

int main()
{
Container c;

c.set("int",10);
c.set("uint",(unsigned int)2147483655);
c.set("char",'A');
c.set("uchar",(unsigned char)200);
c.set("float",2.335f);
c.set("double",55.443);
c.set("long double",(long double)45.33);
c.set("short",(short int)43);
c.set("ushort",(unsigned short int)543);
c.set("lint",(long int)-777);
c.set("ulint",(unsigned long int)54345);
c.set("llint",(long long int)-4838);
c.set("ullint",(unsigned long long int)30304);
c.set("wchar",(wchar_t)'A');

cout<<"------------------------------------------------------"<<endl;
extractAndPrint(c);
return 0;
}
