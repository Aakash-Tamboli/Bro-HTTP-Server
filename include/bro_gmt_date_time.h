#ifndef __BRO_GMTDATETIME__
#define __BRO_GMTDATETIME__ 3

#include<bro.h>
class GMTDateTime
{
private:
struct tm gmtDateTime;
bool isValid;
public:
GMTDateTime();
GMTDateTime(int,int,int,int,int,int);
int getDay();
int getMonth();
int getYear();
int getHour();
int getMinutes();
int getSecond();
int getWeekDay();
string stringify();
void addSeconds(int);
void addMinutes(int);
void addHours(int);
void addDays(int);
void addMonths(int);
void addYears(int);
};
ostream & operator<<(ostream &,GMTDateTime &);
#endif
