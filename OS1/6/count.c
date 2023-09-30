/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
C#, VB, Perl, Swift, Prolog, Javascript, Pascal, HTML, CSS, JS
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>

void count(int in, char t[])
{
 int f=0, w=0, l=0, ch=0;
 char c,prev;
 while(read(in,&c,1))
 {
  if(f==0)
  {
   if(c!=' ' && c!='\n' && c!='\t')
    w++;
   ch++;
   f=1;
   prev=c;
   
  if(c=='\n')
   l++;
  }
  else
   {
    if(c=='\n')
     l++;
    else if( (prev=='\t' || prev==' ' || prev=='\n') && (c!='\t' && c!=' ') )
     w++;
    ch++;
    prev=c;
   }
 }
 if(strcasecmp(t,"C")==0)
  printf("No. of Characters : %d",ch);
 if(strcasecmp(t,"W")==0)
  printf("No. of Words :%d",w);
 if(strcasecmp(t,"L")==0)
  printf("No. of Lines :%d",l);
}

main(int argc, char* argv[])
{
 char cmd[80],*token, t[10][20];
 int pid, ntoken, e, in;
 do
 {
  printf("\nMyShell$ ");
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
     waitpid(NULL);
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
     waitpid(NULL);
     break;
     
   case 3:
   if(strcasecmp(t[0],"count")==0)
   {
    if(strcasecmp(t[1],"C")==0 || strcasecmp(t[1],"W")==0 || strcasecmp(t[1],"L")==0)
    {
     in=open(t[2],O_RDONLY);
     if(in==-1)
     {
      printf("\nERROR : File Not Found");
      continue;
     }
     else
     {
      count(in,t[1]);
      close(in);
      continue;
     }
    }
   }
   pid=fork();
    if(pid==0)
    {
     e=execlp(t[0],t[0],t[1],t[2],(char*)0);
     if(e<0)
      printf("Error Occurred\n");
    }
    else
     waitpid(NULL);
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
     waitpid(NULL);
     break;
  }
 }while(1);
}
