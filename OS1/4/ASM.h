/*Header File*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

const char regs[4][8]={"AREG","BREG","CREG","DREG"};
const char impers[11][8]={"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
const char assd[5][8]={"START","END","EQU","LTORG","ORIGIN"};
const char cond[6][8]={"LT","LE","EQ","GT","GE","ANY"};
const char dec[2][8]={"DC","DS"};

struct node
{
	char symbol[10];
	int df,uf,address,ef;
	struct node *next;
};

struct node *root=NULL;

int imparative(char s[])
{
	int i;
	for(i=0;i<11;i++)
	{
		if(strcasecmp(s,impers[i])==0)
			return i;
	}
	return -1;
}

int declarative(char s[])
{
	int i;
	for(i=0;i<2;i++)
	{
		if(strcasecmp(s,dec[i])==0)
			return i+1;
	}
	return 0;
}

int ass_dir(char s[])
{
	int i;
	for(i=0;i<5;i++)
	{
		if(strcasecmp(s,assd[i])==0)
			return i+1;
	}
	return 0;
}

int cond_code(char s[])
{
	int i;
	for(i=0;i<6;i++)
	{
		if(strcasecmp(s,cond[i])==0)
			return i+1;
	}
	return 0;
}

int reg_code(char s[])
{
	int i;
	for(i=0;i<4;i++)
	{
		if(strcasecmp(s,regs[i])==0)
			return i+1;
	}
	return 0;
}

int isnum(char s[])
{
	int i;
	for(i=0;s[i]!='\0';i++)
		if(!isdigit(s[i]))
			return 0;
	return 1;
}

void insert(char t[],int LC,int f)
{
	struct node *temp;
	temp = (struct node*)malloc(sizeof(struct node));
	strcpy(temp->symbol,t);
	if(f==1)
	{temp->df=1;temp->uf=0;temp->address=LC;temp->ef=0;}
	else if(f==-1)
	{temp->df=0;temp->uf=1;temp->address=0;temp->ef=0;}
	temp->next=NULL;

	if(root==NULL)
		root=temp;
	else
	{
		struct node *p;
		p=root;
		while(p->next!=NULL)
		{	p=p->next;	}
		p->next=temp;
	}
}

void display()
{
	struct node *t;
	printf("\nSymbol\tAddress\tUsed\tDefined");
	for(t=root;t!=NULL;t=t->next)
	{
		printf("\n %s \t %d \t %d \t %d",t->symbol,t->address,t->uf,t->df);
	}
}

int search(char s[])
{
	struct node *temp;
	int pos;
	for(temp=root,pos=1 ; temp!=NULL; temp=temp->next,pos++)
	{
		if(strcmp(temp->symbol,s)==0)
		{
			return pos;
		}
	}
	return -1;
}

int addressOf(char s[])
{
	struct node *t;
	for(t=root; t!=NULL; t=t->next)
	{
		if(strcmp(t->symbol,s)==0)
		{
			return(t->address);
		}
	}
	return -1;
}
void errors()
{
	int n=1;
	struct node *t;
	//printf("\n\nErrors: ");
	for(t=root;t!=NULL;t=t->next)
	{
		if(t->uf==1 && t->df==0)
		{
			printf("\n%d. Symbol %s is used but not defined",n++,t->symbol);
		}
		if(t->df==1 && t->ef==1)
		{
			printf("\n%d. Re-declaration of Symbol %s",n++,t->symbol);
		}
	}
//	printf("\n\nWarnings: "); n=1;
        for(t=root;t!=NULL;t=t->next)
        {
                if(t->df==1 && t->uf==0)
                {
                        printf("\n%d. Symbol %s is defined but not used",n++,t->symbol);
                }
	}
}


struct IC
{
	int address;
	char sclass[3];
	int code;
	char reg;
	char op;
	int cons;
	struct IC *next;
};

struct IC *head = NULL;

void insert_IC(int address, char sc[], int code, char reg, char op, int cons)
{
	struct IC *temp;
	temp = (struct IC*)malloc(sizeof(struct IC));
	temp->address=address;
	strcpy(temp->sclass,sc);	temp->code=code;
	temp->reg=reg;
	temp->op=op;	temp->cons=cons;
	temp->next=NULL;

	if(head==NULL)
		head=temp;
	else
	{
		struct IC *p;
		p=head;
		while(p->next!=NULL)
		{	p=p->next;	}
		p->next=temp;
	}
}


char *check_class(char s[])
{
	if(imparative(s)!=-1)
		return"IS";
	else if(declarative(s)!=0)
		return "DL";
	else if(ass_dir(s)!=0)
		return "AD";
	else
		return"";
}

int check_reg(char s[])
{
	int n=cond_code(s);
	if(n!=0)
		return n;
	n = reg_code(s);
		return n;
}

void display_IC()
{
	struct IC *t;
	printf("\nIntermediate Code:\n\n");
	for(t=head;t!=NULL;t=t->next)
	{
		if(t->reg!=0 && t->op!=' ')
		{
			printf("%d \t <%s,%d> %d <%c,%d>\n",t->address,t->sclass,t->code,t->reg,t->op,t->cons);
		}
		else if(t->reg==0 && t->op!=' ')
		{
			printf("%d \t <%s,%d> <%c,%d>\n",t->address,t->sclass,t->code,t->op,t->cons);
		}
		else if(t->reg==0 && t->op==' ')
		{
			printf("%d \t <%s,%d>\n",t->address,t->sclass,t->code);
		}
	}
}
