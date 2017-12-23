#include "relay.h"

int gradeFunction() {
	struct stu studentList[20];
	struct stuNMarks studentMarks[20];
	int assignmentStatus[5] = { 0,0,0,0,0 };
	int stuNumber = 0, i = 0;
	int assignmentNO = 0, questionNO = 0;

	loadStudentList(studentList, &stuNumber);

	loadStudentMarks(studentMarks, studentList, &assignmentStatus[0], stuNumber);

	if (indexReader(&assignmentNO, &questionNO, &assignmentStatus[0]) == -1) {
		return 0;
	}
	grading(studentMarks, assignmentNO, questionNO, stuNumber);

	writeStudentMarks(studentMarks, stuNumber, &assignmentStatus[0]);

	return 0;
}

int indexReader(int *assignmentNO, int *questionNO, int* assignmentStatus) {
	int assignment = 0, overwrite = 0, question = 1;
	printf("Which Assignment You Want to Grade\n(Enter a number from 1 -- 5):");
	scanf("%d", &assignment);
	while (!(assignment >= 1 && assignment <= 5)) {
		puts("Error: The data you entered is invalid, Please enter a Number from 1 -- 5:");
		scanf("%d", &assignment);
	}
	if (assignmentStatus[assignment - 1] == 1) {
		printf("You've graded Assignment %d before, do you want to overwrite the data?\n", assignment);
		puts("1 - Overwrite the existing data\n0 - Abort the operation");
		scanf("%d", &overwrite);
		if (overwrite == 0) {
			return -1;
		}
		else if (overwrite == 1) {
			*assignmentNO = assignment;
		}
		*assignmentNO = assignment;
	}
	*assignmentNO = assignment;
	assignmentStatus[assignment - 1] = 1;
	printf("You'are grading Assignment %d, How many question in this assignment?\n(Enter a Number from 1 -- 10):", assignment);
	scanf("%d", &question);
	while (!(question >= 1 && question <= 10)) {
		puts("Error: The data you entered is invalid, Please enter a Number from 1 -- 10:");
		scanf("%d", &question);
	}
	*questionNO = question;
	return 0;
}

int grading(struct stuNMarks *studentMarks, int assignmentNO, int questionNO, int stuNumber) {
	char letterGrade;
	float marksum = 0;
	for (int i = 0; i < stuNumber; i++) {
		printf("Now grade for student: %s\n", studentMarks[i].name);
		for (int j = 0; j < questionNO; j++) {
			printf("\tPlase input the grade for Assignment %d, Question %d(A,B,C,D)\n\t", assignmentNO, j + 1);
			do {
				scanf("%c", &letterGrade);
			} while (!((letterGrade >= 'a' && letterGrade <= 'd') || (letterGrade >= 'A' && letterGrade <= 'D')));
			switch (letterGrade) {
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
			}
		}
		printf("Assignment %d's mark for student: %s is: %.2f\n", assignmentNO, studentMarks[i].name, marksum / questionNO);
		switch (assignmentNO) {
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
		marksum = 0;
	}
	printf("Finished the grading for Assignment %d\n", assignmentNO);
	return 0;
}

int writeStudentMarks(struct stuNMarks *studentMarks, int stuNumber, int* assignmentStatus) {
	FILE *markp;

	markp = fopen("marks.txt", "w");
	if (markp == NULL) {
		puts("Fatal Error: Unable to write student marks list.");
		return -1;
	}

	fprintf(markp, "Name      ID    ");
	for (int i = 0; i < 5; i++) {
		if (assignmentStatus[i] == 1) {
			fprintf(markp, "Assignment%d  ", i + 1);
		}
	}
	fprintf(markp, "\n");

	for (int i = 0; i < stuNumber; i++) {
		fprintf(markp, "%-10s%-6d", studentMarks[i].name, studentMarks[i].studentID);
		if (assignmentStatus[0] == 1) {
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
		fprintf(markp, "\n");
	}

	printf("Output the data successful.\n");
	fclose(markp);
	return 0;
}