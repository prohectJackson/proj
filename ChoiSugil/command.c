#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "command.h"

void sCommand(char *buf)
{

	FILE *fin, *frperson, *fwperson;
	Person p1;

	// person.dat 사람 데이터 읽기.
	frperson = fopen("person.dat", "r");
	if (frperson == NULL){
		fprintf(stdout, "can't open read person.dat file\n");
		exit(1);
	}
	fscanf(frperson, "%d %d %d %d", &p1.room1, &p1.room2, &p1.room3, &p1.room4);
	fclose(frperson);

	fin = fopen("log.dat", "a+");
	if (fin == NULL){
		fprintf(stdout, "can't open log.dat file\n");
		exit(1);
	}
	//datetime
	time_t rawtime = time(NULL);
	struct tm *ptm = localtime(&rawtime);
	fprintf(fin,"month: %02d day: %02d  %02d:%02d:%02d :: %s\n", ptm->tm_mon, ptm->tm_mday,ptm->tm_hour, ptm->tm_min, ptm->tm_sec, buf);
	fclose(fin);


	if (!strcmp(buf, "1personIn" ))
		printf("1personIn : %d\n", ++p1.room1);
	if (!strcmp(buf, "2personIn" ))
		printf("2personIn : %d\n", ++p1.room2);
	if (!strcmp(buf, "3personIn" ))
		printf("3personIn : %d\n", ++p1.room3);
	if (!strcmp(buf, "4personIn" ))
		printf("4personIn : %d\n", ++p1.room4);

	if (!strcmp(buf, "1personOut" ))
	{
		if (p1.room1 == 0) printf("there is no person in room1 : %d\n", p1.room1);
		else {
			printf("there is %d person.\n", --p1.room1);
			if (p1.room1 == 0) {
				printf("turn off Light\n");
				strcpy(buf, "1turnOff");
			}
		}
	}
	if (!strcmp(buf, "2personOut" ))
	{
		if (p1.room2 == 0) printf("there is no person in room2 : %d\n", p1.room2);
		else {
			printf("there is %d person.\n", --p1.room2);
			if (p1.room2 == 0) {
				printf("turn off Light\n");
				strcpy(buf, "2turnOff");
			}
		}
	}
	if (!strcmp(buf, "3personOut" ))
	{
		if (p1.room3 == 0) printf("there is no person in room1 : %d\n", p1.room3);
		else {
			printf("there is %d person.\n", --p1.room3);
			if (p1.room3 == 0) {
				printf("turn off Light\n");
				strcpy(buf, "3turnOff");
			}
		}
	}
	if (!strcmp(buf, "4personOut" ))
	{
		if (p1.room4 == 0) printf("there is no person in room1 : %d\n", p1.room4);
		else {
			printf("there is %d person.\n", --p1.room4);
			if (p1.room4 == 0) {
				printf("turn off Light\n");
				strcpy(buf, "4turnOff");
			}
		}
	}

	// person.dat 사람 데이터 쓰기.
	fwperson = fopen("person.dat", "w");
	if (fwperson == NULL){
		fprintf(stdout, "can't open write person.dat file\n");
		exit(1);
	}
	fprintf(fwperson, "%d %d %d %d", p1.room1, p1.room2, p1.room3, p1.room4);
	fclose(fwperson);
}
