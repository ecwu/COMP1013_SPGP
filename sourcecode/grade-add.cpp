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
int loadStudentMarks(struct stuNMarks *studentMarks, struct stu *studentList, int* assignmentStatus, int stuNumber);
void loadStudentMarksInit(struct stuNMarks *studentMarks, struct stu *studentList, int stuNumber);
int indexReader(int *assignmentNO, int *questionNO, int* assignmentStatus);
int grading(struct stuNMarks *studentMarks, int assignmentNO, int questionNO, int stuNumber);

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
    int stuNumber = 0, i = 0;
    int assignmentNO = 0, questionNO = 0;

    loadStudentList(studentList, &stuNumber);

    loadStudentMarks(studentMarks, studentList, &assignmentStatus[0], stuNumber);
    puts("Name      ID    Assignmnet1  Assignment2  Assignment3  Assignment4  Assignment5  ");
    for(int i = 0; i < stuNumber; i++){
        printf("%-10s%-6d%-13.2f%-13.2f%-13.2f%-13.2f%-13.2f\n", studentMarks[i].name, studentMarks[i].studentID, studentMarks[i].assignment1, studentMarks[i].assignment2, studentMarks[i].assignment3, studentMarks[i].assignment4,studentMarks[i].assignment5);
    }

    indexReader(&assignmentNO, &questionNO, &assignmentStatus[0]);
    grading(studentMarks, assignmentNO, questionNO, stuNumber);
    puts("Name      ID    Assignmnet1  Assignment2  Assignment3  Assignment4  Assignment5  ");
    for(int i = 0; i < stuNumber; i++){
        printf("%-10s%-6d%-13.2f%-13.2f%-13.2f%-13.2f%-13.2f\n", studentMarks[i].name, studentMarks[i].studentID, studentMarks[i].assignment1, studentMarks[i].assignment2, studentMarks[i].assignment3, studentMarks[i].assignment4,studentMarks[i].assignment5);
    }
    

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
        (*stuNumber)++;
	}

    fclose(namep);

    return 0;
}

int loadStudentMarks(struct stuNMarks *studentMarks, struct stu *studentList, int* assignmentStatus, int stuNumber){
    FILE *markp;
    char studentNameBuffer[10], firstLineBuffer[256];
    int index = 0, i = 0;

    markp = fopen("marks.txt", "r");
    if(markp == NULL){
        loadStudentMarksInit(studentMarks, studentList, stuNumber);
        return 0;
    }

    fscanf(markp, "%[^\n]\n", firstLineBuffer);

    while(firstLineBuffer[i] != '\0'){
        switch(firstLineBuffer[i]){
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

    while((fscanf(markp, "%[^ ]%d", studentNameBuffer, &studentMarks[index].studentID)) != EOF || index < stuNumber){
		strcpy(studentMarks[index].name, studentNameBuffer);
        if(assignmentStatus[0] == 1){
            fscanf(markp, "%f", &studentMarks[index].assignment1);
        }else{
			studentMarks[index].assignment1 = 0.0;
		}
        if(assignmentStatus[1] == 1){
            fscanf(markp, "%f", &studentMarks[index].assignment2);
        }else{
			studentMarks[index].assignment2 = 0.0;
		}
        if(assignmentStatus[2] == 1){
            fscanf(markp, "%f", &studentMarks[index].assignment3);
        }else{
			studentMarks[index].assignment3 = 0.0;
		}
        if(assignmentStatus[3] == 1){
            fscanf(markp, "%f", &studentMarks[index].assignment4);
        }else{
			studentMarks[index].assignment4 = 0.0;
		}
        if(assignmentStatus[4] == 1){
            fscanf(markp, "%f", &studentMarks[index].assignment5);
        }else{
			studentMarks[index].assignment5 = 0.0;
		}
            fscanf(markp, "\n");
        index++;
    }

    fclose(markp);
    return 0;

}

void loadStudentMarksInit(struct stuNMarks *studentMarks, struct stu *studentList, int stuNumber){
    for (int i = 0; i < stuNumber; i++){
        strcpy(studentMarks[i].name, studentList[i].name);
        studentMarks[i].studentID = studentList[i].studentID;
        studentMarks[i].assignment1 = 0.0;
        studentMarks[i].assignment2 = 0.0;
        studentMarks[i].assignment3 = 0.0;
        studentMarks[i].assignment4 = 0.0;
        studentMarks[i].assignment5 = 0.0;
    }
}

int indexReader(int *assignmentNO, int *questionNO, int* assignmentStatus){
    int assignment = 0, overwrite = 0, question = 0;
    printf("Which Assignment You Want to Grade(Enter a number from 1 -- 5):");
    scanf("%d", &assignment);
    if(assignmentStatus[assignment-1] == 1){
        printf("You've graded Assignment %d before, do you want to overwrite the data?\n", assignment);
        puts("Enter '1' to overwrite the existing data, Enter '0' to abort the operation.");
        scanf("%d", &overwrite);
        if(overwrite == 0){
            return -1;
        }else if(overwrite == 1){
            *assignmentNO = assignment;
        }
        *assignmentNO = assignment;
    }
    *assignmentNO = assignment;
    printf("You'are grading Assignment %d, How many question in this assignment?(Enter a Number from 1 -- 10):\n", assignment);
    scanf("%d", &question);
    while(!(question >= 1 && question <= 10)){
        puts("Error: The data you entered is invalid, Please enter a Number from 1 -- 10:\n");
        scanf("%d", &question);
    }
    *questionNO = question;
	return 0;
}

int grading(struct stuNMarks *studentMarks, int assignmentNO, int questionNO, int stuNumber){
    char letterGrade;
    float marksum = 0;
    for(int i = 0; i < stuNumber; i++){
        printf("Now grade for student: %s\n", studentMarks[i].name);
        for (int j = 0; j < questionNO; j++){
            printf("\tPlase input the grade for Assignment %d, Question %d(A,B,C,D)\n\t", assignmentNO, j + 1);
            do{
                scanf("%c", &letterGrade);
            }while(!((letterGrade >= 'a' && letterGrade <= 'd')||(letterGrade >= 'A' && letterGrade <= 'D')));
            switch(letterGrade){
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
        printf("Assignment %d's Mark for student: %s is: %.2f\n", assignmentNO, studentMarks[i].name, marksum/questionNO);
        switch(assignmentNO){
            case 1:
                studentMarks[i].assignment1 = marksum/questionNO;
                break;
            case 2:
                studentMarks[i].assignment2 = marksum/questionNO;
                break;
            case 3:
                studentMarks[i].assignment3 = marksum/questionNO;
                break;
            case 4:
                studentMarks[i].assignment4 = marksum/questionNO;
                break;
            case 5:
                studentMarks[i].assignment5 = marksum/questionNO;
                break;
        }
        marksum = 0;
    }
    printf("Finished the grading for assignment %d", assignmentNO);
    return 0;
}