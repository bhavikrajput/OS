#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct symtab{
	int idx;
	char symb[10];
	int addr;
	int uf,df,cnt;
	struct symtab *next;
}*shead = NULL, *scur,*snew;

struct intcode{
	int addr,regcode;
	char opcode[20],oper[20];
	struct intcode *next;
}*ihead = NULL,*icur,*inew;

char *optab[11] = {"STOP","ADD","SUB","MULT","MOVER","MOVEM", "COMP","BC","DIV","READ","PRINT"};
char *regtab[11] = {"","AREG","BREG","CREG","DREG","LT","LE","EQ","GT","GE","ANY"};
int plc ,lc = 0;
int symcnt = 0;

int searchopcint(char opc[]);
void entersymtab(char a[],int);

int searchopc(char sym[10]){
	int i,flag = 0;
	for(i = 0; i <=10 ; i++){
		if(strcmp(optab[i],sym) == 0){
			flag = 1;
			break;
		}
	}
	if(flag == 1){
		return 1;
	}
	return 0;
}

void entersymtab(char sym[10],int value){
	struct symtab *temp;

	int flag = 0;

	for(temp = shead; temp != NULL; temp = temp->next){
		if(strcmp(temp->symb,sym) == 0){
			flag = 1;
			break;
		}
	}
	if(flag == 0){
		snew = (struct symtab *)malloc(sizeof(struct symtab));
		strcpy(snew->symb,sym);
		switch(value){
			case 0: sprintf(inew->oper,"<S,%d>",++symcnt);
				snew->idx = symcnt;
				snew->addr = -1;
				snew->uf = 1;
				snew -> cnt = 0;
				break;
			case 1: snew->idx = ++symcnt;
				snew->addr = plc;
				snew->df = 1;
				snew->cnt++;
				break;
		}
		snew -> next = NULL;
		if(shead == NULL){
			shead = scur = snew;
		}else{
			scur->next = snew;
			scur = snew;
		}
	}else{
		switch(value){
			case 0: sprintf(inew->oper,"<S,%d>",temp->idx);
				temp->uf = 1;
				break;
			case 1:
				if(temp->addr == -1){
					temp->addr = plc;
				}
				temp->cnt++;
				temp->df = 1;
				break;
		}
	}
}

int searchreg(char sym[10]){
	int i,flag = 0;
	for(i = 0; i <= 10; i++)
	{
		if(strcmp(regtab[i],sym) == 0)
		{
			flag = 1;
			break;
		}
	}
	
	printf("Register code %d \n",i);
	if(flag == 1){
		if(i <= 4){
			 inew->regcode = i;
		}else{
			inew->regcode = i - 4;
		}
		return 1;
	}else{
		return 0;
	}
}

int searchopcint(char sym[10]){
	int i,flag = 0;
	for(i = 0; i <= 10; i++){
		if(strcmp(optab[i],sym) == 0){
			flag = 1;
			break;
		}
	}
	if(flag == 1){
		sprintf(inew->opcode,"<IS,%d>",i);
		return 1;
	}else{
		return 0;
	}
}


int main(int argc, char *argv[]){
	struct symtab *s;
	struct intcode *i;

	FILE *fp;

	char progstmt[80],fname[10];
	char lbl[10],opc[10],reg[10],oper[10];
	char *dcconst;
	int ntok;

	if(argc!=2){
		printf("Error: Insufficient Arguments");
		exit(1);
	}else{
		strcpy(fname,argv[1]);
	}

	fp = fopen(fname,"r");
	if(fp == NULL){
		printf("Error : File not found");
		exit(1);
	}

	while(!feof(fp)){
		inew = (struct intcode *)malloc(sizeof(struct intcode));

		strcpy(progstmt,"");
		strcpy(lbl,"");
		strcpy(opc,"");
		strcpy(reg,"");
		strcpy(oper,"");
		fgets(progstmt,80,fp);
		ntok = sscanf(progstmt,"%s%s%s%s",lbl,opc,reg,oper);
		switch(ntok){
			case 1:
				searchopcint(lbl);
				inew->addr = plc;
				plc = lc;
				lc++;
				break;
			case 2:
				if(strcmp(lbl,"START") == 0){
					strcpy(inew->opcode,"<AD,1>");
					strcpy(oper,opc);
					strcpy(opc,lbl);
					strcpy(lbl,"");
					sprintf(inew->oper,"<C,%s>",oper);
					lc = atoi(oper);
				}else{							//READ A
					if(searchopc(lbl)){
						plc  = lc;
						inew->addr = plc;
						strcpy(oper,opc);
						strcpy(opc,lbl);
						strcpy(lbl,"");
						searchopcint(opc);
						entersymtab(oper,0);
						lc++;
					}else{					//HALT STOP
						plc = lc;
						inew->addr = plc;
						searchopcint(opc);
						entersymtab(lbl,1);
						lc++;
					}
				}
				break;
			case 3:
				if(strcmp(opc,"DS") == 0){
					plc = lc;
					inew->addr = plc;
					strcpy(inew->opcode,"<DL,1>");
					entersymtab(lbl,1);
					lc += atoi(reg);
				}
				if(strcmp(opc,"DC") == 0){
					plc = lc;
					inew->addr = plc;
					strcpy(inew->opcode,"<DL,2>");
					entersymtab(lbl,1);
					lc++;
					dcconst = strtok(reg,"'");
					sprintf(inew->oper,"<C,%s>",dcconst);
				}
				if((strcmp(opc,"DS")!=0) && (strcmp(opc,"DC")!=0)){
					if(searchopc(lbl)){
						plc = lc;
						inew->addr = plc;
						strcpy(oper,reg);
						strcpy(reg,opc);
						strcpy(opc,lbl);
						strcpy(lbl,"");
						searchopcint(opc);
						searchreg(reg);
						entersymtab(oper,0);
						lc++;
					}else{
						plc = lc;
						inew->addr = plc;
						strcpy(oper,reg);
						strcpy(reg,"");
						searchopcint(opc);
						entersymtab(lbl,1);
						entersymtab(oper,0);
						lc++;
					}
				}
				break;
			case 4:
				plc = lc;
				inew->addr = plc;
				searchopcint(opc);
				searchreg(reg);
				entersymtab(lbl,1);
				entersymtab(oper,0);
				lc++;
				break;
		}
		inew->next = NULL;

		if(ihead == NULL){
			ihead = icur = inew;
		}else{
			icur->next = inew;
			icur = inew;
		}
	}
	printf("\n Symbol Table\n\n");
	printf("Sr.no\tName\tAddress\tUsed\tDefine\n");

	for(s = shead;s!=NULL;s = s->next){
		printf("\n%d\t%s\t%d\t%d\t%d\t",s->idx,s->symb,s->addr,s->uf,s->df);
	}
	printf("\n");
	for(s = shead ; s!= NULL; s = s->next){
		if(s->df == 0){
			printf("\nError: Symbol %s is used but not Defined",s->symb);
			exit(0);
		}
		if(s->uf == 0){
			printf("\nWarnig: SYmbol %s is Defined but not used",s->symb);
			//exit(0);
		}
		if(s->cnt >1){
			printf("\nRedeclaration of Symbol %s",s->symb);
			exit(0);
		}
	}
	printf("\n");
	printf("Intermediate Code:\n");
	for(i = ihead; i!=NULL; i= i->next){
		printf("\n%d\t%s\t%d\t%s\n",i->addr,i->opcode,i->regcode,i->oper);
	}
	fclose(fp);
	return 0;
}
