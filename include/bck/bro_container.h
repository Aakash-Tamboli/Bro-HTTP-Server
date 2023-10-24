#ifndef __BRO_CONTAINER__
#define __BRO_CONTAINER__ 4
#include<bro.h>

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
void set(string,T1,bool *,__container_operation_failure_reason__ *);
template<class T2>
void get(string,T2,bool *,__container_operation_failure_reason__ *);
template<class T3>
void remove(string,T3,bool *,__container_operation_failure_reason__ *);
bool contains(string);
};


template<class T1> // because we are using template feature so according to mentor and docs it will not become part of library because we know complier will write those appropritate function for us,acc to user called that's why I expose the implementation part of this Container class
void Container::set(string keyName,T1 something,bool *success,__container_operation_failure_reason__ *reason)
{
auto iterator=dataSet.find(keyName);
if(iterator!=dataSet.end())
{
if(reason) *reason=__KEY_EXISTS__;
if(success) *success=false;
return;
}
void *ptr;
ptr=malloc(sizeof(something));
if(ptr==NULL)
{
if(reason) *reason=__OUT_OF_MEMORY__;
if(success) *success=false;
return;
}
memcpy(ptr,&something,sizeof(something));
Bag bag;
bag.ptr=ptr;
bag.size=sizeof(something);
dataSet.insert(pair<string,Bag>(keyName,bag));
if(success) *success=true;
}
template<class T2>
void Container::get(string keyName,T2 anything,bool *success,__container_operation_failure_reason__ *reason)
{
auto iterator=dataSet.find(keyName);
if(iterator==dataSet.end())
{
if(reason) *reason=__KEY_DOES_NOT_EXIST__;
if(success) *success=false;
return;
}
Bag bag;
bag=iterator->second;
if(bag.size!=sizeof(*anything))
{
if(reason) *reason=__VALUE_SIZE_MISMATCH__;
if(success) *success=false;
return;
}
memcpy(anything,bag.ptr,sizeof(*anything));
if(success) *success=true;
}
template<class T3>
void Container::remove(string keyName,T3 anything,bool *success,__container_operation_failure_reason__ *reason)
{
auto iterator=dataSet.find(keyName);
if(iterator==dataSet.end())
{
if(reason) *reason=__KEY_DOES_NOT_EXIST__;
if(success) *success=false;
return;
}
Bag bag;
bag=iterator->second;
if(bag.size!=sizeof(anything))
{
if(reason) *reason=__VALUE_SIZE_MISMATCH__;
if(success) *success=false;
return;
}
memcpy(anything,bag.ptr,sizeof(*anything));
free(bag.ptr);
if(success) *success=true;
}
bool Container::contains(string keyName)
{
auto iterator=dataSet.find(keyName);
return iterator!=dataSet.end();
}


#endif
