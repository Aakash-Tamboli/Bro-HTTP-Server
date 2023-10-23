#include<stdio.h>
#include<iostream>
using namespace std;
int main()
{
FILE *f;
f=fopen("abc.ttt","r");
long length;
fseek(f,0,SEEK_END);
length=ftell(f);
rewind(f);
cout<<"Length of File is: "<<length<<endl;
char buffer[4096];
int bytesToRead=4096;
int bytesLeftToRead=length;
int i;
while(bytesLeftToRead>0)
{
if(bytesLeftToRead<bytesToRead) bytesToRead=bytesLeftToRead;
fread(buffer,bytesToRead,1,f);
cout<<"(";
for(i=0;i<bytesToRead;i++) cout<<"["<<(int)buffer[i]<<"]";
cout<<")"<<endl;
bytesLeftToRead=bytesLeftToRead-bytesToRead;
}
cout<<"Bytes Left to Read: "<<bytesLeftToRead<<endl;
fclose(f);
return 0;
}
