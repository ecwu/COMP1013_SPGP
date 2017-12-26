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
	char studentNameTemp[11]; // name buffer for swap
	int studentIDTemp = 0; // id buffer for swap
	float studentMarksSumi = 0.0, studentMarksSumj = 0.0; // Marks sum for compare
	float studentAssignment1 = 0.0, studentAssignment2 = 0.0, studentAssignment3 = 0.0, studentAssignment4 = 0.0, studentAssignment5 = 0.0;
	/*Assignments buffers for swap*/

	for (int i = 0; i < stuNumber; i++) { // bubble sort
		studentMarksSumi = studentMarks[i].assignment1 + studentMarks[i].assignment2 + studentMarks[i].assignment3 + studentMarks[i].assignment4 + studentMarks[i].assignment5;
		for (int j = i; j < stuNumber; j++) {
			studentMarksSumj = studentMarks[j].assignment1 + studentMarks[j].assignment2 + studentMarks[j].assignment3 + studentMarks[j].assignment4 + studentMarks[j].assignment5;
			if (studentMarksSumi < studentMarksSumj) { // If the previous one is smaller than the last one

				strcpy(studentNameTemp, studentMarks[j].name);
				studentIDTemp = studentMarks[j].studentID;
				studentAssignment1 = studentMarks[j].assignment1;
				studentAssignment2 = studentMarks[j].assignment2;
				studentAssignment3 = studentMarks[j].assignment3;
				studentAssignment4 = studentMarks[j].assignment4;
				studentAssignment5 = studentMarks[j].assignment5;
				// the last one to buffers

				strcpy(studentMarks[j].name, studentMarks[i].name);
				studentMarks[j].studentID = studentMarks[i].studentID;
				studentMarks[j].assignment1 = studentMarks[i].assignment1;
				studentMarks[j].assignment2 = studentMarks[i].assignment2;
				studentMarks[j].assignment3 = studentMarks[i].assignment3;
				studentMarks[j].assignment4 = studentMarks[i].assignment4;
				studentMarks[j].assignment5 = studentMarks[i].assignment5;
				// the previous one to the last one

				strcpy(studentMarks[i].name, studentNameTemp);
				studentMarks[i].studentID = studentIDTemp;
				studentMarks[i].assignment1 = studentAssignment1;
				studentMarks[i].assignment2 = studentAssignment2;
				studentMarks[i].assignment3 = studentAssignment3;
				studentMarks[i].assignment4 = studentAssignment4;
				studentMarks[i].assignment5 = studentAssignment5;
				//buffer to the the previous
			}
		}
	}

	return 0;
}

int marksToSum(struct stuNMarks *studentMarks, struct stuNSum *studentSum, int stuNumber) {
	// Copy student's Name, ID and add up score to studentSum structure
	for (int i = 0; i < stuNumber; i++) {
		strcpy(studentSum[i].name, studentMarks[i].name);
		studentSum[i].studentID = studentMarks[i].studentID;
		studentSum[i].sum = studentMarks[i].assignment1 + studentMarks[i].assignment2 + studentMarks[i].assignment3 + studentMarks[i].assignment4 + studentMarks[i].assignment5;
	}
	return 0;
}

int writeStudentSum(struct stuNSum *studentSum, int stuNumber) {
	FILE *sortedp;

	sortedp = fopen("sorted.txt", "w"); // Open/New the sorted.txt file
	if (sortedp == NULL) {
		puts("Fatal Error: Unable to write sorted file."); // If unable to open / new sorted.txt file, output an error message and exit sorted function
		return -1;
	}

	fprintf(sortedp, "Name      ID    Total  \n"); // Write the table head to the file

	for (int i = 0; i < stuNumber; i++) {
		fprintf(sortedp, "%-10s%-6d%-7.2f\n", studentSum[i].name, studentSum[i].studentID, studentSum[i].sum); 
		// Write the student's name, id, total score one by one
	}

	printf("Output the sorted data successful.\n"); // Display a success message after finish output process
	fclose(sortedp); // close the sorted.txt file
	return 0;
}

int loadSortedList(int stuNumber) {
	FILE *sortedp;
	struct marksNPointer *pnode1, *pnode2, *head; // struct variable for linked list
	char studentNameBuffer[11], uselessBuffer[256]; // student name and scanf Buffer
	int studentIDBuffer = 0, index = 0; // student id Buffer
	float studentTotalBuffer = 0.0; // student total marks buffer

	sortedp = fopen("sorted.txt", "r"); // Open the file
	if (sortedp == NULL) {
		puts("Fatal Error: Unable to load sorted file."); // If unable to open students.txt file, output an error message and terminate the program
		exit(0);
	}
	fscanf(sortedp, "%[^\n]\n", uselessBuffer); // Pass the first line of the file
	while ((fscanf(sortedp, "%[^]0123456789]%d%f\n", studentNameBuffer, &studentIDBuffer, &studentTotalBuffer)) != EOF) {
		int endPosition = strlen(studentNameBuffer) - 1;
		while (studentNameBuffer[endPosition] == ' ') { // Trim the extra space
			studentNameBuffer[endPosition] = '\0';
			endPosition--;
		}
		if (index == 0){ // if this is the first node (head)
			pnode1 = (struct marksNPointer *)malloc(sizeof(struct marksNPointer)); // allocate the memory spaces
			strcpy(pnode1->name, studentNameBuffer); // copy student's name to node
			pnode1->studentID = studentIDBuffer; // copy student's id to node
			pnode1->sum = studentTotalBuffer; // copy student's total score to node
			head = pnode1; // head point to pnode1
		}
		else { // if this is the node follow the head
			pnode2 = (struct marksNPointer *)malloc(sizeof(struct marksNPointer)); // allocate the memory spaces
			strcpy(pnode2->name, studentNameBuffer); // copy student's name to node
			pnode2->studentID = studentIDBuffer; // copy student's id to node
			pnode2->sum = studentTotalBuffer; // copy student's total score to node
			pnode1->nextNode = pnode2; // pnode1's nextNode point to pnode2 (two nodes linked)
			pnode1 = pnode2; // pnode1 pointed to pnode2
		}
		index++; // started next student
	}
	pnode2->nextNode = NULL; // nextNode of the last node set to NULL (the end of the link list)
	fclose(sortedp); // close the file
	puts("Name      ID    Total        "); // Output the table head
	outputLinkedList(head); // call function to output the table
	
	// Start free linked list process
	pnode1 = head;
	while (pnode1->nextNode != NULL) {
		head = head->nextNode;
		free(pnode1);
		pnode1 = head;
	}
	free(pnode1);
	return 0;
}

int outputLinkedList(struct marksNPointer *current) { // Print out using recursion
	if (current->nextNode == NULL) { // print the information until meet the tail of the linked list & base case
		printf("%-10s%-6d%-13.2f\n", current->name, current->studentID, current->sum);
		return 0;
	}
	printf("%-10s%-6d%-13.2f\n", current->name, current->studentID, current->sum); // print out the last node
	return outputLinkedList(current->nextNode); // recursion
}