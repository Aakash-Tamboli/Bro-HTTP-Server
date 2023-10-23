#include<stdio.h>
#include<iostream>
#include<string.h>
#include<chrono>
using namespace std;
struct VMD
{
long start_position;
long end_position;
char var_name[256];
};
/*
the return type would represent an error number
if 0 is returned, it would mean that there are no errors
-1 stands for: unable to open .chtml file
-2 stands for: unable to open .vmd file
*/
int createVMD(const char *chtmlFileName,const char *vmdFileName)
{
long sp,ep;
char var_name[256];
int var_name_index;
int virtualStackSize;
FILE *chtmlFile,*vmdFile;
struct VMD vmd_record;
chtmlFile=fopen(chtmlFileName,"r");
if(chtmlFile==NULL) return -1;
vmdFile=fopen(vmdFileName,"wb");
if(vmdFile==NULL)
{
fclose(chtmlFile);
return -2;
}
fseek(chtmlFile,0,SEEK_END);
long fileLength=ftell(chtmlFile);
rewind(chtmlFile);
char m;
int x;
virtualStackSize=0;
sp=0;
ep=0;
x=1;
while(x<=fileLength)
{
m=fgetc(chtmlFile);
if(m=='$')
{
// there is no ${living${being}}
var_name_index=0;
virtualStackSize=1;
sp=x;
}
else if(m=='{')
{
if(x==sp+1)
{
if(virtualStackSize!=1)
{
virtualStackSize=0;
}
else
{
virtualStackSize=2;
var_name_index=0;
}
}
else
{
virtualStackSize=0;
}
}
else if(m=='}')
{
if(x-sp>2)
{
if(virtualStackSize!=2)
{
virtualStackSize=0;
}
else
{
ep=x;
var_name[var_name_index]='\0';
cout<<sp<<", "<<ep<<", "<<var_name<<endl;
vmd_record.start_position=sp;
vmd_record.end_position=ep;
strcpy(vmd_record.var_name,var_name);
fwrite(&vmd_record,sizeof(struct VMD),1,vmdFile);
sp=0;
ep=0;
var_name_index=0;
virtualStackSize=0;
}
}
else
{
virtualStackSize=0;
}
}
else if(virtualStackSize==2)
{
var_name[var_name_index++]=m;
}
x++;
}
fclose(chtmlFile);
fclose(vmdFile);
return 0;
}

int main()
{
auto start=chrono::system_clock::now();
cout<<createVMD("test2.chtml","test2.vmd")<<endl;
auto end=chrono::system_clock::now();
cout<<chrono::duration_cast<chrono::milliseconds>(end-start).count()<<" milliseconds"<<endl;
return 0;
}

