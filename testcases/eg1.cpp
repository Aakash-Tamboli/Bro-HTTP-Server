#include<bro_container.h>
#include<bro_gmt_date_time.h>
#include<iostream>
using namespace std;
int main()
{
Container c;
int x=10;
c.set("x",x,NULL,NULL);
int y;
c.get("x",&y,NULL,NULL);
cout<<y<<endl;
GMTDateTime now;
cout<<now<<endl;
return 0;
}
