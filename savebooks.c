#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXTITL 40
#define MAXAUTHOR 40
#define MAXBOOKS 100			//max number of books
char *s_gets(char *st,int n);

struct book{			//book template
	char title[MAXTITL];
	char author[MAXAUTHOR];
	float value;
};

int main(void)
{
	struct book library[MAXBOOKS];	//array of structs
	int count=0;
	int index,filecount;
	FILE *pbooks;
	int size=sizeof(struct book);

	if((pbooks=fopen("book1.dat","a+b"))==NULL)
	{
		fputs("Can't open book.dat file\n",stderr);
		exit(1);
	}
	rewind(pbooks);			//go to file start
	while(count<MAXBOOKS && fread(&library[count],size,
					      1,pbooks)==1)
	{
		if(count==0)
			puts("Current contents of book.dat:");
		printf("\n%s by %s: $%.2f\n",library[count].title,
			library[count].author,library[count].value);
		count++;
	}

	filecount=count;		//keeps track of how many structures were read.

	if(count == MAXBOOKS)
	{
		fputs("The book.dat file is full.",stderr);
		exit(2);
	}
	puts("Please add new book title.");
	puts("Press [enter] at the start of a line to stop.");
	while(count<MAXBOOKS && s_gets(library[count].title,MAXTITL)!= NULL
			     && library[count].title[0]!='\0')
	{
		puts("Now enter the author.");
		s_gets(library[count].author,MAXAUTHOR);
		puts("Now enter the value.");
		scanf("%f",&library[count++].value);
		while(getchar()!='\n')
			continue;
		if(count<MAXBOOKS)
			puts("Enter next title.");
	}

	if(count>0)
	{
		puts("Here is the list of your books:");
		for(index=0;index<count;index++)
		{
			printf("\n%s by %s: $%.2f\n",library[index].title,
				library[index].author,library[index].value);
		}
		fwrite(&library[filecount],size,count-filecount,
				pbooks);
		
	}
	else
	   puts("\nNo books were found!");

	puts("\nEnd of session.\n");

	fclose(pbooks);

	return 0;
	

}

char *s_gets(char *st,int n)
{
	char *ret_val;
	char *find;

	ret_val=fgets(st,n,stdin);

	if(ret_val)
	{
		find=strchr(st,'\n');

		if(find)
			*find='\0';

		else
			while(getchar()!='\n')
				continue;
	}

	return ret_val;
}
