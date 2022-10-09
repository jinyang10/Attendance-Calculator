#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"zoomrecs.h"

//function to convert lab letter to corresponding integer
int convertLetter(char* labLetter) {
	int i = 0;
	char labletter = labLetter[0];
	char A = 'A';
	if (labletter == A) {
		return i; 
	} else {
		i = i + (labletter - A);
		return i;
	}
}

//addZoomRecord called once for each time a line (record) of lab attendance is read from input file
//searches for the student's info in a linked list (uses email as search attribute) 
//if found, updates the duration associated with that lab for that student
//if not found, creates a new ZoomRecord for the student, and adds it to the linked list 
// -- maintains list in order of email ids alphabetically
//line[] will be an fgets from the file

struct ZoomRecord* addZoomRecord(struct ZoomRecord *ptr, char line[]) {
	char labletter[2]; 
	int flag = 0;
	struct ZoomRecord *cur = NULL;
	cur = ptr;
	int labIndex;
	// a line has email, name, lab, duration

	//it's the first node
	if (cur == NULL) {
		struct ZoomRecord *node = (struct ZoomRecord *) malloc(sizeof(struct ZoomRecord));
		if (node == NULL) {
			printf("Unable to allocate memory\n");
			exit(1);
		}
		node->next = NULL;
		//user email 
		char* token = strtok(line, ",");
		strcpy(node->email, token);
		//name
		token = strtok(NULL, ",");
		strcpy(node->name, token);
		//lab letter
		token = strtok(NULL, ",");
		strcpy(labletter, token);
		labIndex = convertLetter(labletter);
		//lab duration
		token = strtok(NULL, ",");

		int i;
		for (i=0; i<9; i++) {
			node->durations[i] = 0;
		}
		int labDur; 
		labDur = atoi(token);
		node->durations[labIndex] = labDur;
		return node;

	//already nodes present in list
	} else {
		struct ZoomRecord* head = ptr;

		//user email
		char* token = strtok(line, ",");
		char lineEmail[61];
		strcpy(lineEmail, token);
		//user name
		token = strtok(NULL, ",");
		char name[61];
		strcpy(name, token);
		//lab letter
		token = strtok(NULL, ",");
		strcpy(labletter, token);
		labIndex = convertLetter(labletter);
		//lab duration
		token = strtok(NULL, ",");
		int labDur;
		labDur = atoi(token);

		int flag = 0;
		//search for student's email in the linked list
		while (cur != NULL) {
			char listEmail[61];
			strcpy(listEmail, cur->email);
			//found student's email in linked list
			if (strcmp(listEmail, lineEmail) == 0) {
				//update their lab duration for that lab
				cur->durations[labIndex] = cur->durations[labIndex] + labDur;
				flag = 1;
				break;
			}
			cur = cur->next;
		}
		//student wasn't found in linked list
		if (flag == 0) {

			//initialize new node for the student
			struct ZoomRecord* node = (struct ZoomRecord *) malloc (sizeof(struct ZoomRecord));	
			strcpy(node->email, lineEmail);
			strcpy(node->name, name);
			int i;
			for (i=0; i<9; i++) {
				node->durations[i] = 0;
			}
			node->durations[labIndex] = labDur;

			//need to find where to place user in the linked list
			cur = ptr;
			struct ZoomRecord *Next = cur->next;
			while (cur != NULL) {
				//reached end of list, must add to the end of the list
				if (strcmp(lineEmail, cur->email) > 0 && Next == NULL) {
					cur->next = node;
					break;
				}
				//greater than current, smaller than next -> insert here
				if (strcmp(lineEmail, cur->email) > 0 && strcmp(lineEmail, Next->email) < 0) {
					cur->next = node;
					node->next = Next;
					break;
				}
				//smaller than current and current == head -> insert as head
				if (strcmp(lineEmail, cur->email) < 0 && cur == head) {
					head = node;
					node->next = cur;
					break;
				}
				//must iterate thru list deeper
				if (strcmp(lineEmail, cur->email) > 0 && strcmp(lineEmail, Next->email) > 0) {
					cur = cur->next;
					Next = Next->next;
				}
			}
		}
		return head;
	}

}

//called once, after all info has been read into the linked list
//reads thru linked list and writes to the output file 
void generateAttendance(struct ZoomRecord *ptr, FILE *fp) {
	char *studName;
	char *studEmail;
	int labIndex;
	struct ZoomRecord *cur = NULL; 
	cur = ptr;
	int validLabs = 0;
	float percentLabs;
	
	fprintf(fp, "User Email,Name (Original Name),A,B,C,D,E,F,G,H,I,Attendance (Percentage)");
	fprintf(fp, "\n");

	while (cur != NULL) {
		//print to the output file, in order of Email,Name,Each lab duration,Attendance (%)
		fprintf(fp, "%s,", cur->email);
		fprintf(fp, "%s,", cur->name);

		for (labIndex=0; labIndex<9; labIndex++) {
			fprintf(fp,"%d,",cur->durations[labIndex]);
			if (cur->durations[labIndex] >= 45) {
				validLabs = validLabs + 1;
			}
		}
		percentLabs = (float) validLabs / 9.0;
		fprintf(fp, "%.2f", percentLabs);
		fprintf(fp, "\n");
		validLabs = 0;
		cur = cur->next;
	}
}
