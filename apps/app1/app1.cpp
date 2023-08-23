#include "bro_v1.6.cpp"
// Bittu [ The Web Application Developer User of Bro Web Server ]
int main()
{
typedef struct _Student
{
int rollNumber;
char name[22];
char gender;
}Student;
Bro bro;

try
{
bro.setStaticResourcesFolder("static");

bro.get("/",[](Request &request,Response &response){

Student stud;
int sno;
char str[14];


response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title> My First Web App in Bro </title>
</head>
<body>
<table border=1>
<thead>
<tr>
<th>S.No</th>
<th>RollNumber</th>
<th>Name</th>
<th>Gender</th>
<th>Edit</th>
<th>Delete</th>
</tr>
</thead>
<tbody>
)"""";
FILE *file=fopen("student.dat","rb");
sno=0;
if(file!=NULL)
{
while(true)
{
fread(&stud,sizeof(Student),1,file);
if(feof(file)) break;
sno++;
response<<"<tr>";
sprintf(str,"%d",sno);
response<<"<td>"<<str<<"</td>";
sprintf(str,"%d",stud.rollNumber);
response<<"<td>"<<str<<"</td>";
response<<"<td>"<<stud.name<<"</td>";
if(stud.gender=='M')
{
response<<"<td><img src='images/male.png' width='24' height='24'></td>";
}
else
{
response<<"<td><img src='images/female.png' width='24' height='24'></td>";
}
response<<"<td><a href='editStudentForm?rollNumber="<<str<<"'>Edit</a></td>";
response<<"<td><a href='deleteStudent?rollNumber="<<str<<"'>Delete</a></td>";
response<<"</tr>";
}
fclose(file);
}
if(sno==0)
{
response<<"<tr><td colspan='6' align='center'> No Student </td></tr>";
}
response<<R""""(
</tbody>
</table>
<br>
<br>
<a href='addStudentForm.html'>Add Student</a>
</body>
</html>
)"""";
response.setContentType("text/html");
});


bro.get("/addStudent",[](Request &request,Response &response){
string rollNumber=request["rollNumber"]; // value we pass in subscript it should match with form component
string name=request["name"];
string gender=request["gender"];
FILE *file;
// ideally I have to check whethere roll Number exists or not
int vRollNumber=atoi(rollNumber.c_str());
file=fopen("student.dat","rb");
if(file!=NULL)
{
bool found=false;
Student studTmp;
while(true)
{
fread(&studTmp,sizeof(Student),1,file);
if(feof(file)) break;
if(studTmp.rollNumber==vRollNumber)
{
found=true;
break;
}
}
if(found)
{

response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title> (Student Add Form) </title>
<script>
function validateForm(frm)
{
var rollNumber=frm.rollNumber.value.trim();
if(rollNumber.length==0)
{
alert("Roll Number Required");
frm.rollNumber.focus();
return false;
}
rollNumber=parseInt(rollNumber);
if(isNaN(rollNumber))
{
alert("Invalid RollNumber");
frm.rollNumber.value='';
frm.rollNumber.focus();
return false;
}
if(rollNumber<=0)
{
alert("Invalid RollNumber");
frm.rollNumber.value='';
frm.rollNumber.focus();
return false;
}
var name=frm.name.value.trim();
if(name.length==0)
{
alert("Name Required");
frm.name.focus();
return false;
}
return true;
}
</script>
</head>
<body>
<h1>(Student Add Form)</h1>
)"""";
char line[301];
sprintf(line,"<div style='color:red'> That %d has been alloted</div>",vRollNumber);

response<<line;
response<<R""""(
<form action='addStudent' onsubmit='return validateForm(this)'>
Roll Number: 
<input type='text' name='rollNumber' id='rollNumber'>
<br>
Name: 
)"""";

sprintf(line,"<input type='text' name='name' maxlength='20' value='%s'><br>",name.c_str());
response<<line;


if(strcmp(gender.c_str(),"M")==0)
{
response<<R""""(
Gender &nbsp; &nbsp;<input type='radio' id='male' name='gender' value='M' checked>
Male &nbsp;&nbsp;&nbsp;
<input type='radio' id='female'name='gender' value='F'>
Female
)"""";
}
else
{
response<<R""""(
Gender &nbsp; &nbsp;<input type='radio' id='male' name='gender' value='M'>
Male &nbsp;&nbsp;&nbsp;
<input type='radio' id='female'name='gender' value='F' checked>
Female
)"""";
}
response<<R""""(
<br>
<br>
<button type='submit'>Add</button>
</form>
<br>
<a href='/'> HOME </a>
</body>
</html>
)"""";

response.setContentType("text/html");
return;
}
}
Student stud;
stud.rollNumber=atoi(rollNumber.c_str());
strcpy(stud.name,name.c_str());
if(gender[0]=='M')
{
stud.gender='M';
}
else
{
stud.gender='F';
}

file=fopen("student.dat","ab");
fwrite(&stud,sizeof(Student),1,file);
fclose(file);
const char *c=R""""(<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title> Student Added !!!</title>
</head>
<body>
<h3> Student Added </h3>
<form action='/'>
<button type='submit'>Click Here To Check</button>
</form>
</body>
</html>
)"""";
response<<c;
response.setContentType("text/html");
});

bro.get("/deleteStudent",[] (Request &request,Response &response){
string vRollNumber=request["rollNumber"];
int rollNumber=atoi(vRollNumber.c_str());
Student stud;
char line[201];
FILE *file,*tmp;
file=fopen("student.dat","rb");
tmp=fopen("tmp.tmp","wb");
while(true)
{
fread(&stud,sizeof(Student),1,file);
if(feof(file)) break;
if(stud.rollNumber==rollNumber) continue;
fwrite(&stud,sizeof(Student),1,tmp);
}
fclose(file);
fclose(tmp);
file=fopen("student.dat","wb");
tmp=fopen("tmp.tmp","rb");
while(true)
{
fread(&stud,sizeof(Student),1,tmp);
if(feof(tmp)) break;
fwrite(&stud,sizeof(Student),1,file);
}
fclose(file);
fclose(tmp);
response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title> Student Deleted !</title>
</head>
<body>
)"""";
sprintf(line,"<h1>Student Delete Whose RollNumber is %d</h1>",rollNumber);
response<<line;
response<<R""""(
<a href='/'> HOME </a>
</body>
</head>
)"""";
response.setContentType("text/html");
});

bro.get("/editStudentForm",[](Request &request,Response &response){
string vRollNumber=request["rollNumber"];
int rollNumber=atoi(vRollNumber.c_str());
Student stud;
FILE *file=fopen("student.dat","rb");
char line[300];
while(true)
{
fread(&stud,sizeof(Student),1,file);
if(feof(file)) break;
if(rollNumber==stud.rollNumber)
{
break;
}
}
fclose(file);
response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title> Edit Student</title>
<script>
function verify(frm)
{
return true;
}
</script>
</head>
<body>
<h1> Edit Student </h1>
<form action='editStudent' onsubmit='return verify(this)'>
RollNumber:
&nbsp;
)"""";

sprintf(line,"<input type='text' id='rollNumber' name='rollNumber' value='%d' readonly><br>",rollNumber);
response<<line;
sprintf(line,"Name:&nbsp;<input type='text' id='name' name='name' value='%s'><br>",stud.name);
response<<line;

if(stud.gender=='M')
{
response<<R""""(
Gender:
&nbsp;&nbsp;
<input type='radio' id='gender' name='gender' value='M' checked> Male
&nbsp;&nbsp;
<input type='radio' id='gender' name='gender' value='F'> Female
)"""";
}
else
{
response<<R""""(
Gender:
&nbsp;&nbsp;
<input type='radio' id='gender' name='gender' value='M'> Male
&nbsp;&nbsp;&nbsp;
<input type='radio' id='gender' name='gender' value='F' checked> Female
)"""";
}
response<<R""""(
<br>
<br>
<button type='submit'> Edit It</button>
</form>
</body>
</html>
)"""";
response.setContentType("text/html");
});


bro.get("/editStudent",[](Request &request,Response &response){
string vRollNumber=request["rollNumber"];
string name=request["name"];
string gender=request["gender"];
int rollNumber=atoi(vRollNumber.c_str());
char line[201];
Student stud,uStud;
uStud.rollNumber=rollNumber;
strcpy(uStud.name,name.c_str());
if(gender[0]=='M') uStud.gender='M';
else uStud.gender='F';

FILE *file,*tmp;
file=fopen("student.dat","rb");
tmp=fopen("tmp.tmp","wb");
while(true)
{
fread(&stud,sizeof(Student),1,file);
if(feof(file)) break;
if(stud.rollNumber==rollNumber) fwrite(&uStud,sizeof(Student),1,tmp);
else fwrite(&stud,sizeof(Student),1,tmp);
}
fclose(file);
fclose(tmp);
file=fopen("student.dat","wb");
tmp=fopen("tmp.tmp","rb");
while(true)
{
fread(&stud,sizeof(Student),1,tmp);
if(feof(tmp)) break;
fwrite(&stud,sizeof(Student),1,file);
}
fclose(file);
fclose(tmp);

response<<R""""(
<!DOCTYPE HTML>
<html lang='en'>
<head>
<meta charset='utf-8'>
<title> Updated !!! </title>
</head>
<body>
<h1> Record Updated</h1>
<a href='/'> Check Here </a>
</body>
</html>
)"""";
response.setContentType("text/html");
});

bro.listen(5050,[](Error &error){
if(error.hasError())
{
cout<<error.getError()<<endl;
return;
}
cout<<"Bro HTTP Server is Ready to accept Request on port 5050"<<endl;
});
}catch(string &exception)
{
cout<<exception<<endl;
}
return 0;
}
