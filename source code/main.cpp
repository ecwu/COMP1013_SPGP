/*
	Structure Programming Group Project
	Group Menber: Jack Wu, Irving Sau, Otto Zhang, Cheryl Shen.
	Create Time: 2017-12-13
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void function_list();

int main(){
	char version[] = "0.0.1"; 
	printf("Welcome to Score Management System %s\n\n\n", version);

	while (1) {
		function_list();
	}

	return 0;
}

void function_list() {
	int i;

	do {

		printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|       Welcome to Use Grade System         	|\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|    Please Select The Following Functions:     |\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|   -Grade-			-- Press 1	|\n");
		printf("\t\t|   -Inquiry-		-- Press 2	|\n");
		printf("\t\t|   -Sort-			-- Press 3	|\n");
		printf("\t\t|   -Quit-			-- Press 4	|\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");

		printf("\n\n\n\n");

		printf("Please Input Number:");
		scanf("%d", &i);

		switch (i) {

			default: printf("Number should between 1 -- 5!\n");
		}

	} while (1);
}