#include "relay.h"

int inquiry() {
	subListFunction(); // Output sub menu
	return 0;
}

void subListFunction() {
	int select; // store which function the user select
	struct stu studentList[20]; // Store the student's basic info
	struct stuNMarks studentMarks[20]; // Store the student's mark
	int assignmentStatus[5] = { 0,0,0,0,0 }; // Indicates Assignment status
	int stuNumber = 0; // Number of students

	loadStudentList(studentList, &stuNumber); // Load the student info and number of students from students.txt
	if (loadStudentMarksforInquiry(studentMarks, &assignmentStatus[0], stuNumber) == -1) { // Load student's marks from marks.txt
		return; // Terminate if the program can't find the marks.txt file
	}

	do {
		puts("1. By index");
		puts("2. By student id");
		puts("3. Quit");
		printf("Please Select the function you want:");
		scanf("%d", &select);

		switch (select) {
		case 1:inquiryByIndex(studentMarks, &assignmentStatus[0], stuNumber); // Call Inquiry By Index function
			break;
		case 2:
			inquiryByStudentId(studentMarks, &assignmentStatus[0], stuNumber); // Call Inquiry By Student ID function
			break;
		case 3:
			return; // Back to main menu
			break;
		default: printf("%d is an invalid Input: Number should between 1 -- 3!\n", select); // Output a Error message if the Input is Invalid
		}

	} while (1);
}

int loadStudentMarksforInquiry(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber) {
	FILE *markp;
	char studentNameBuffer[11], firstLineBuffer[256]; // student name and scanf Buffer
	int index = 0, i = 0; // Student's Index variable

	markp = fopen("marks.txt", "r"); // Open the marks.txt file
	if (markp == NULL) {
		puts("Fatal Error: Unable to load students marks file."); // If unable to open the file, output an error message and terminate the program
		return -1;
	}

	fscanf(markp, "%[^\n]\n", firstLineBuffer); // Read the first line of the file

	while (firstLineBuffer[i] != '\0') { // Check what Assignment is graded
		switch (firstLineBuffer[i]) {
		case '1':
			assignmentStatus[0] = 1;
			break;
		case '2':
			assignmentStatus[1] = 1;
			break;
		case '3':
			assignmentStatus[2] = 1;
			break;
		case '4':
			assignmentStatus[3] = 1;
			break;
		case '5':
			assignmentStatus[4] = 1;
			break;
		}
		i++;
	} 

	while ((fscanf(markp, "%[^]0123456789]%d", studentNameBuffer, &studentMarks[index].studentID)) != EOF || index < stuNumber) {
		/*
		Read the entire file and save the corresponding information into the structure studentMarks
		Read line by line
		%[^]0123456789] will read anything until meet any number and put into studentNameBuffer
		*/
		int endPosition = strlen(studentNameBuffer) - 1;
		while (studentNameBuffer[endPosition] == ' ') { // Trim the extra space
			studentNameBuffer[endPosition] = '\0';
			endPosition--;
		}
		strcpy(studentMarks[index].name, studentNameBuffer); // Write the student's name to structure
		if (assignmentStatus[0] == 1) {// Read Assignment if it exist
			fscanf(markp, "%f", &studentMarks[index].assignment1);
		}
		else {
			studentMarks[index].assignment1 = 0.0; // If the assignment not exist init it to 0
		}
		if (assignmentStatus[1] == 1) {
			fscanf(markp, "%f", &studentMarks[index].assignment2);
		}
		else {
			studentMarks[index].assignment2 = 0.0;
		}
		if (assignmentStatus[2] == 1) {
			fscanf(markp, "%f", &studentMarks[index].assignment3);
		}
		else {
			studentMarks[index].assignment3 = 0.0;
		}
		if (assignmentStatus[3] == 1) {
			fscanf(markp, "%f", &studentMarks[index].assignment4);
		}
		else {
			studentMarks[index].assignment4 = 0.0;
		}
		if (assignmentStatus[4] == 1) {
			fscanf(markp, "%f", &studentMarks[index].assignment5);
		}
		else {
			studentMarks[index].assignment5 = 0.0;
		}
		fscanf(markp, "\n");
		index++; // index increase (ready to read next student)
	}

	fclose(markp); // close the marks file
	return 0;

}

int inquiryByIndex(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber) {
	int inputIndex = 0; // Variable for user's input
	puts("Index   Name      ID    "); // Output the index table head
	for (int i = 0; i <stuNumber; i++) {
		printf("%-8d%-10s%-6d\n", i+1, studentMarks[i].name, studentMarks[i].studentID); // Output student's info with Index
	}
	printf("Please input the student's index you want to inquire:");
	scanf("%d", &inputIndex); // read user's input
	while (!(inputIndex > 0 && inputIndex <= stuNumber)) {
		printf("%d is an invalid index, please enter another one:", inputIndex); // If Index does not exist, an error message is output
		scanf("%d", &inputIndex);
	}

	printf("Name      ID    "); // Output the score table head
	for (int i = 0; i < 5; i++) {
		if (assignmentStatus[i] == 1) {
			printf("Assignment%d  ", i + 1);
		}
	}
	printf("\n");

	printf("%-10s%-6d", studentMarks[inputIndex - 1].name, studentMarks[inputIndex - 1].studentID); // Output the Marks according to the index that user entered
	if (assignmentStatus[0] == 1) {
		printf("%-13.2f", studentMarks[inputIndex - 1].assignment1);
	}
	if (assignmentStatus[1] == 1) {
		printf("%-13.2f", studentMarks[inputIndex - 1].assignment2);
	}
	if (assignmentStatus[2] == 1) {
		printf("%-13.2f", studentMarks[inputIndex - 1].assignment3);
	}
	if (assignmentStatus[3] == 1) {
		printf("%-13.2f", studentMarks[inputIndex - 1].assignment4);
	}
	if (assignmentStatus[4] == 1) {
		printf("%-13.2f", studentMarks[inputIndex - 1].assignment5);
	}

	printf("\n");
	printf("\n");

	return 0;
}

int inquiryByStudentId(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber) {
	int inputID = 0; // Variable for user's input
	puts("Please input the student's id you want to inquire:");
	scanf("%d", &inputID); // read user's input
	for (int i = 0; i < stuNumber; i++) {
		if (studentMarks[i].studentID == inputID) {// Output the Marks according to the student id that user entered
			printf("Name      ID    ");
			for (int i = 0; i < 5; i++) {
				if (assignmentStatus[i] == 1) {
					printf("Assignment%d  ", i + 1);
				}
			}
			printf("\n");

			printf("%-10s%-6d", studentMarks[i].name, studentMarks[i].studentID);
			if (assignmentStatus[0] == 1) {
				printf("%-13.2f", studentMarks[i].assignment1);
			}
			if (assignmentStatus[1] == 1) {
				printf("%-13.2f", studentMarks[i].assignment2);
			}
			if (assignmentStatus[2] == 1) {
				printf("%-13.2f", studentMarks[i].assignment3);
			}
			if (assignmentStatus[3] == 1) {
				printf("%-13.2f", studentMarks[i].assignment4);
			}
			if (assignmentStatus[4] == 1) {
				printf("%-13.2f", studentMarks[i].assignment5);
			}
			printf("\n");
			printf("\n");
			return 0;
		}
	}
	puts("The student does not exist."); // If student number does not exist, an error message is output
	printf("\n");
	return -1;
}
