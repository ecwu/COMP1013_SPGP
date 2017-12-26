#include "relay.h"


int main() {
	char version[] = "1.0.0"; // version number
	printf("Welcome to Grade Management System %s\n", version);

	while (1) { // Output start menu
		listFunction();
	}

	return 0;
}

void listFunction() {
	int select;

	do {
		printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|    Welcome to Use Grade Management System     |\n");
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
		scanf("%d", &select); // Read user's input

		switch (select) {
		case 1:
			grade(); // Call the garde function
			break;
		case 2:
			inquiry(); // Call the inquiry function
			break;
		case 3:
			sort(); // Call the sort function
			break;
		case 4:
			puts("Quitting the system...");
			exit(0); // Terminate the program
			break;
		default: printf("%d is an invalid Input: Number should between 1 -- 4!\n", select);
		}

	} while (1);
}
