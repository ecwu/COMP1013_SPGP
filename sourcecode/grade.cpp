#include <stdio.h>
#include <string.h>

struct stu{
    char name[10];
    int studentID;
};

struct stuNMarks{
    char name[10];
    int studentID;
    float assignment1;
    float assignment2;
    float assignment3;
    float assignment4;
    float assignment5;
};

int gradeFunction();
int loadStudentList(struct stu *studentList, int *stuNumber);
int loadStudentMarks(struct stuNMarks *studentMarks, int *assignmentStatus);

int main(){
    int input = 0;
    puts("input 1 / 0 to run / terminate");
    scanf("%d", &input);
    switch(input){
        case 1:
            gradeFunction();
            break;
        default:
            return 0;
    }
    return 0;
}
int gradeFunction(){
    struct stu studentList[20];
    struct stuNMarks studentMarks[20];
    int assignmentStatus[5] = {0,0,0,0,0};
    int stuNumber = 0;

    loadStudentList(studentList, &stuNumber);


    return 0;
}

int loadStudentList(struct stu *studentList, int *stuNumber){
    FILE *namep;
    char studentNameBuffer[10], firstLineBuffer[256];

    namep = fopen("students.txt", "r");
    if(namep == NULL){
        puts("Fatal Error: Unable to load students list.");
        return -1;
    }

    fscanf(namep, "%[^\n]\n", firstLineBuffer);

    while((fscanf(namep, "%[^ ]%d\n", studentNameBuffer, &studentList[*stuNumber].studentID)) != EOF){
        strcpy(studentList[*stuNumber].name, studentNameBuffer);
        printf("Name:%s, ID:%d\n", studentList[*stuNumber].name,studentList[*stuNumber].studentID);
        (*stuNumber)++;
	}

    printf("Total Student Number is: %d\n", *stuNumber);

    fclose(namep);

    return 0;
}

int loadStudentMarks(struct stuNMarks *studentMarks, int *assignmentStatus){
    FILE *markp;
    FILE *namep;
    char studentNameBuffer[10], firstLineBuffer[256];

    markp = fopen("marks.txt", "r");
    if(markp == NULL){
        namep = fopen("students.txt", "r");
        if(namep == NULL){
            puts("Fatal Error: Unable to load students list.");
            return -1;
        }
        fclose(namep);
        return 0;
    }



    fclose(markp);
    return 0;

}