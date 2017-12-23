#include "relay.h"

int inquiry() {
	subListFunction();
	return 0;
}

void subListFunction() {
	int select;
	struct stu studentList[20];
	struct stuNMarks studentMarks[20];
	int assignmentStatus[5] = { 0,0,0,0,0 };
	int stuNumber = 0;

	loadStudentList(studentList, &stuNumber);
	if (loadStudentMarksforInquiry(studentMarks, &assignmentStatus[0], stuNumber) == -1) {
		return;
	}

	do {
		puts("1 - Inquire By Index");
		puts("2 - Inquire By Student ID");
		puts("3 - Return to the previous menu");
		printf("Please Select the function you want:");
		scanf("%d", &select);

		switch (select) {
		case 1:inquiryByIndex(studentMarks, &assignmentStatus[0], stuNumber);
			break;
		case 2:
			inquiryByStudentId(studentMarks, &assignmentStatus[0], stuNumber);
			break;
		case 3:
			return;
			break;
		default: printf("%d is an invalid Input: Number should between 1 -- 3!\n", select);
		}

	} while (1);
}

int loadStudentMarksforInquiry(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber) {
	FILE *markp;
	char studentNameBuffer[11], firstLineBuffer[256];
	int index = 0, i = 0;

	markp = fopen("marks.txt", "r");
	if (markp == NULL) {
		puts("Fatal Error: Unable to load students marks list.");
		return -1;
	}

	fscanf(markp, "%[^\n]\n", firstLineBuffer);

	while (firstLineBuffer[i] != '\0') {
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
		int endPosition = strlen(studentNameBuffer) - 1;
		while (studentNameBuffer[endPosition] == ' ') {
			studentNameBuffer[endPosition] = '\0';
			endPosition--;
		}
		strcpy(studentMarks[index].name, studentNameBuffer);
		if (assignmentStatus[0] == 1) {
			fscanf(markp, "%f", &studentMarks[index].assignment1);
		}
		else {
			studentMarks[index].assignment1 = 0.0;
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
		index++;
	}

	fclose(markp);
	return 0;

}

int inquiryByIndex(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber) {
	int inputIndex = 0;
	puts("Index   Name      ID    ");
	for (int i = 0; i <stuNumber; i++) {
		printf("%-8d%-10s%-6d\n", i+1, studentMarks[i].name, studentMarks[i].studentID);
	}
	printf("Please input the student's index you want to inquire:");
	scanf("%d", &inputIndex);
	while (!(inputIndex > 0 && inputIndex <= stuNumber)) {
		printf("%d is an invalid index, please enter another one:", inputIndex);
		scanf("%d", &inputIndex);
	}

	printf("Name      ID    ");
	for (int i = 0; i < 5; i++) {
		if (assignmentStatus[i] == 1) {
			printf("Assignment%d  ", i + 1);
		}
	}
	printf("\n");

	printf("%-10s%-6d", studentMarks[inputIndex - 1].name, studentMarks[inputIndex - 1].studentID);
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
	int inputID = 0;
	puts("Please input the student's id you want to inquire:");
	scanf("%d", &inputID);
	for (int i = 0; i < stuNumber; i++) {
		if (studentMarks[i].studentID == inputID) {
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
	puts("The student does not exist.");
	printf("\n");
	return -1;
}
