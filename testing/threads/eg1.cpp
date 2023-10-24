#include<iostream>
#include<chrono>
#include<string.h>
#include<map>
#include<thread>
using namespace std;
class Student
{
private:
string name;
int assignmentFrom;
int assignmentTo;
bool isCompleted;
public:
Student(string nm,int asgFrom,int asgTo):name(nm),assignmentFrom(asgFrom),assignmentTo(asgTo)
{
this->isCompleted=false;
}
void operator()()
{
for(int i=this->assignmentFrom;i<=this->assignmentTo;i++)
{
this_thread::sleep_for(chrono::milliseconds(300));
cout<<"Processing Assignment No: "<<i<<endl;
}
cout<<this->name<<" is telling that the assignement is completed"<<endl;
this->isCompleted=true;
}
};

typedef struct _grp
{
thread *t;
Student *s;
}grp;

int main()
{
string name;
int asgFrom;
int asgTo;
thread *t;
cout<<"Teacher Enter the class"<<endl;
cout<<"Teacher start distributing assignement"<<endl;
while(true)
{
cout<<"Student Name: ";
cin>>name;
if(strcmp(name.c_str(),"quit")==0) break;
cout<<"Assignment From: ";
cin>>asgFrom;
cout<<"Assignement To: ";
cin>>asgTo;
t=new thread(Student(name,asgFrom,asgTo));
} // inifnte loop ends
return 0;
}
