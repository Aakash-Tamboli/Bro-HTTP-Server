#include<iostream>
#include<time.h>
using namespace std;
class GMTDateTime
{
private:
struct tm gmtDateTime;
bool isValid;
public:
GMTDateTime() // to pick system date & time
{
time_t elapsedSeconds;
elapsedSeconds=time(NULL); // return number of seconds elapsed since 1 Jan 1970
if(elapsedSeconds==-1) // this will not happen but incase that's why I handle it
{
this->isValid=false;
this->gmtDateTime.tm_mday=0;
this->gmtDateTime.tm_mon=0;
this->gmtDateTime.tm_year=0;
this->gmtDateTime.tm_hour=0;
this->gmtDateTime.tm_min=0;
this->gmtDateTime.tm_sec=0;
return;
}
struct tm *gmt=gmtime(&elapsedSeconds); // According to Docs and mentor it returns static structure, so we are not responsible for releasing memory
this->gmtDateTime=*gmt;
this->isValid=true;
}
/*
I will clearly specify in docs that web developer should give month from jan to dec where jan represents 0 and dec represents 11
month(0-11)
*/
GMTDateTime(int day,int month,int year,int hour,int minute,int second)
{
struct tm tmptm;
tmptm.tm_mday=day;
tmptm.tm_mon=month;
tmptm.tm_year=year;
tmptm.tm_hour=hour;
tmptm.tm_min=minute;
tmptm.tm_sec=second;
if(mktime(&tmptm)==-1) // mktime will set wday part in the structure
{
this->isValid=false;
this->gmtDateTime.tm_mday=0;
this->gmtDateTime.tm_mon=0;
this->gmtDateTime.tm_year=0;
this->gmtDateTime.tm_min=0;
this->gmtDateTime.tm_sec=0;
return;
}
this->isValid=true;
this->gmtDateTime=tmptm;
}
int getDay()
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_mday;
}

int getMonth() // I will return in 1 to 12 form
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_mon+1;
}

int getYear() // returns actual year
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_year+1900;
}
int getHour()
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_hour;
}

int getMinutes()
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_min;
}
int getSecond()
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_sec;
}

int getWeekDay() // returns Sun to Sat in form of 0 to 6
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_wday;
}

string stringify()
{
if(!(this->isValid)) return string("");
char buffer[80];
strftime(buffer,80,"%a, %d %b %Y %H:%M:%S GMT",&(this->gmtDateTime));
return string(buffer);
}
};

ostream & operator<<(ostream &out,GMTDateTime &gmtDateTime)
{
out<<gmtDateTime.stringify();
return out;
}

int main()
{
GMTDateTime now;
cout<<now<<endl;
return 0;
}
