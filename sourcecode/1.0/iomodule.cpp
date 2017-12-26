#include "relay.h"

int loadStudentList(struct stu *studentList, int *stuNumber) {
	FILE *namep;
	char studentNameBuffer[11], firstLineBuffer[256]; // student name and scanf Buffer

	namep = fopen("students.txt", "r"); // Open the students.txt file
	if (namep == NULL) {
		puts("Fatal Error: Unable to load students list."); // If unable to open students.txt file, output an error message and terminate the program
		exit(0);
		return -1;
	}

	fscanf(namep, "%[^\n]\n", firstLineBuffer); // Read the first line of the file

	while ((fscanf(namep, "%[^]0123456789]%d\n", studentNameBuffer, &studentList[*stuNumber].studentID)) != EOF) { 
		/*
		Read the entire file and save the corresponding information into the structure studentList
		Read line by line
		%[^]0123456789] will read anything until meet any number and put into studentNameBuffer
		*/
		int endPosition = strlen(studentNameBuffer) - 1;

		while (studentNameBuffer[endPosition] == ' ') { // Trim the extra space
			studentNameBuffer[endPosition] = '\0';
			endPosition--;
		}
		strcpy(studentList[*stuNumber].name, studentNameBuffer); // Write the student's name to structure
		(*stuNumber)++;
	}

	fclose(namep);

	return 0;
}

int loadStudentMarks(struct stuNMarks *studentMarks, struct stu *studentList, int* assignmentStatus, int stuNumber) {
	FILE *markp;
	char studentNameBuffer[11], firstLineBuffer[256]; // student name and scanf Buffer
	int index = 0, i = 0;

	markp = fopen("marks.txt", "r"); // Open the marks.txt file (if exist)
	if (markp == NULL) { // If the file not exist (never graded before)
		loadStudentMarksInit(studentMarks, studentList, stuNumber); // init the studentMarks structure
		return 0;
	}

	fscanf(markp, "%[^\n]\n", firstLineBuffer); // Read the first line of the file

	while (firstLineBuffer[i] != '\0') { // Check which Assignment(s) is/are graded
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
		if (assignmentStatus[0] == 1) { // Read Assignment if it exist
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
		index++; // index increase (ready to read next student)
	}

	fclose(markp); // close the marks file
	return 0;

}

void loadStudentMarksInit(struct stuNMarks *studentMarks, struct stu *studentList, int stuNumber) {
	for (int i = 0; i < stuNumber; i++) { // copy the student's name and ID from studentList structure
		strcpy(studentMarks[i].name, studentList[i].name);
		studentMarks[i].studentID = studentList[i].studentID;
		studentMarks[i].assignment1 = 0.0; // init all the assignment marks to zero
		studentMarks[i].assignment2 = 0.0;
		studentMarks[i].assignment3 = 0.0;
		studentMarks[i].assignment4 = 0.0;
		studentMarks[i].assignment5 = 0.0;
	}
}