#pragma once
struct stu {
	char name[11];
	int studentID;
};

struct stuNMarks {
	char name[11];
	int studentID;
	float assignment1;
	float assignment2;
	float assignment3;
	float assignment4;
	float assignment5;
};

struct stuNSum {
	char name[11];
	int studentID;
	float sum;
};

struct marksNPointer {
	char name[11];
	int studentID;
	float sum;
	struct marksNPointer *nextNode;
};

int gradeFunction();
int loadStudentList(struct stu *studentList, int *stuNumber);
int loadStudentMarks(struct stuNMarks *studentMarks, struct stu *studentList, int* assignmentStatus, int stuNumber);
void loadStudentMarksInit(struct stuNMarks *studentMarks, struct stu *studentList, int stuNumber);
int indexReader(int *assignmentNO, int *questionNO, int* assignmentStatus);
int grading(struct stuNMarks *studentMarks, int assignmentNO, int questionNO, int stuNumber);
int writeStudentMarks(struct stuNMarks *studentMarks, int stuNumber, int* assignmentStatus);
int inquiry();
int loadStudentMarksforInquiry(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber);
int inquiryByIndex(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber);
int inquiryByStudentId(struct stuNMarks *studentMarks, int* assignmentStatus, int stuNumber);
void subListFunction();
int sort();
int bubbleSort(struct stuNMarks *studentMarks, int stuNumber);
int marksToSum(struct stuNMarks *studentMarks, struct stuNSum *studentSum, int stuNumber);
int writeStudentSum(struct stuNSum *studentSum, int stuNumber);
int loadSortedList(int stuNumber);
int outputLinkedList(struct marksNPointer *current);