/*
Structure Programming Group Project
Group Menber: Jack Wu, Irving Sau, Otto Zhang, Cheryl Shen.
Create Time: 2017-12-13
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relay.h"

void listFunction();

int main() {
	char version[] = "0.6.0";
	printf("Welcome to Score Management System %s\n\n\n", version);

	while (1) {
		listFunction();
	}

	return 0;
}

void listFunction() {
	int select;

	do {
		printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|       Welcome to Use Grade System         	|\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|    Please Select The Following Functions:     |\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|   $$-Grade-			-- Press 1	|\n");
		printf("\t\t|   $$-Inquiry-			-- Press 2	|\n");
		printf("\t\t|   $$-Sort-			-- Press 3	|\n");
		printf("\t\t|   $$-Quit-			-- Press 4	|\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");
		printf("Please Input Number:");
		scanf("%d", &select);

		switch (select) {
		case 1:
			gradeFunction();
			break;
		case 2:
			inquiry();
			break;
		case 3:
			sort();
			break;
		case 4:
			puts("Quitting the system...");
			exit(0);
			break;
		default: printf("%d is an invalid Input: Number should between 1 -- 4!\n", select);
		}

	} while (1);
}
