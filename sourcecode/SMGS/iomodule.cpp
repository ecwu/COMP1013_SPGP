#include "relay.h"

int loadStudentList(struct stu *studentList, int *stuNumber) {
	FILE *namep;
	char studentNameBuffer[11], firstLineBuffer[256];

	namep = fopen("students.txt", "r");
	if (namep == NULL) {
		puts("Fatal Error: Unable to load students list.");
		exit(0);
		return -1;
	}

	fscanf(namep, "%[^\n]\n", firstLineBuffer);

	while ((fscanf(namep, "%[^]0123456789]%d\n", studentNameBuffer, &studentList[*stuNumber].studentID)) != EOF) {
		int endPosition = strlen(studentNameBuffer) - 1;

		while (studentNameBuffer[endPosition] == ' ') {
			studentNameBuffer[endPosition] = '\0';
			endPosition--;
		}
		strcpy(studentList[*stuNumber].name, studentNameBuffer);
		(*stuNumber)++;
	}

	fclose(namep);

	return 0;
}

int loadStudentMarks(struct stuNMarks *studentMarks, struct stu *studentList, int* assignmentStatus, int stuNumber) {
	FILE *markp;
	char studentNameBuffer[11], firstLineBuffer[256];
	int index = 0, i = 0;

	markp = fopen("marks.txt", "r");
	if (markp == NULL) {
		loadStudentMarksInit(studentMarks, studentList, stuNumber);
		return 0;
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

void loadStudentMarksInit(struct stuNMarks *studentMarks, struct stu *studentList, int stuNumber) {
	for (int i = 0; i < stuNumber; i++) {
		strcpy(studentMarks[i].name, studentList[i].name);
		studentMarks[i].studentID = studentList[i].studentID;
		studentMarks[i].assignment1 = 0.0;
		studentMarks[i].assignment2 = 0.0;
		studentMarks[i].assignment3 = 0.0;
		studentMarks[i].assignment4 = 0.0;
		studentMarks[i].assignment5 = 0.0;
	}
}