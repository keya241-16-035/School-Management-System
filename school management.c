#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct student{
char na[30];
char cl[10];
int rl;
char date[12];
}s;
FILE*fp;
long sz=sizeof(s);
void input();
int main()
{
 int cho;
 while(1){
 system("cls");
 printf("<==School Management==> \n");
 printf("1.Take Admission \n");
 printf("2.Student Info \n");
 printf("3.Search \n");
 printf("4.Modify \n");
 printf("5.Delete \n");
 printf("6.Sort by roll \n");
 printf("0.Exit \n\n");
 printf("Enter Your Choice: \n");
 scanf("%d",&cho);
 switch(cho){
 case 0:
     exit(0);
 case 1:
     input();
 break;
 case 2:
     display();
 break;
 case 3:
     search();
 break;
 case 4:
     modify();
 break;
 case 5:
     del();
 break;
 case 6:
   sort();
 break;

 default:
    printf("Enter valid choice!Please enter a valid option.\n");
break;
 }

 printf("\n\n Press To Continue.....\n");
 getch();
}
return 0;
}
void input(){

char myDate[12];
time_t t= time(NULL);
struct tm tm=*localtime(&t);
sprintf(myDate, "%02d/%02d/%d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
strcpy(s.date,myDate);
fp=fopen("student.txt","ab");
printf("Enter Student Name:");
fflush(stdin);
gets(s.na);
printf("Enter Class:");
fflush(stdin);
gets(s.cl);
printf("Enter Roll:");
scanf("%d",&s.rl);
fwrite(&s,sizeof(s),1,fp);
printf("Record Successfully Saved....");
fclose(fp);
}
void display(){
system("cls");
printf("<==Student Info==>\n");
printf("%-30s %-20s %-10s %s\n", "Name", "Class", "Roll", "Date");
fp=fopen("Student.txt","rb");

while(fread(&s,sizeof(s),1,fp)==1)
{
printf("%-30s %-20s %-10d %s\n", s.na, s.cl, s.rl, s.date);
}
fclose(fp);
}
void search()
{
 int cho;
 while(1)
 {
     system("cls");
     printf("<==Search==> \n");
     printf("1.Search By Roll \n");

     printf("0.Back To Main Menu Immediately");
     printf("\n\n Enter Choice:");
     scanf("%d",&cho);
     switch(cho)
     {
    case 0: main();
    break;
    case 1: searchByRoll();
    break;
    default:
    printf("Invalid Choice");
    }
    getch();
}
}
void searchByRoll()
 {
 int rl,f=0;
 printf("Enter Roll to Search:");
 scanf("%d",&rl);
 printf("%-30s %-20s %-10s %s\n", "Name", "Class", "Roll", "Date");
fp=fopen("Student.txt","rb");
while(fread(&s,sizeof(s),1,fp)==1)
{
if(rl==s.rl)
{
 f=1;

printf("%-30s %-20s %-10d %s\n", s.na, s.cl, s.rl, s.date);
break;
}
}
fclose(fp);
if(f==0)
{
    printf("Record not found");
}
else
{
   printf("Record Found Successfully");
}
 }
void modify()
{
 int rl,f=0;
 printf("Enter roll to modify:");
 scanf("%d",&rl);
 fp=fopen("student.txt","rb+");
 while(fread(&s,sizeof(s),1,fp)==1)
{
if(rl==s.rl)
{
 f=1;
 printf("Enter new name:");
fflush(stdin);
gets(s.na);
printf("Enter new class");
fflush(stdin);
gets(s.cl);
printf("Enter new roll:");
scanf("%d",&s.rl);
fseek(fp,-sizeof(s),1);
fwrite(&s,sizeof(s),1,fp);
fclose(fp);
break;
}
}
if(f==0)
{
    printf("Record not found");
}
else
    {
    printf("Record Modified Successfully");
    }
}
void del()
{
    int rl,f=0;
    printf("Enter roll to delete:");
    scanf("%d",&rl);
    FILE*ft;
    fp=fopen("student.txt","rb");
    ft=fopen("temp.txt","ab");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        if(rl==s.rl)
        {
            f=1;
        }
   else
    {
    fwrite(&s,sizeof(s),1,ft);
   }
}
fclose(fp);
fclose(ft);
remove("student.txt");
rename("temp.txt","student.txt");
if(f==0)
{
    printf("Record not found");
}
else{
    printf("Record Deleted Successfully");
}
}

void sort()
{
 int c=0,i,j;
 struct student s1[50],t;
 system("cls");
 printf("<==Sort by roll==> \n\n");
 printf("%-30s %-20s %-10s %s\n", "Name", "Class", "Roll", "Date");
 fp=fopen("student.txt","rb");
while(fread(&s,sizeof(s),1,fp)==1)
{
  s1[c++]= s;
}
for(i=0;i<c-1;i++)
{
 for(j=i+1;j<c;j++)
 {
  if(s1[i].rl>s1[j].rl)
  {
     t=s1[i];
     s1[i]=s1[j];
     s1[j]=t;
  }
 }
}
for(i=0;i<c;i++)


printf("%-30s %-20s %-10d %s\n",s1[i].na,s1[i].cl,s1[i].rl,s1[i].date);
 fclose(fp);
}




