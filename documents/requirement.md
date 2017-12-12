## Program Structure

- System Menu
  - Grade
  - Inquire
    - By index
    - By student ID
    - Quit
  - Sort
  - Quit

## Description

### Menu (Main Menu)

- Display an order list (Menu) for every function
- Read the parameter inputed by user
- call the correspond sub-function

### Grade

- ask user to input the assignment index and question(s) amount.
  - `5` means `Assignment 5`
- Input the score of every question for every student
  - Calculate the total score for the student
  - Start the next student
- all students' score save to a file call `marks.txt`

```
Format in file marks.txt
Name    ID    Assignment1   Assignment2  ......
Tony    1234  3.5           ...    
Andrew  1235  3.3           ...    
Amy     2323  4             ...     
........ 
```

### Inquire

> Like Search for the student

- Display a order list (sub-Menu)
- Read the parameter inputed by user
- call the correspond sub-function(i.e. "sub-sub-function")

1. `By Index`
   - ask user to input a index
   - output a list with information: `index` and `Student Name`
     - ask user to input a `index`
   - read the `index` inputed by user
   - display that student's information (Marks)
2. `By student ID`
   - ask user to input a student ID
   - read the `Student ID` inputed by user
   - display that student's information (Marks)
3. `Quit`
   - go back to main menu

### Sort

> This part have special request: use list(链表)

- sort the students’ list (file `students.txt`) according to the total marks for all the assignments.
- save the result to `sorted.txt`
- output the sorted result to the screen 

```
Format in file students.txt
Name   ID     
Tony   1234         
Andrew 1235     
Amy    2323
......
```

```
Format in file sorted.txt
Name   ID     Total     
Andrew 1235   15         
Amy    2323   12      
Tony   1234   11.3
......
```

### Quiz

- finish all jobs
- quit the system

## More information

1. There are no more than 20 students in total 
2. Student's ID is a `4 digits number` and not begin with a `0`
3. Max Assignment amount is `5`
4. Max questions number in an Assignment is `10`
5. Marks for each questions are equal
6. Letter grades

| letter | Grade |
| ------ | :---: |
| A      | 4pts  |
| B      | 3pts  |
| C      | 2pts  |
| D      | 1pts  |

1. The user always give the valid inputs

## Requirement

1. Using Main and Sub-functions
2. User-friendly
   - input notifications