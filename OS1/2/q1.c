#include"ASM.h"

int main(int argc, char *argv[])
{
	if(argc!=2)
	{
		printf("\nPlease enter the valid arguments!\n");
		exit(0);
	}
	FILE *fp;
	int n,LC=0,f,i;
	char instr[50],str[50];
	fp=fopen(argv[1],"r");
	if(fp==NULL)
	{
		printf("\nFile could not open!\n");
		exit(0);
	}
	struct node* temp;

	while(fgets(instr,50,fp)!=NULL)
	{
		n=0;
		char *s=instr;
		char *str1;
		char t1[10]={ },t2[10]={ },t3[10]={ },t4[10]={ };

		while((str1=strtok_r(s,"\n ,\t",&s)))
		{	
			n++;
			switch(n)
			{
				case 1: strcpy(t1,str1);
					break;
				case 2: strcpy(t2,str1);
					break;
				case 3: strcpy(t3,str1);
					break;
				case 4: strcpy(t4,str1);
					break;
				default:printf("\nInvalid Statement!\n");
					break;
			}
		}
		if(LC==0)
		{
			LC=atoi(t2);
			f=0;
		}
		else if(f==0)
			f=1;
		else if(f!=2)
			LC++;
		else
			f=1;


		if(f==0)
			printf("\t %s \t %s \t %s \t %s\n",t1,t2,t3,t4);
		else
			printf("%d\t %s \t %s \t %s \t %s\n",LC,t1,t2,t3,t4);

	if(imparative(t1)==-1 && declarative(t1)==0 && ass_dir(t1)==0 && cond_code(t1)==0 && reg_code(t1)==0 && isnum(t1)==0)
		{
			if(search(t1)==-1 && strcmp(t1,"")!=0)
				insert(t1,LC,1);
			else
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcasecmp(temp->symbol,t1)==0)
					{
						if(temp->address==0)
						{
							temp->address=LC;
							temp->df=1;
						}
						else
							temp->ef=1;
						break;
					}
				}
			}
		}

	if(imparative(t2)==-1 && declarative(t2)==0 && ass_dir(t2)==0 && cond_code(t2)==0 && reg_code(t2)==0 && isnum(t2)==0)
		{
			if(search(t2)==-1 && strcmp(t2,"")!=0)
				insert(t2,0,-1);
			else
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcasecmp(temp->symbol,t2)==0)
					{
						temp->uf=1;
						break;
					}
				}
			}
		}

		if(declarative(t2))
		{
			if(search(t1)==-1)
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcasecmp(temp->symbol,t1)==0 && temp->address==0)
					{
						temp->address=LC;
						temp->df=1;
						break;
					}
					
				}
			}
			if(strcasecmp(t2,"DS")==0)
			{
				LC+=atoi(t3);
			}
			else
			{
				char *con = strtok(t3,"'");
				LC++;
			}				
			f=2;
		}
	if(declarative(t2)==0)
	{
	if(imparative(t3)==-1 && declarative(t3)==0 && ass_dir(t3)==0 && cond_code(t3)==0 && reg_code(t3)==0 && isnum(t3)==0)
		{
			if(search(t3)==-1 && strcasecmp(t3,"")!=0)
				insert(t3,0,-1);
			else
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcasecmp(temp->symbol,t3)==0)
					{
						temp->uf=1;
						break;
					}
				}
			}
		}
	}
	
if(imparative(t4)==-1 && declarative(t4)==0 && ass_dir(t4)==0 && cond_code(t4)==0 && reg_code(t4)==0 && isnum(t4)==0)
		{
			if(search(t4)==-1 && strcasecmp(t4,"")!=0)
				insert(t4,0,-1);
			else
			{
				for(temp=root;temp!=NULL;temp=temp->next)
				{
					if(strcasecmp(temp->symbol,t4)==0)
					{
						temp->uf=1;
						break;
					}
				}
			}
		}	
	}
	display();
	errors();
	printf("\n");

	rewind(fp);
	LC=0;	
	while(fgets(instr,50,fp)!=NULL)
	{
		n=0;
		char *s=instr;
		char *str1;
		char t[4][10]={"\0"};

		while((str1=strtok_r(s,"\n ,\t\0",&s)))
		{	
			switch(n)
			{
				case 0: strcpy(t[n++],str1);
					break;
				case 1: strcpy(t[n++],str1);
					break;
				case 2: strcpy(t[n++],str1);
					break;
				case 3: strcpy(t[n++],str1);
					break;
				default:printf("\nInvalid Statement!\n");
					break;
			}
		}
		if(LC==0)
		{
			LC=atoi(t[1]);
			f=0;
		}
		else if(f==0)
			f=1;
		else if(f!=2)
			LC++;
		else
			f=1;
	
		char sclass[3]={ };
		int code=0;
		char reg=0;
		char op=' ';
		int no=0;
		int f1=0;
		int address = LC;
		for(i=0;i<n;i++)
		{
			if(imparative(t[i])!=-1 || declarative(t[i])!=0 || ass_dir(t[i])!=0)
			{
				strcpy(sclass,check_class(t[i]));
				if(strcasecmp(sclass,"IS")==0)
				{
					code=imparative(t[i]);
				}
				else if(strcasecmp(sclass,"DL")==0)
				{
					code=declarative(t[i]);
				}
				else if(strcasecmp(sclass,"AD")==0)
				{
					code=ass_dir(t[i]);
				}
			}
			else if(cond_code(t[i])!=0 || reg_code(t[i])!=0)
				reg = check_reg(t[i]);
			else if(search(t[i])!=-1 && f1==0 && i!=0)
			{
				op='S';
				no=search(t[i]);
				f1=1;
			}
			else if(isnum(t[i]) && f1==0 && strcmp(t[i],"")!=0 && i!=0)
			{
				op='C';
				no = atoi(t[i]);
				f1=1;
			}
		}
		if(declarative(t[1]))
		{
			op='C';
			if(strcasecmp(t[1],"DC")==0)
			{
				char *z = strtok(t[2],"\'");
				no = atoi(z);
			}
			else
				no = atoi(t[2]);
		}
		else if(imparative(t[0])==-1 && declarative(t[0])==0 && ass_dir(t[0])==0 && cond_code(t[0])==0 && reg_code(t[0])==0 && isnum(t[0])==0)
		{
			address = addressOf(t[0]);
		}

		insert_IC(address,sclass,code,reg,op,no);

		if(declarative(t[1]))
		{
			if(strcasecmp(t[1],"DC")==0)
				LC++;
			else
				LC+=atoi(t[2]);
			f=2;	
		}
		
	}
	display_IC();

	int op,add,reg,sym,pos;
	char name[20];
	struct IC *t;
	printf("\nEnter the file name to store the machine code: ");
	scanf("%s",name);
	fp = fopen(name,"w");

	printf("\nMachine Code:\n");
	for(t=head; t!=NULL; t=t->next)
	{
		if(strcasecmp(t->sclass,"AD")!=0 && strcasecmp(t->sclass,"DL")!=0)
		{
			add = t->address;
			op = t->code;
			reg = t->reg;
			pos = t->cons;
			sym = 0;
			for(temp=root,i=0 ; temp!=NULL && i<pos; temp=temp->next,i++)
			{
				sym = temp->address;
			}
			printf("%d %02d%d%03d\n",add,op,reg,sym);
			fprintf(fp,"%d %02d%d%03d\n",add,op,reg,sym);
		}
		if(strcmp(t->sclass,"DC")==0 && t->code==1)
		{
			printf("%d %d\n",t->address,t-sym);
			fprintf(fp,"%d %d\n",t->address,t-sym);
		}
	}
	fclose(fp);
}	
