# Structured Programming
> Repo for UICcst 16 Y2A Structured Programming Group Project.

**This Group project require us to develop a system for teacher to grade assignment.**

## Program Structure

- System Menu
  - Grade
  - Inquire
    - By index
    - By student ID
    - Quit
  - Sort
  - Quit
  
## More Information
### Menu
- Display an order list for every function
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
Name    ID    Assignment1   Assignment2  .....
Tony    1234  3.5           ...    
Andrew  1235  3.3           ...    
Amy     2323  4             ...     
........ 
```
