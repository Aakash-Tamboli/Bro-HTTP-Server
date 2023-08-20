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
response<<"<td><a href='editStudent?rollNumber="<<str<<"'>Edit</a></td>";
response<<"<td><a href='/deleteStudent?rollNumber="<<str<<"'>Delete</a></td>";
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
char line[101];
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
strcpy(&stud.gender,gender.c_str());
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

