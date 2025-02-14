/*
Yenkel jaoui 324523075, liav huli 314917808 , yehuda harush 324023332
libary project.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define size 30
struct libary
{
	char* bookname;
	char* writer;
	int nummofbook;
	int loanbook;
	int publishingyear;
};
struct libary* myupdate(struct libary*, int*);
struct libary* addbook(struct libary* , int*);
struct libary* myremove(struct libary*, int*);
void findinfo(struct libary*,int);
int find_size();
void print(struct libary*,int);
struct libary* fill(int);
void writeonfile(struct libary*,int);


int main()
{
	int size1;
	int x=0;
	size1 = find_size();
	struct libary* p = fill(size1);
	while (x != 6)
	{	
		printf("1.find\n2.add\n3.remove\n4.update\n5.print\n6.exit\n");
		scanf_s("%d", &x);
		switch (x)
		{
		case 1:
			findinfo(p, size1);
			break;
		case 2:
			p = addbook(p, &size1);
			break;
		case 3:
			p = myremove(p, &size1);
			break;
		case 4:
			p = myupdate(p, &size1);
			break;
		case 5:
		print(p, size1);
			break;

		default:
			if (x != 6)
				printf("not in the range\n");
			else
				printf("goodbye!");
		}
	}
	writeonfile(p, size1);
	for (int i = 0; i < size1; i++)
		free(p[i].bookname,p[i].writer);
	free(p);
	return 0;
	
}

//���� ��� ��� ����� ����
int find_size()
{
	FILE* fp;
	int x = fopen_s(&fp, "libary.txt", "r");
	char namebook[size];
	char namewriter[size];
	int numberbook, loanbook, year;
	int count=0;

	if (x !=0)
	{
		printf("File doesnt exist");
		return 0;
	}
	while (fscanf(fp, "%s %s %d %d %d",namebook,namewriter,&numberbook,&loanbook,&year)!=EOF)
	{
		count++;
	}
	fclose(fp);
	return count;
}
struct libary* fill(int size1)
{
	char name[size];
	char wrname[size];
	int t, y, z;
	struct libary* p;
	FILE* fp = NULL;
	p = (struct libary*)malloc(size1 * sizeof(struct libary));
	if (p == NULL)
	{
		printf("error malloc failed");
		return 0;
	}
	int x = fopen_s(&fp, "libary.txt", "r");
	if (x)
	{
		printf("File doesnt exist\n");
		return 0;
	}
	for (int i = 0; i < size1; i++)
	{

		fscanf(fp,"%s %s %d %d %d",name,wrname,&t,&y,&z);
		p[i].bookname = (char*)malloc((strlen(name) + 1) * sizeof(char));
		if (p[i].bookname==NULL)
		{
			printf("error malloc failed");
			return 0;
		}
		strcpy(p[i].bookname, name);
		p[i].writer = (char*)malloc((strlen(wrname) + 1) * sizeof(char));
		if (p[i].writer == NULL)
		{
			printf("error malloc failed");
			return 0;
		}
		strcpy(p[i].writer, wrname);
		p[i].nummofbook = t;
		p[i].loanbook = y;
		p[i].publishingyear = z;
	}
	fclose(fp);
	return p;
}

//����� ����
void findinfo(struct libary *p,int size1)
{
	int option;
	char name[size];
	printf("enter your option , 1 : writer search , 2 : book name search .\n");
	scanf("%d", &option);
	if (option==1)
	{
		printf("enter the writer you looking for\n");
		getchar();
		gets_s(name, size);
		for (int i = 0; i < size1; i++)
		{
			if (strcmp(p[i].writer, name) == 0)
			{
				printf("\nbook name : %s\nwriter name : %s\nnumber of books : %d\nnumber of loan books : %d\npublishing year : %d\n\n\n", p[i].bookname, p[i].writer, p[i].nummofbook, p[i].loanbook, p[i].publishingyear);
			}
			else
			{
				printf("not found\n");
			}
		}
	}
	if (option == 2)
	{
		printf("enter the book you looking for\n");
		getchar();
		gets_s(name, size);
		for (int i = 0; i < size1; i++)
		{
			if (strcmp(p[i].bookname, name) == 0)
			{
				printf("book name : %s\nwriter name : %s\nnumber of books : %d\nnumber of loan books : %d\npublishing year : %d\n\n", p[i].bookname, p[i].writer, p[i].nummofbook, p[i].loanbook, p[i].publishingyear);
			}
			else
			{
				printf("not found\n");
			}
		}
		
	}
	if (option != 1 && option != 2)
	{
		printf("error worng number\n");
	}
}
struct libary* addbook(struct libary* info, int *size1)
{
	char name[size];
	char wrname[size];
	int num,j=0,f=0;
	printf("enter how much books you want to add\n");
	scanf_s("%d", &num);
	info =(struct libary*)realloc(info, (*size1 + num)*sizeof(struct libary));
	if (info == NULL)
	{
		printf("error realloc failed");
		return 0;
	}
	getchar();
	for (int i = *size1; i < *size1+num; i++)
	{	
		printf("enter your bookname\n");
		gets_s(name,size);
		info[i].bookname = (char*)malloc((strlen(name) + 1) * sizeof(char));
		if (info[i].bookname == NULL)
		{
			printf("error malloc failed");
			return 0;
		}
		strcpy(info[i].bookname, name);
		printf("enter your writer name\n");
		gets_s(wrname,size);
		info[i].writer = (char*)malloc((strlen(wrname) + 1) * sizeof(char));
		if (info[i].writer == NULL)
		{
			printf("error malloc failed");
			return 0;
		}
		strcpy(info[i].writer, wrname);
		printf("enter numofbooks:\n");
		scanf_s("%d",&info[i].nummofbook);
		printf("enter loanbook number:\n");
		scanf_s("%d",&info[i].loanbook);
		printf("enter publish year:\n");
		scanf_s("%d",&info[i].publishingyear);
	}
	*size1 = num + *size1;
	return info;
}
struct libary* myremove(struct libary *info, int *size1)
{
	int place,count=0;
	char namebook[size];
	struct libary* newinfo = NULL;
	printf("enter the name of book you want to remove:\n");
	getchar();
	gets_s(namebook,size);
	for (int i = 0; i < *size1; i++)
	{
		if (strcmp(info[i].bookname,namebook)==0)
		{
			count++;
			place = i;
		}

	}
	if (count == 0)
	{
		printf("no book\n");
		return info;
	}
	newinfo = (struct libary*)malloc((*size1 - 1) * sizeof(struct libary));
	for (int i = 0; i < place; i++)
	{
		newinfo[i].bookname = (char*)malloc((strlen(info[i].bookname) + 1) * sizeof(char));
		if (newinfo[i].bookname==NULL)
		{
			printf("malloc failed");
				return 0;
		}
		strcpy(newinfo[i].bookname, info[i].bookname);
		newinfo[i].writer = (char*)malloc((strlen(info[i].writer) + 1) * sizeof(char));
		if (newinfo[i].writer == NULL)
		{
			printf("malloc failed");
			return 0;
		}
		strcpy(newinfo[i].writer, info[i].writer);
		newinfo[i].nummofbook = info[i].nummofbook;
		newinfo[i].loanbook = info[i].loanbook;
		newinfo[i].publishingyear = info[i].publishingyear;
	}
	for (int i = place+1; i < *size1; i++)
	{
		newinfo[i-1].bookname = (char*)malloc((strlen(info[i].bookname) + 1) * sizeof(char));
		if (newinfo[i-1].bookname == NULL)
		{
			printf("malloc failed");
			return 0;
		}
		strcpy(newinfo[i-1].bookname, info[i].bookname);
		newinfo[i-1].writer = (char*)malloc((strlen(info[i].writer) + 1) * sizeof(char));
		if (newinfo[i-1].writer == NULL)
		{
			printf("malloc failed");
			return 0;
		}
		strcpy(newinfo[i-1].writer, info[i].writer);
		newinfo[i-1].nummofbook = info[i].nummofbook;
		newinfo[i-1].loanbook = info[i].loanbook;
		newinfo[i-1].publishingyear = info[i].publishingyear;
	}
	*size1 = *size1 - 1;
	return newinfo;
}
struct libary* myupdate(struct libary*info,int *size1)
{
	int x,num,count=0;
	char name[size];
	printf("enter your option\n1:add book\n2:remove book\n");
	scanf_s("%d", &x);
	if (x==1)
	{
		printf("which book you want to add:\n");
		getchar();
		gets_s(name,size);
		for (int i = 0; i < *size1; i++)
		{
			if (strcmp(info[i].bookname,name)==0)
			{
				printf("there are %d books , how much books you want to add?\n",info[i].nummofbook);
				scanf_s("%d", &num);
				info[i].nummofbook += num;
				count++;
			}
		}
		if (count==0)
			printf("book doesnt exists\n");
	}
	if (x==2)
	{
		printf("which book you want to remove\n");
		getchar();
		gets_s(name, size);
		for (int i = 0; i < *size1; i++)
		{
			if (strcmp(info[i].bookname, name) == 0)
			{
				printf("there are %d books , how much books you want to remove?\n",info[i].nummofbook);
				scanf_s("%d", &num);
				if ( (info[i].nummofbook - num)<0)
				{
					printf("error\n");
				}
				info[i].nummofbook -= num;
				count++;
			}
		}
		if (count == 0)
			printf("book doesnt exists\n");
	}
	return info;
}


void print(struct libary* info,int size1)
{
	for (int i = 0; i < size1; i++)
		printf("%s %s %d %d %d\n", info[i].bookname, info[i].writer, info[i].nummofbook, info[i].loanbook, info[i].publishingyear);
}


void writeonfile(struct libary* p, int size1)
{
	FILE* fp = NULL;
	int x=fopen_s(&fp, "libary.txt", "w");
	if (x!=0)
	{
		printf("file doesnt exists");
	}
	for (int i = 0; i < size1; i++)
		fprintf(fp, "%s %s %d %d %d\n", p[i].bookname, p[i].writer, p[i].nummofbook, p[i].loanbook, p[i].publishingyear);
	fclose(fp);
}
