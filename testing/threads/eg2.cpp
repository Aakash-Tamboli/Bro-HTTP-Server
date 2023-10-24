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
bool _isCompleted;
public:
Student(string nm,int asgFrom,int asgTo):name(nm),assignmentFrom(asgFrom),assignmentTo(asgTo)
{
this->_isCompleted=false;
}
void operator()()
{
for(int i=this->assignmentFrom;i<=this->assignmentTo;i++)
{
this_thread::sleep_for(chrono::milliseconds(300));
cout<<"Processing Assignment No: "<<i<<endl;
}
cout<<this->name<<" is telling that the assignement is completed"<<endl;
this->_isCompleted=true;
}
bool isCompleted()
{
return this->_isCompleted;
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
Student *student;
int asgFrom;
int asgTo;
thread *t;
map<string,grp> m;
grp g;
cout<<"Teacher Enter the class"<<endl;
cout<<"Teacher start distributing assignement"<<endl;
while(true)
{
for(auto p: m)
{
grp g=p.second;
if(g.s->isCompleted()) delete g.t;
}
cout<<"Student Name: ";
cin>>name;
if(strcmp(name.c_str(),"quit")==0) break;
cout<<"Assignment From: ";
cin>>asgFrom;
cout<<"Assignement To: ";
cin>>asgTo;
student=new Student(name,asgFrom,asgTo);
t=new thread(*student);
g.t=t;
g.s=student;
m.insert(pair<string,grp>(name,g));
if(m.size()==0) break;
} // inifnte loop ends




return 0;
}
