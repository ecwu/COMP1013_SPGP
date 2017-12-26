/*
	Head file relay.h for Structure Programming Group Project
	Developed by: Group 8
	Group Menber: Jack Wu, Irving Sau, Otto Zhang, Cheryl Shen.
	Create Time: 2017-12-13
*/

/* Head file include */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Structures Define */

struct stu {
	char name[11];
	int studentID;
}; // Store basic student info
struct stuNMarks {
	char name[11];
	int studentID;
	float assignment1;
	float assignment2;
	float assignment3;
	float assignment4;
	float assignment5;
}; // Store student info & score
struct stuNSum {
	char name[11];
	int studentID;
	float sum;
}; // Store student info & total score
struct marksNPointer {
	char name[11];
	int studentID;
	float sum;
	struct marksNPointer *nextNode;
}; // Store info in stuNSum and a struct pointer

/* Function Call */

void listFunction(); // Output the Main Menu

int grade(); // Start the Grade Process
int loadStudentList(struct stu *studentList, int *stuNumber); // Load from students.txt to struct
int loadStudentMarks(struct stuNMarks *studentMarks, struct stu *studentList, int* assignmentStatus, int stuNumber); // Load from marks.txt to struct (init if not exist)
void loadStudentMarksInit(struct stuNMarks *studentMarks, struct stu *studentList, int stuNumber); // Init the score
int indexReader(int *assignmentNO, int *questionNO, int* assignmentStatus); // Read the Assignment Index and Question Number from user
int grading(struct stuNMarks *studentMarks, int assignmentNO, int questionNO, int stuNumber); // Grading Students one by one & save to struct
int writeStudentMarks(struct stuNMarks *studentMarks, int stuNumber, int* assignmentStatus); // Write the struct to marks.txt

int inquiry(); // Start the Inquiry Process
int loadStudentMarksforInquiry(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber); // Load from marks.txt to struct (terminate if not exist)
int inquiryByIndex(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber); // Inquiry student by index
int inquiryByStudentId(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber); // Inquiry student by student id
void subListFunction(); // Output the Sub Menu for inquiry

int sort(); // Start the Sort Process
int bubbleSort(struct stuNMarks *studentMarks, int stuNumber); // Bubble Sort the elements in struct (according to total score)
int marksToSum(struct stuNMarks *studentMarks, struct stuNSum *studentSum, int stuNumber); // rewrite the marks struct to total marks struct
int writeStudentSum(struct stuNSum *studentSum, int stuNumber); // write the struct to sorted.txt
int loadSortedList(int stuNumber); // load the info from sorted.txt to a linked list
int outputLinkedList(struct marksNPointer *current); // Display the info from the linked list