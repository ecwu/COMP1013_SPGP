#include<stdio.h>

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

int Index()
{
	FILE *marks;
	int inputOfIndex, i = 0;
	struct stuNMarks studentList[20];
	char menu1[100], menu2[100], menu3[100], menu4[100], menu5[100], menu6[100], menu7[100];//define 7 string to store the elements of menu

	marks = fopen("marks.txt", "r");

	if(fopen("marks.txt", "r") == NULL)//input the value from .txt to program
	{
		printf("open error");
	}else
	{
		if(i == 0)//identify the first menu row, if it is, jump to next row to scan value
		{	
			fscanf(marks, "%s %s %s %s %s %s %s", menu1, menu2, menu3, menu4, menu5, menu6, menu7);
			i = 1;//let i = 1, and store the first student infomation below
		}
		while(i > 0 && fscanf(marks,"%s %d %f %f %f %f %f", studentList[i].name, &studentList[i].studentID, &studentList[i].assignment1, &studentList[i].assignment2, &studentList[i].assignment3, &studentList[i].assignment4, &studentList[i].assignment5) != EOF)
		{
			i++;
		}
	}


	printf("%-8s %-10s %-6s %-13s %-13s %-13s %-13s %-13s\n","index", menu1, menu2, menu3, menu4, menu5, menu6, menu7);//print the element list of menu

	for(int j = 1; j < i; j++)//print out the student and use j as the pointer to search in the index inquiry
	{
		printf("%-8d %-10s %-6d %-13.2f %-13.2f %-13.2f %-13.2f %-13.2f\n", j, studentList[j].name, studentList[j].studentID, studentList[j].assignment1, studentList[j].assignment2, studentList[j].assignment3, studentList[j].assignment4, studentList[j].assignment5);
	}

	printf("\n\n\nPlease input the index you want to find:");
	scanf("%d", &inputOfIndex);

	printf("\n\n\n%-10s %-6s %-13s %-13s %-13s %-13s %-13s\n", menu1, menu2, menu3, menu4, menu5, menu6, menu7);
	printf("\n%-10s %-6d %-13.2f %-13.2f %-13.2f %-13.2f %-13.2f\n", studentList[inputOfIndex].name, studentList[inputOfIndex].studentID, studentList[inputOfIndex].assignment1, studentList[inputOfIndex].assignment2, studentList[inputOfIndex].assignment3, studentList[inputOfIndex].assignment4, studentList[inputOfIndex].assignment5);

	return 0;
}

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

		printf("Please Input Number:");
		scanf("%d", &modeSelect);

		switch (modeSelect) {

			case 1: Index(); break;
			//case 2: StudentID(); break;
	
			default: printf("Number should between 1 -- 2!\n");
		}
	return 0;
}

// int main()
// {
// 	Inquiry();
// 	return 0;
// }