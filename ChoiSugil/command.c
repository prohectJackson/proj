#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void sCommand(char *buf)
{

	FILE *fin;
	fin = fopen("log.dat", "a+");

	if (fin == NULL){
		fprintf(stdout, "can't open file\n");
		exit(1);
	}
	fprintf(fin,"%s\n", buf);
	fclose(fin);


	printf("sCommand excution! : %s\n", buf);
	if (!strcmp(buf, "1personIn" ))
	{
		printf("1personIn : %s\n", buf);
	}

	if (!strcmp(buf, "1personOut" ))
	{
		printf("1personOut : %s\n", buf);
	}
}
