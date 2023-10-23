#include<bro_header_utility.h>

void HeaderUtility::parseHeader(const char *header,map<string,string> &headerFieldMap)
{
const char *startingPoint,*endingPoint,*colonPtr,*ptr;
ptr=header;
while(*ptr)
{
colonPtr=NULL;
startingPoint=ptr;
while(*ptr && *ptr!='\r' && *ptr!='\n')
{
if(colonPtr==NULL && *ptr==':') colonPtr=ptr;
ptr++;
}
endingPoint=ptr-1;
if(*ptr=='\r') ptr+=2;
else ptr++;
if(startingPoint==ptr || colonPtr==NULL) // really, this will never happen if client is browser
{
ptr++;
continue;
}
string fieldName(startingPoint,colonPtr-startingPoint);
if(*(colonPtr+1)==' ') startingPoint=colonPtr+2;
else startingPoint=colonPtr+1;
string fieldValue(startingPoint,endingPoint-startingPoint+1);
transform(fieldName.begin(),fieldName.end(),fieldName.begin(),::tolower);
headerFieldMap.insert(pair<string,string>(fieldName,fieldValue));
if(*ptr=='\r' && *(ptr+1)=='\n') break; // header ends
}// loop ends
}
