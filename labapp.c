#include<stdio.h>
#include<stdlib.h>
#include"zoomrecs.h"

int main(int argc, char *argv[]){
	//open the input csv file, for each line of csv file, call addZoomRecord 
	char line[1000];
	
	FILE *outputFile;
	struct ZoomRecord *head = NULL;
	//open input csv file
	FILE *fp = fopen(argv[1], "rt");
	
	//1st line = header, skip it
	fgets(line,1000,fp);

	//fgets before starting while loop to avoid hitting EOF 
	fgets(line, 1000, fp);
	//while EOF hasn't been hit, call addZoomRecord for each line of the input CSV
	while (!feof(fp)) {
		head = addZoomRecord(head, line);
		fgets(line,1000,fp);
	}
	fclose(fp);
	
	//open output csv file to write to it, call generateAttendance with head of list + the file pointer
	outputFile = fopen(argv[2], "wt");
	generateAttendance(head, outputFile);

	while (head != NULL) {
		struct ZoomRecord* next = head->next;
		free(head);
		head = next;
	}
}



