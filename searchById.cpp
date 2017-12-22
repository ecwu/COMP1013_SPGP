#include <stdio.h>
#include <string.h>

void searchById();
int loadStudentMarks(struct stuNMarks *studentMarks, int* assignmentStatus);

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

int Inquiry()
{
		int modeSelect;
	
		printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|       Welcome to Use Inquiry System         	|\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|      Please Select The mode of inquiry:       |\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|   $$-By Index      -- Press 1	                |\n");
		printf("\t\t|   $$-By ID         -- Press 2                 |\n");
		printf("\t\t|                                               |\n");
		printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");

		printf("\n\n\n\n");

		printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");
		printf("\t\t|                                                                                                            |\n");
		printf("\t\t|Early Access Program                                                                                        |\n");
		printf("\t\t|Get instant access and start using; get involved with this program as it develops.                          |\n");
		printf("\t\t|Note: This Early Access Program is not complete and may or may not change further. If you are notexcited to |\n");
		printf("\t\t|use this program in its current state, then you should wait to see if the program progresses further in     |\n");
		printf("\t\t|development.                                                                                                |\n");
		printf("\t\t|                                                                                                            |\n");
		printf("\t\t|$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$|\n");

		printf("\n\n\n\n");

		printf("Please Input Number:");
		scanf("%d", &modeSelect);

		switch (modeSelect) {

			//case 1: Index(); break;
			case 2: searchById(); break;
	
			default: printf("Number should between 1 -- 2!\n");
		}
		return 0;
}

void searchById(){
	int assignmentStatus[5] = {0,0,0,0,0};
	struct stuNMarks studentMarks[20];

	loadStudentMarks(studentMarks,&assignmentStatus[0]);
	puts("OK!");

	
	FILE *markp;
	int stid,i=0,m=0;
	/*
	if((fpm=fopen("marks.txt","r"))==NULL){
		printf("Error:Can Not Open!\n");
		return;
	}
		for(i=0;i<20;i++){
			fscanf(fpm,"%s",&studentMarks[i].name);
			fscanf(fpm,"%d",&studentMarks[i].studentID);
			fscanf(fpm,"%f",&studentMarks[i].assignment1);
			fscanf(fpm,"%f",&studentMarks[i].assignment2);
			fscanf(fpm,"%f",&studentMarks[i].assignment3);
			fscanf(fpm,"%f",&studentMarks[i].assignment4);
			fscanf(fpm,"%f",&studentMarks[i].assignment5);
		}
		*/
		printf("Please input the Student ID:\n");
		scanf("%d",&stid);
		for(i=0;i<20;i++){
			if(stid==studentMarks[i].studentID){
				printf("Name      ID    ");
				for(int i=0;i<5;i++){
				if(assignmentStatus[i] = 1){
					printf("Assignment%d  ",i + 1);
				}
				}
				printf("\n");
//				printf("Name      ID    Assignment1  Assignment2  Assignment3  Assignment4  Assignment5  \n");
				printf("%-10s%-6d%-13.2f%-13.2f%-13.2f%-13.2f%-13.2f\n",studentMarks[i].name,studentMarks[i].studentID,studentMarks[i].assignment1,studentMarks[i].assignment2,studentMarks[i].assignment3,studentMarks[i].assignment4,studentMarks[i].assignment5);
				break;
				}
		}
		if(i==20)
			printf("Error: Can Not Find The Student!\n");
		fclose(markp);
		
}

int main()
{
	Inquiry();
	return 0;
}

int getStudentNumber(){
	FILE *markp;
	char studentTemp[256];
	int stuNumber = 0;
	markp = fopen("marks.txt","r");
	 if(markp == NULL){
        printf("Error");
        return 0;
    }
	 while(fgets(studentTemp,256,markp)!= NULL){
		 stuNumber++;
	 }
	 stuNumber -= 1;
	 fclose(markp);
	 return stuNumber;
}

int loadStudentMarks(struct stuNMarks *studentMarks, int* assignmentStatus){
    FILE *markp;
    char studentNameBuffer[10], firstLineBuffer[256];
	int stuNumber = 0;
    int index = 0, i = 0;
	stuNumber = getStudentNumber();
    markp = fopen("marks.txt", "r");
    if(markp == NULL){
        printf("Error");
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
