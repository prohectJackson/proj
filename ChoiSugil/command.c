#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "command.h"

void sCommand(char *buf)
{

	FILE *fin, *fperson;
	Person p1;

	// person.dat 사람 데이터 읽기.
	fperson = fopen("person.dat", "r");
	if (fin == NULL){
		fprintf(stdout, "can't open person.dat file\n");
		exit(1);
	}
	fscanf(fperson, "%d %d %d %d", &p1.room1, &p1.room2, &p1.room3, &p1.room4);
	fclose(fperson);

	fin = fopen("log.dat", "a+");
	if (fin == NULL){
		fprintf(stdout, "can't open log.dat file\n");
		exit(1);
	}
	fprintf(fin,"%s\n", buf);
	fclose(fin);


	printf("sCommand excution! : %s\n", buf);
	if (!strcmp(buf, "1personIn" ))
	{
		printf("1personIn : %d\n", ++p1.room1);
	}

	if (!strcmp(buf, "1personOut" ))
	{
		if (p1.room1 == 0) printf("there is no person in room1 : %d", --p1.room1);
		printf("there is no person in room1 %d", p1.room1);
	}

	// person.dat 사람 데이터 쓰기.
	fperson = fopen("person.dat", "w");
	if (fin == NULL){
		fprintf(stdout, "can't open person.dat file\n");
		exit(1);
	}
	fprintf(fperson, "%d %d %d %d", p1.room1, p1.room2,p1.room3,p1.room4);
	fclose(fperson);
}
