#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int mem[1000];
int reg[4];

int PC;
int last;
int F=0;


void Load()
{
	FILE *fp;
	char filename[30];

	FILE *fp1;

	int address;
	int code;
	int i;

	printf("\nEnter the File name:");

	scanf("%s",filename);

	fp=fopen(filename,"r");

	if(fp==NULL)
	{
		printf("\nInvalid filename");

		exit(0);

	}

	else
	{
		while(!feof(fp))
		{
			fscanf(fp,"%d %d",&address,&code);

			if(address!=-1)
				last=address;

			if(address==-1)
				PC=code;

		}

		fclose(fp);

		fp1=fopen(filename,"r");

		i=PC;


		while(!feof(fp1))
		{
			fscanf(fp1,"%d %d",&address,&code);

			if(address!=-1)
				mem[i++]=code;
		}

		fclose(fp1);

		printf("\nContents of File have been loaded onto memory");
	
		printf("\nStarting address is %d",PC);

		printf("\nEnding address is %d",last);

		F=1;

	}

}



void Print()
{
	int i;

	printf("\nContents of memory are:");

	for(i=PC;i<=last;i++)
	{
		printf("\n %d \t %d",i,mem[i]);

	}

}


void Execute(int choice)
{
	int temp;
	int instr;
	int reg1,target;
	int flag;
	int i;
	int op1,op2;
	i=PC;


	while(1)
	{
		temp=mem[i++];

		target=temp%1000;
		instr=(temp/1000)/10;
		reg1=(temp/1000)%10;

		if(choice==0)
			printf("\n Areg: %d \t Breg: %d \t Creg: %d \t Dreg: %d",reg[0],reg[1],reg[2],reg[3]);

		if(instr==0)
			break;

		switch(instr)
		{
			case 1: if(reg1<1 || reg1>4)
				{
					printf("\nInvalid register");
					exit(0);
				}

				else
				{
					reg[reg1-1]=reg[reg1-1]+mem[target];

				}

				break;

			case 2: if(reg1<1 || reg1>4)
				{
					printf("\nInvalid register");
					exit(0);
				}

				else
				{
					reg[reg1-1]=reg[reg1-1]-mem[target];
				}
				break;

			case 3: if(reg1<1 || reg1>4)
				{
					printf("\nInvalid register");
					exit(0);
				}

				else
				{
					reg[reg1-1]=reg[reg1-1]*mem[target];
				}
				break;

			case 4: if(reg1<1 || reg1>4)
				{
					printf("\nInvalid register");
					exit(0);
				}

				else
				{
					reg[reg1-1]=mem[target];
				}

				break;

			case 5: if(reg1<1 || reg1>4)
				{
					printf("\nInvalid register");
					exit(0);
				}
				else
				{
					mem[target]=reg[reg1-1];
				}
				break;

			case 6: op1=reg[reg1-1];
				op2=mem[target];
				break;

			case 7: if(reg1<1 || reg1>6)
				{
					printf("Invalid condition code");
					exit(0);
				}

				else
				{
					switch(reg1)
					{
						case 1://LT
							if(op1<op2)
								flag=1;
							else
								flag=0;
							break;

						case 2://LE
							if(op1<=op2)
								flag=1;
							else
								flag=0;
							break;

						case 3://EQ
							if(op1==op2)
								flag=1;
							else
								flag=0;
							break;

						case 4://GT
							if(op1>op2)
								flag=1;
							else
								flag=0;
							break;

						case 5: //GE
							if(op1>=op2)
								flag=1;
							else
								flag=0;
							break;

						case 6://ANY
							flag=1;
							break;
					}

					if(flag==1)
						i=target;

				}

					break;

			case 8:if(reg1<1 || reg1>4)
			       {
				       printf("\nInvalid register");
				       exit(0);
			       }

			       else
			       {
				       reg[reg1-1]=reg[reg1-1]/mem[target];
			       }

			       break;

			 case 9: printf("\nEnter value:");

				 scanf("%d",&mem[target]);

				 break;

			case 10: printf("\nThe output is: %d",mem[target]);

				 break;

		}

	}

}


void main()
{
	int i;

	int choice;

	for(i=0;i<4;i++)
	{
		reg[i]=0;

	}

	while(1)
	{
		printf("\n1.Load Program\n2.Print \n3.Execute \n4.Trace \n5.Exit\nEnter the Choice:");

		scanf("%d",&choice);


		switch(choice)
		{
			case 1: Load();
				break;

			case 2: if(F==0)
					printf("\nProgram not loaded in memory");

				else
					Print();

				break;

			case 3: if(F==0)
					printf("\nProgram not loaded in memory");

				else
					Execute(1);

				break;

			case 4: if(F==0)
					printf("\nProgram not loaded in memory");

				else
				{
					for(i=0;i<4;i++)
					{
						reg[i]=0;
					}

					Execute(0);
				}

				break;

			case 5: exit(0);
				break;

		}

	}

}





