/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>

main(int argc, char* argv[])
{
 char cmd[80],*token, t[10][20];
 int pid, ntoken, e;
 do
 {
  printf("MyShell$ ");
  gets(cmd);
  token=strtok(cmd, " ");
  strcpy(t[0],token);
  ntoken=0;
  while(token)
  {
   ntoken++;
   token=strtok(NULL," ");
   if(token!=NULL)
    strcpy(t[ntoken], token);
  }
 switch(ntoken)
 {
  case 1:
   if(strcasecmp(t[0],"exit")==0)
    exit(0);
   else
   {
    pid=fork();
    if(pid==0)
    {
     e=execlp(t[0],t[0],(char*)0);
     if(e<0)
      printf("Error Occurred\n");
    }
    else
     wait(NULL);
   }
     break;
  
  case 2:
 
    pid=fork();
    if(pid==0)
    {
     e=execlp(t[0],t[0],t[1],(char*)0);
     if(e<0)
      printf("Error Occurred\n");
    }
    else
     wait(NULL);
     break;
     
   case 3:
   pid=fork();
    if(pid==0)
    {
     e=execlp(t[0],t[0],t[1],t[2],(char*)0);
     if(e<0)
      printf("Error Occurred\n");
    }
    else
     wait(NULL);
     break;
     
    case 4:
     pid=fork();
    if(pid==0)
    {
     e=execlp(t[0],t[0],t[1],t[2],t[3],(char*)0);
     if(e<0)
      printf("Error Occurred\n");
    }
    else
     wait(NULL);
     break;
  }
 }while(1);
}
