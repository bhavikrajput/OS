#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<string.h>
void
search (char c,char *fn, char *s)
{
  int i=1,cnt=0,j=0, handle;
  char ch,buff[80],*p;
  printf("\n c=%c \t s=%s \t fn=%s ", c, s, fn);
  if ((handle = open (fn, O_RDONLY)) == -1)
    {
      printf ("File %s not found\n", fn);
      return;
    }
  switch(c)
  {
  case 'f':while(read(handle,&ch,1)!=0)
  {
  if(ch=='\n')
  {
  buff[j]='\0';
  j=0;
  if(strstr(buff,s)!=NULL)
  {
  printf("%d : %s\n",i,buff);
  break;
  }
  i++;
  }
  else
    buff[j++]=ch;
  }
  break;
  
  
case 'c':while(read(handle,&ch,1)!=0)
  {
  if(ch=='\n')
  {
  buff[j]='\0';
  j=0;
  if(strstr(buff,s)!=NULL)
  {
  p=buff;
  while((p=strstr(p,s))!=NULL)
  {
  cnt++;
  p++;
  }
  }
  }
   buff[j++]=ch;
  }
  printf("Total no. of occurance=%d",cnt);
  break;

case 'a':while(read(handle,&ch,1)!=0)
  {
  if(ch=='\n')
  {
  buff[j]='\0';
  j=0;
  if(strstr(buff,s)!=NULL)
  printf("%d:%s\n",i,buff);
  i++;
  }
  else
   buff[j++]=ch;
  }
  }
  close(handle);
 }
  
main ()
{
  char command[80], t1[20], t2[20], t3[20], t4[20];
  int n, pid, e;
 // system ("clear");
  while (1)
    {
      printf ("my_shell$");
      fflush (stdin);
      fgets (command,80, stdin);
      n = sscanf (command, "%s %s %s %s", t1, t2, t3, t4);
      switch (n)
	{
	case 1:
	  /*if (!fork ())
	    {
	      execlp (t1, t1, NULL);
	      perror (t1);
	    }
	  break;*/
	if(strcasecmp(t1,"exit")==0)
	    exit(0);
	   else
   {
    pid=fork();
    if(pid==0)
    {
     e=execlp(t1,t1,(char*)0);
     if(e<0)
      printf("Error Occurred\n");
    }
    else
     waitpid();
   }
     break;
	case 2:
	  /*if (!fork ())
	    {
	      execlp (t1, t1, t2, NULL);
	      perror (t1);
	    }
	  break;*/
 pid=fork();
    if(pid==0)
    {
     e=execlp(t1,t1,t2,(char*)0);
     if(e<0)
      printf("Error Occurred\n");
    }
    else
     waitpid();
     break;
      case 3:
	  /*if (!fork ())
	    {
	      execlp (t1, t1, t2, NULL);
	      perror (t1);
	    }
	  break;*/
pid=fork();
    if(pid==0)
    {
     e=execlp(t1,t1,t2,t3,(char*)0);
     if(e<0)
      printf("Error Occurred\n");
    }
    else
     waitpid();
     break;
     
	case 4:
	  if (strcmp (t1, "search") == 0)
	    search (t2[0],t3,t4);
	  else
	    {
	      if (!fork ())
		{
		  execlp (t1, t1, t2, t3, NULL);
		  perror (t1);
		}
	    }
	  }
    }
}
