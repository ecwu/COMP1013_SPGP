#include "relay.h"

int sort() {
	struct stu studentList[20];
	struct stuNMarks studentMarks[20];
	struct stuNSum studentSum[20];
	int assignmentStatus[5] = { 0,0,0,0,0 };
	int stuNumber = 0;
	
	loadStudentList(studentList, &stuNumber);
	if (loadStudentMarksforInquiry(studentMarks, &assignmentStatus[0], stuNumber) == -1) {
		return -1;
	}

	bubbleSort(studentMarks, stuNumber);
	marksToSum(studentMarks, studentSum, stuNumber);
	writeStudentSum(studentSum, stuNumber);

	loadSortedList(stuNumber);
	printf("\n");

	return 0;
}

int bubbleSort(struct stuNMarks *studentMarks, int stuNumber) {
	char studentNameTemp[11];
	int studentIDTemp = 0;
	float studentMarksSumi = 0.0, studentMarksSumj = 0.0;
	float studentAssignment1 = 0.0, studentAssignment2 = 0.0, studentAssignment3 = 0.0, studentAssignment4 = 0.0, studentAssignment5 = 0.0;

	for (int i = 0; i < stuNumber; i++) {
		studentMarksSumi = studentMarks[i].assignment1 + studentMarks[i].assignment2 + studentMarks[i].assignment3 + studentMarks[i].assignment4 + studentMarks[i].assignment5;
		for (int j = i; j < stuNumber; j++) {
			studentMarksSumj = studentMarks[j].assignment1 + studentMarks[j].assignment2 + studentMarks[j].assignment3 + studentMarks[j].assignment4 + studentMarks[j].assignment5;
			if (studentMarksSumi < studentMarksSumj) {
				strcpy(studentNameTemp, studentMarks[j].name);
				studentIDTemp = studentMarks[j].studentID;
				studentAssignment1 = studentMarks[j].assignment1;
				studentAssignment2 = studentMarks[j].assignment2;
				studentAssignment3 = studentMarks[j].assignment3;
				studentAssignment4 = studentMarks[j].assignment4;
				studentAssignment5 = studentMarks[j].assignment5;
				strcpy(studentMarks[j].name, studentMarks[i].name);
				studentMarks[j].studentID = studentMarks[i].studentID;
				studentMarks[j].assignment1 = studentMarks[i].assignment1;
				studentMarks[j].assignment2 = studentMarks[i].assignment2;
				studentMarks[j].assignment3 = studentMarks[i].assignment3;
				studentMarks[j].assignment4 = studentMarks[i].assignment4;
				studentMarks[j].assignment5 = studentMarks[i].assignment5;
				strcpy(studentMarks[i].name, studentNameTemp);
				studentMarks[i].studentID = studentIDTemp;
				studentMarks[i].assignment1 = studentAssignment1;
				studentMarks[i].assignment2 = studentAssignment2;
				studentMarks[i].assignment3 = studentAssignment3;
				studentMarks[i].assignment4 = studentAssignment4;
				studentMarks[i].assignment5 = studentAssignment5;
			}
		}
	}

	return 0;
}

int marksToSum(struct stuNMarks *studentMarks, struct stuNSum *studentSum, int stuNumber) {
	for (int i = 0; i < stuNumber; i++) {
		strcpy(studentSum[i].name, studentMarks[i].name);
		studentSum[i].studentID = studentMarks[i].studentID;
		studentSum[i].sum = studentMarks[i].assignment1 + studentMarks[i].assignment2 + studentMarks[i].assignment3 + studentMarks[i].assignment4 + studentMarks[i].assignment5;
	}
	return 0;
}

int writeStudentSum(struct stuNSum *studentSum, int stuNumber) {
	FILE *sortedp;

	sortedp = fopen("sorted.txt", "w");
	if (sortedp == NULL) {
		puts("Fatal Error: Unable to write student total marks list.");
		return -1;
	}

	fprintf(sortedp, "Name      ID    Total  \n");

	for (int i = 0; i < stuNumber; i++) {
		fprintf(sortedp, "%-10s%-6d%-7.2f\n", studentSum[i].name, studentSum[i].studentID, studentSum[i].sum);
	}

	printf("Output the data successful.\n");
	fclose(sortedp);
	return 0;
}

int loadSortedList(int stuNumber) {
	FILE *sortedp;
	struct marksNPointer *pnode1, *pnode2, *head;
	char studentNameBuffer[11], uselessBuffer[256];
	int studentIDBuffer = 0, index = 0;
	float studentTotalBuffer = 0.0;

	sortedp = fopen("sorted.txt", "r");
	if (sortedp == NULL) {
		puts("Fatal Error: Unable to load sorted marks list.");
		exit(0);
	}
	fscanf(sortedp, "%[^\n]\n", uselessBuffer);
	while ((fscanf(sortedp, "%[^]0123456789]%d%f\n", studentNameBuffer, &studentIDBuffer, &studentTotalBuffer)) != EOF) {
		int endPosition = strlen(studentNameBuffer) - 1;
		while (studentNameBuffer[endPosition] == ' ') {
			studentNameBuffer[endPosition] = '\0';
			endPosition--;
		}
		if (index == 0){
			pnode1 = (struct marksNPointer *)malloc(sizeof(struct marksNPointer));
			strcpy(pnode1->name, studentNameBuffer);
			pnode1->studentID = studentIDBuffer;
			pnode1->sum = studentTotalBuffer;
			head = pnode1;
		}
		else {
			pnode2 = (struct marksNPointer *)malloc(sizeof(struct marksNPointer));
			strcpy(pnode2->name, studentNameBuffer);
			pnode2->studentID = studentIDBuffer;
			pnode2->sum = studentTotalBuffer;
			pnode1->nextNode = pnode2;
			pnode1 = pnode2;
		}
		index++;
	}
	pnode2->nextNode = NULL;
	fclose(sortedp);
	puts("Name      ID    Total        ");
	outputLinkedList(head);
	pnode1 = head;
	while (pnode1->nextNode != NULL) {
		head = head->nextNode;
		free(pnode1);
		pnode1 = head;
	}
	free(pnode1);
	return 0;
}

int outputLinkedList(struct marksNPointer *current) {
	if (current->nextNode == NULL) {
		printf("%-10s%-6d%-13.2f\n", current->name, current->studentID, current->sum);
		return 0;
	}
	printf("%-10s%-6d%-13.2f\n", current->name, current->studentID, current->sum);
	return outputLinkedList(current->nextNode);
}