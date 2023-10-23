#include<bro_gmt_date_time.h>

GMTDateTime::GMTDateTime() // to pick system date & time
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

GMTDateTime::GMTDateTime(int day,int month,int year,int hour,int minute,int second)
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
int GMTDateTime::getDay()
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_mday;
}

int GMTDateTime::getMonth() // I will return in 1 to 12 form
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_mon+1;
}

int GMTDateTime::getYear() // returns actual year
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_year+1900;
}
int GMTDateTime::getHour()
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_hour;
}

int GMTDateTime::getMinutes()
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_min;
}
int GMTDateTime::getSecond()
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_sec;
}

int GMTDateTime::getWeekDay() // returns Sun to Sat in form of 0 to 6
{
if(!(this->isValid)) return -1;
return this->gmtDateTime.tm_wday;
}

string GMTDateTime::stringify()
{
if(!(this->isValid)) return string("");
char buffer[80];
strftime(buffer,80,"%a, %d %b %Y %H:%M:%S GMT",&(this->gmtDateTime));
return string(buffer);
}
void GMTDateTime::addSeconds(int seconds)
{
if(this->isValid)
{
this->gmtDateTime.tm_sec+=seconds;
mktime(&(this->gmtDateTime)); // mktime will be do necesary adjustment in other attribtes
}
}
void GMTDateTime::addMinutes(int minutes)
{
if(this->isValid)
{
this->gmtDateTime.tm_min+=minutes;
mktime(&(this->gmtDateTime)); // mktime will be do necesary adjustment in other attribtes
}
}

void GMTDateTime::addHours(int hours)
{
if(this->isValid)
{
this->gmtDateTime.tm_hour+=hours;
mktime(&(this->gmtDateTime)); // mktime will be do necesary adjustment in other attribtes
}
}

void GMTDateTime::addDays(int days)
{
if(this->isValid)
{
this->gmtDateTime.tm_mday+=days;
mktime(&(this->gmtDateTime)); // mktime will be do necesary adjustment in other attribtes
}
}

void GMTDateTime::addMonths(int months)
{
if(this->isValid)
{
this->gmtDateTime.tm_mon+=months;
mktime(&(this->gmtDateTime)); // mktime will be do necesary adjustment in other attribtes
}
}

void GMTDateTime::addYears(int years)
{
if(this->isValid)
{
this->gmtDateTime.tm_year+=years;
mktime(&(this->gmtDateTime)); // mktime will be do necesary adjustment in other attribtes
}
}

ostream & operator<<(ostream &out,GMTDateTime &gmtDateTime)
{
out<<gmtDateTime.stringify();
return out;
}

