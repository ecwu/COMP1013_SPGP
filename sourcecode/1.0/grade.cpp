#include "relay.h"

int grade() {
	// Define all the variables that need to be used
	struct stu studentList[20]; // Store the student's basic info
	struct stuNMarks studentMarks[20]; // Store the student's mark
	int assignmentStatus[5] = { 0,0,0,0,0 }; // Indicates Assignment status
	int stuNumber = 0, i = 0; // Number of students
	int assignmentNO = 0, questionNO = 0; // Assignment Index & Question number

	loadStudentList(studentList, &stuNumber); // Load the student info and number of students from students.txt

	loadStudentMarks(studentMarks, studentList, &assignmentStatus[0], stuNumber); // Load or Initialize student's marks from marks.txt

	if (indexReader(&assignmentNO, &questionNO, &assignmentStatus[0]) == -1) { // Ask user to enter the Assignment Index and Number of questions
		return 0;
		// The user chooses not to overwrite the data
	}
	grading(studentMarks, assignmentNO, questionNO, stuNumber); // Start the Grading process

	writeStudentMarks(studentMarks, stuNumber, &assignmentStatus[0]); // Save the new marks data to the marks.txt

	return 0;
}

int indexReader(int *assignmentNO, int *questionNO, int* assignmentStatus) {
	int assignment = 0, overwrite = 0, question = 1;
	printf("Which Assignment You Want to Grade\n(Enter a number from 1 -- 5):");
	scanf("%d", &assignment); // Read user's assignment target index
	while (!(assignment >= 1 && assignment <= 5)) { // Output a error message if the inputed index is invalid (not between 1 - 5) 
		puts("Error: The data you entered is invalid, Please enter a Number from 1 -- 5:"); // ask user to re-enter
		scanf("%d", &assignment);
	}
	if (assignmentStatus[assignment - 1] == 1) { // Check if the target index is already graded
		printf("You've graded Assignment %d before, do you want to overwrite the data?\n", assignment);
		puts("1 - Overwrite the existing data\n0 - Abort the operation");
		scanf("%d", &overwrite); // Read whether the user overwrites the data
		if (overwrite == 0) {
			return -1;
		}
	}
	*assignmentNO = assignment; // Save the target index to the variable
	assignmentStatus[assignment - 1] = 1; // change the Assignment's status
	printf("You'are grading Assignment %d, How many question in this assignment?\n(Enter a Number from 1 -- 10):", assignment);
	scanf("%d", &question); // Read how many question(s) in this assignment
	while (!(question >= 1 && question <= 10)) {
		puts("Error: The data you entered is invalid, Please enter a Number from 1 -- 10:"); // Output a error message if the inputed number is invalid (not between 1 - 10) 
		scanf("%d", &question);
	}
	*questionNO = question; // Save the number to the variable
	return 0;
}

int grading(struct stuNMarks *studentMarks, int assignmentNO, int questionNO, int stuNumber) {
	char letterGrade; // Save the input grading letter
	float marksum = 0; // Save the sum of each question mark
	for (int i = 0; i < stuNumber; i++) {
		printf("Now grade for student: %s (%d/%d)\n", studentMarks[i].name, i+1, stuNumber); // Output the student name
		for (int j = 0; j < questionNO; j++) {
			printf("\tPlase input the grade for Assignment %d, Question %d(A,B,C,D,F)\n\t", assignmentNO, j + 1); // Ask user to enter the score for that question
			do {
				scanf("%c", &letterGrade); // Read the grading letter
			} while (!((letterGrade >= 'a' && letterGrade <= 'd') || (letterGrade >= 'A' && letterGrade <= 'D') || (letterGrade == 'F') || (letterGrade == 'f')));
			switch (letterGrade) { // add the corresponding mark to the marksum variable
			case 'a':
			case 'A':
				marksum += 4.0;
				break;
			case 'b':
			case 'B':
				marksum += 3.0;
				break;
			case 'c':
			case 'C':
				marksum += 2.0;
				break;
			case 'd':
			case 'D':
				marksum += 1.0;
				break;
			case 'f':
			case 'F':
				marksum += 0.0;
				break;
			}
		}
		printf("Assignment %d's mark for student: %s is: %.2f\n", assignmentNO, studentMarks[i].name, marksum / questionNO); // Output the student's score
		switch (assignmentNO) { // Write the weighted score into the corresponding structure variable (According to current grading assignment index)
		case 1:
			studentMarks[i].assignment1 = marksum / questionNO;
			break;
		case 2:
			studentMarks[i].assignment2 = marksum / questionNO;
			break;
		case 3:
			studentMarks[i].assignment3 = marksum / questionNO;
			break;
		case 4:
			studentMarks[i].assignment4 = marksum / questionNO;
			break;
		case 5:
			studentMarks[i].assignment5 = marksum / questionNO;
			break;
		}
		marksum = 0; // reset the marksum variable
	}
	printf("Finished the grading for Assignment %d\n", assignmentNO); // Output a success message
	return 0;
}

int writeStudentMarks(struct stuNMarks *studentMarks, int stuNumber, int* assignmentStatus) {
	FILE *markp;

	markp = fopen("marks.txt", "w"); // Open the file that will output the marks
	if (markp == NULL) {
		puts("Fatal Error: Unable to write student marks list."); // Output an error message if it can not be opened
		return -1;
	}

	fprintf(markp, "Name      ID    "); // Write the table header
	for (int i = 0; i < 5; i++) {
		if (assignmentStatus[i] == 1) { // Output the table header according to Assignment Status
			fprintf(markp, "Assignment%d  ", i + 1);
		}
	}
	fprintf(markp, "\n"); // Output a line feed

	for (int i = 0; i < stuNumber; i++) {
		fprintf(markp, "%-10s%-6d", studentMarks[i].name, studentMarks[i].studentID); // Write the student name and ID
		if (assignmentStatus[0] == 1) { // Output the student's score according to Assignment Status
			fprintf(markp, "%-13.2f", studentMarks[i].assignment1);
		}
		if (assignmentStatus[1] == 1) {
			fprintf(markp, "%-13.2f", studentMarks[i].assignment2);
		}
		if (assignmentStatus[2] == 1) {
			fprintf(markp, "%-13.2f", studentMarks[i].assignment3);
		}
		if (assignmentStatus[3] == 1) {
			fprintf(markp, "%-13.2f", studentMarks[i].assignment4);
		}
		if (assignmentStatus[4] == 1) {
			fprintf(markp, "%-13.2f", studentMarks[i].assignment5);
		}
		fprintf(markp, "\n"); // Output a line feed
	}

	printf("Output the marks data successful.\n"); // Output a success message on screen
	fclose(markp); // close the file
	return 0;
}