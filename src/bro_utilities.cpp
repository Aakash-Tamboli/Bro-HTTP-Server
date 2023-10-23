
#include<bro_utilities.h>

BroUtilities::BroUtilities()
{
}
bool BroUtilities::isHexChar(char c)
{
if(c>='0' && c<='9') return true;
if(c>='a' && c<='f') return true;
if(c>='A' && c<='F') return true;
return false;
}

void BroUtilities::decodePercentEncoding(char *encodedString,char *decodedString)
{
int i,decodedAscii;
i=0;
while(*encodedString!='\0')
{
if(*encodedString=='+')
{
decodedString[i]=' ';
i++;
encodedString++;
continue;
}
if(*encodedString!='%')
{
decodedString[i]=*encodedString;
i++;
encodedString++;
continue;
}
encodedString++;
if(isHexChar(*encodedString) && isHexChar(*(encodedString+1)))
{
sscanf(encodedString,"%2x",&decodedAscii);
decodedString[i]=decodedAscii;
i++;
encodedString+=2;
}
else
{
i=0;
break;
}
}// loop ends
decodedString[i]='\0';
}

void BroUtilities::loadMIMETypes(map<string,string> &mimeTypesMap)
{
FILE *file;
file=fopen("bro-data/mime.types","r");
if(file==NULL) return;
char *mimeType;
char *extension;
char line[200];
int x;

while(true)
{
fgets(line,200,file);
if(feof(file)) break;
if(line[0]=='#') continue;
// logic to remove \r\n or \n from end of the string starts here
x=strlen(line)-1;
while(true)
{
if(line[x]=='\r' || line[x]=='\n')
{
line[x]='\0';
x--;
}
else
{
break;
}
}
// logic to remove \r\n or \n from end of the string ends here
mimeType=&line[0];
for(x=0;line[x]!='\t';x++);
line[x]='\0';
x++;
while(line[x]=='\t') x++;

while(true)
{
extension=&line[x];
while(line[x]!='\0' && line[x]!=' ') x++;
if(line[x]=='\0')
{
// add entry to map and break the loop
mimeTypesMap.insert(pair<string,string>(string(extension),string(mimeType)));
// cout<<extension<<"  , "<<mimeType<<endl;
break;
}
else
{
// placing \0 on xth index,add entry to map and increment the value of x
line[x]='\0';
mimeTypesMap.insert(pair<string,string>(string(extension),string(mimeType)));
//cout<<extension<<"  , "<<mimeType<<endl;
x++;
}
}// parsing loop ends here
}// extrating and insert in map loop ends
fclose(file);
}

