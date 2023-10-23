#include<string.h>
#include<iostream>
using namespace std;
void createVMDFileName(const char *chtmlFileName,char *vmdFileName)
{
char *dotPtr;
while(*chtmlFileName)
{
if(*chtmlFileName=='.') dotPtr=vmdFileName;
*vmdFileName=*chtmlFileName;
chtmlFileName++;
vmdFileName++;
}
*vmdFileName='\0';
strcpy(dotPtr+1,"vmd");
}
int main()
{
char vmdFileName[257];
createVMDFileName("whatever.chtml",vmdFileName);
cout<<vmdFileName<<endl;
return 0;
}
