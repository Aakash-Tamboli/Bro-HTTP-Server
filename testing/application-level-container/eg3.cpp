#include<iostream>
#include<string.h>
#include<map>
#include<stdlib.h>

using namespace std;

class Container
{
private:

typedef struct _bag
{
void *ptr;
int size;
}Bag;
map<string,Bag> dataSet;

public:
template<class T1>
void set(string key,T1 value)
{
cout<<sizeof(value)<<endl;
void *ptr;
ptr=malloc(sizeof(value));
memcpy(ptr,&value,sizeof(value));
Bag bag;
bag.ptr=ptr;
bag.size=sizeof(value);
dataSet.insert(pair<string,Bag>(key,bag));
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
Bag bag=iterator->second;
if(bag.size!=sizeof(*destination))
{
if(success) *success=false;
return;
}
memcpy(destination,bag.ptr,sizeof(*destination));
if(success) *success=true;
}
};

// No Error Prone Code
class Bulb
{
private:
int wattage;
public:
Bulb()
{
this->wattage=0;
}

Bulb(const Bulb &other)
{
this->wattage=other.wattage;
}

void setWattage(int wattage)
{
this->wattage=wattage;
}

int getWattage()
{
return this->wattage;
}

};

void keepData(Container &c)
{
Bulb g; // local object
g.setWattage(60);
c.set("philips",g);
} // g will be die (conceptually) but its content will copied to Container


void extractAndPrint(Container &c)
{
Bulb k;
bool success;
c.get("philips",&k,&success);
if(success)
{
cout<<k.getWattage()<<endl;
}
else
{
cout<<"Philips does not exists"<<endl;
}
}

int main()
{
Container c;
keepData(c);
extractAndPrint(c);
return 0;
}
