#include<bro_template_engine.h>
void TemplateEngine::createVMDFileName(const char *chtmlFileName,char *vmdFileName)
{
char *dotPtr;
const char *ptr;
ptr=chtmlFileName;
while(*ptr!='\0') ptr++;
while(ptr>=chtmlFileName)
{
if(*ptr=='/')
{
chtmlFileName=ptr+1;
break;
}
ptr--;
}
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
void TemplateEngine::createVMDFile(const char *chtmlFileName,const char *pathToVMDFile)
{
long sp,ep;
char var_name[256];
int var_name_index;
int virtualStackSize;
FILE *chtmlFile,*vmdFile;
struct VMD vmd_record;
chtmlFile=fopen(chtmlFileName,"rb"); // rb mode for capturing each byte including \r\n(during pressing enter key) which is kept when somebody write .chtml using notepad
if(chtmlFile==NULL)
{
// code to sendBack 404 error
return;
}
vmdFile=fopen(pathToVMDFile,"wb");
if(vmdFile==NULL)
{
// code to send back 500 internal server error
fclose(chtmlFile);
return;
}
fseek(chtmlFile,0,SEEK_END);
long fileLength=ftell(chtmlFile);
rewind(chtmlFile);
char m;
int x;
virtualStackSize=0;
sp=0;
ep=0;
x=0;
while(x<fileLength)
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
}
void TemplateEngine::processCHTMLFile(const char *chtmlFileName,Request &request,int clientSocketDescriptor)
{
/*
later on this will be implemented
string folder("bro_private");
string subFolder=string("bro_private")+string(PATH_SEPRATOR)+string("vmdFiles");
if(!FileSystemUtility::directoryExists(folder.c_str()))
{
// I will implements later on
}
if(!FileSystemUtility::directoryExists(subFolder.c_str()))
{
// I will implements later on
}
*/

if(!FileSystemUtility::directoryExists("vmd_files"))
{
if(!FileSystemUtility::createDirectory("vmd_files"))
{
// I will implements later on
}
}
char vmdFileName[257];
createVMDFileName(chtmlFileName,vmdFileName);
string folderName=string("vmd_files");
string pathToVMDFile=folderName+string(PATH_SEPRATOR)+string(vmdFileName);
bool generateVMDFile=false;
if(FileSystemUtility::fileExists(pathToVMDFile.c_str()))
{
if(FileSystemUtility::getLastUpdatedTime(chtmlFileName)>FileSystemUtility::getLastUpdatedTime(pathToVMDFile.c_str()))
{
generateVMDFile=true;
}
}
else
{
generateVMDFile=true;
}
if(createVMDFile)
{
createVMDFile(chtmlFileName,pathToVMDFile.c_str());
}
// process the .chtml file pickup info from .vmd file
// the code to calculate response Size starts here
FILE *chtmlFile=fopen(chtmlFileName,"rb");
FILE *vmdFile=fopen(pathToVMDFile.c_str(),"rb");
fseek(chtmlFile,0,SEEK_END);
long fileLength=ftell(chtmlFile);
rewind(chtmlFile);
long responseSize=fileLength;
string data;
struct VMD vmdRecord;
while(1)
{
fread(&vmdRecord,sizeof(struct VMD),1,vmdFile);
if(feof(vmdFile)) break;
responseSize=responseSize-(vmdRecord.end_position-vmdRecord.start_position)+1;
data=request.getCHTMLVariable(vmdRecord.var_name);
responseSize=responseSize+data.length();
}// loop ends
cout<<"Response Size is: "<<responseSize<<endl;
// the code to process .chtml file starts here
string mimeType("text/html");
char header[200];
sprintf(header,"HTTP/1.1 200 OK\r\n ContentType:%s\r\n Content-Length: %ld\r\n Connection: close\r\n\r\n",mimeType.c_str(),responseSize);
send(clientSocketDescriptor,header,strlen(header),0);
long bytesLeftToRead;
int bytesToRead;
char buffer[4096];
rewind(vmdFile);
long tmpBytesLeftToRead;
long bytesProcessedFromFile=0;
while(true)
{
fread(&vmdRecord,sizeof(struct VMD),1,vmdFile);
if(feof(vmdFile)) break;
tmpBytesLeftToRead=vmdRecord.start_position-bytesProcessedFromFile;
bytesToRead=4096;
while(tmpBytesLeftToRead>0)
{
if(tmpBytesLeftToRead<bytesToRead) bytesToRead=tmpBytesLeftToRead;
fread(buffer,bytesToRead,1,chtmlFile);
if(feof(chtmlFile)) break;
bytesProcessedFromFile=bytesProcessedFromFile+bytesToRead;
send(clientSocketDescriptor,buffer,bytesToRead,0);
tmpBytesLeftToRead=tmpBytesLeftToRead-bytesToRead;
}// inner loop ends
fread(buffer,(vmdRecord.end_position-vmdRecord.start_position)+1,1,chtmlFile);
bytesProcessedFromFile=bytesProcessedFromFile+(vmdRecord.end_position-vmdRecord.start_position)+1;
if(request.isCHTMLVariablecontains(vmdRecord.var_name))
{
data=request.getCHTMLVariable(vmdRecord.var_name);
cout<<"Extract and dispatch to client: "<<data<<endl;
send(clientSocketDescriptor,data.c_str(),data.length(),0);
}
} // outer loop ends
// remaing portion of .chtml file after dynamic data.
bytesLeftToRead=fileLength;
bytesLeftToRead=bytesLeftToRead-bytesProcessedFromFile;
bytesToRead=4096;
while(bytesLeftToRead>0)
{
if(bytesLeftToRead<bytesToRead) bytesToRead=bytesLeftToRead;
fread(buffer,bytesToRead,1,chtmlFile);
if(feof(chtmlFile)) break;
send(clientSocketDescriptor,buffer,bytesToRead,0);
bytesLeftToRead=bytesLeftToRead-bytesToRead;
}// loop ends
// the code to process .chtml file ends here
fclose(chtmlFile);
fclose(vmdFile);
}
