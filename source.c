/*
Author: Dominic Lewis
Date Created: 20151230
Purpose: Programming Project

To do:

Bugs:

Working on:

Notes:
-On line 22 there is a Windows.h library that is included, this library will only work on windows machines.
*/

//Libaries
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <Windows.h>				//THIS LIBRARY WILL ONLY WORK ON WINDOWS MACHINES

//Symbolic Constants
#define PASSMARK 40.00		//If students mark is 40% or above thhey will be awarded a pass, anything else is a fail.
#define TRUE 1			//Boolean
#define FALSE 0			//Boolean
#define MAXMARK 100		//Maximuim Mark
#define MINMARK 0		//Minimuim mark


//Structures
struct STUDENTDATA {
	int studentUID;
	char studentForname[21];
	char studentSurname[21];
	int assignementMark;
	float examinationMark;
	float moduleMark;
	char moduleGrade[5];
	//This structure contains the students info
};

//Prototype Functions
char Menu();												         		      //This function will create the menu which the user will use to navigate the program.
int IncrementStudentNum(int, struct STUDENTDATA*);								 //This function will be used to increment the amount of students that are being stored inside the program.
void EnterStudent(int*, int, struct STUDENTDATA*);							    //This function will be used to add a new student record to the program.	
int ValidIntID(int min, int max, struct STUDENTDATA*, int numstudents);	       //This function checks if the user is passing a valid ID to the program
int DupeIDCheck(int entry, struct STUDENTDATA*, int numStudents);			  //This function checks if the user UID is a duplicate ID
char *ValidStringEntry(int maxString, char *stringToCheck);			         //This function checks whether or not the string that is entered is valid
void CleanIO();															    //Function which will be used isntead of fflush											
int ValidAssignmentMark(struct STUDENTDATA*);						       // This function will check if the assignment mark is valid
float ValidExaminationMark(struct STUDENTDATA*);					      // This function will check if the examination mark is valid	
float CalculateModuleMark(int numStudent, struct STUDENTDATA*);	    	 //This function will Calculate the students module mark and grade
void DisplayAllStudents(int numstudent, struct STUDENTDATA*);	    	//This function will display all of the student records
int ValidInt(int min, int max);										   //This function will be a general valid int checker
void FindStudentRecord(int numStudent, struct STUDENTDATA*);	      //This function will be used to search and find a student record and then potentially edit it
char YesOrNo();													     //This function will be used to accept a character that is Y/N and validate it
void ReEnterMarks(int numstudent, struct STUDENTDATA*, int j);	    //This function will allow marks to be reentered into a function
float CalculateNewModuleMark(int j, struct STUDENTDATA*);	       //This function will Calculate the students new module grade and mark														
void CalculateAverage(struct STUDENTDATA*, int numStudent);		  //THis function will Calculate the average of all the m
																 //Main Function
void main() {

	//Create struct variables
	struct STUDENTDATA studentInfo[808];

	//Define other local variables
	int numStudents = 0;       //This int will be passed around to count how many students there are. 
	char menuChoice;			//This char will store the users menu choice inside this variable

								//This loop will ensure that the system will not prematurely end 
	do {
		menuChoice = Menu();		////Set the menuChoice variable to whatever the function Menu returns; 

									//Switch statement to call appropriate functions

		switch (menuChoice) {
			//Add new student record 
		case 'A':
			numStudents = IncrementStudentNum(numStudents, studentInfo);	//Set numstudents to be the value of IncremementStudentNum which will be the function which calls the function that creates a new record inside the struct array, passed to it is the number of students currently and the structure(Via referencing). 
			break;

			//Display all student records
		case 'D':
			DisplayAllStudents(numStudents, studentInfo);

			break;

			//Find an individual student record
		case 'F':
			FindStudentRecord(numStudents, studentInfo);
			break;

			//Average Marks
		case 'M':
			CalculateAverage(studentInfo, numStudents);

			break;

			//Quit the program
		case 'Q':
			printf("\n\nThe program will now quit.\n\n");
			Sleep(2000);
			break;

		}  //End of switch statment here 


	} while (menuChoice != 'Q'); //Do loop exits if user inputs q 




								 //Pause and exit system

	system("pause");
	exit(0);

}
//This function will get from the user what input they want to enter into the system.
char Menu() {
	//Local variables
	char menuEntry;

	//Below will tell the user what options are available to them and also validate whatever they choice to input. 
	do {


		printf("\n\nInput A to create a new Student Record\n\nInput D to display all student records\n\nInput F to find an individual students record\n\nEnter M to display the current average mark\n\nEnter Q to quit\n\nEnter Here: ");
		scanf_s(" %c", &menuEntry, 1);
		CleanIO();
		menuEntry = toupper(menuEntry);		//This passes whatever the users inputs through the toupper function to convert it to uppercase.


		if ((menuEntry != 'A') && (menuEntry != 'D') && (menuEntry != 'F') && (menuEntry != 'Q') && (menuEntry != 'M')) {
			printf("\n\nERROR, Please enter an accepted value.\n\n");
			Sleep(1500);
		}			//This function will output an Error message and attempt to correct a users incorrect usage of a system, it also has a delay feature inbuilt so that the user can view the error message before the prompt appears again



	} while ((menuEntry != 'A') && (menuEntry != 'D') && (menuEntry != 'F') && (menuEntry != 'Q') && (menuEntry != 'M'));


	return menuEntry;


}


//This function will be used to increment the number of students when a student is added
int IncrementStudentNum(int numStudents, struct STUDENTDATA *studentInfo) {

	//Local Variables
	int studentAdded = FALSE;	//This variables will ensure the number of students is only incremented whenever a student is succesfully added, allowing the user to quit if neccesary.

	EnterStudent(&studentAdded, numStudents, studentInfo);

	//This loop will ensure that numStudents is only incremented if the user adds a Record;
	if (studentAdded = TRUE) {
		numStudents++;
	}
	return numStudents;

}

//This function will input a student into the STUDENTDATA struct
void EnterStudent(int *studentAdded, int numStudents, struct STUDENTDATA *studentInfo) {

	//Local Variables
	char userContinue;
	//This will check if the user wants to continue
	printf("\n\nAre you certain you would like to add a user?\n\nInput Y if you would like to\n\nInput N if you would like to return to the menu\n\nInput Here: ");
	scanf_s("%c", &userContinue, 1);
	CleanIO();

	userContinue = toupper(userContinue);

	switch (userContinue) {
	case 'N':	//This will leave the student added variable as false so no modification is needed, it will also exit this statment
		break;
	case 'Y':
		*studentAdded = TRUE;			//This will turn student added to true, ensuring that numStudents is incremented in the function that calls

										//Below will add the required information to the records

		printf("\n\nRules\n ID: Each student must have a unique ID, it must be between 101 and 999\nEach of the students names can be a maximuim of 20 characters long and may contain a hyphen.\nThe minimuim mark for both of the marks is 0 and the maximuim is 100\n\n IF A STUDENT MISSES EITHER EXAM ENTER 0 into the system");


		//GET STUDENT ID
		printf("\n\nEnter Student ID: ");

		studentInfo[numStudents].studentUID = ValidIntID(101, 999, studentInfo, numStudents);		//Stores an input from the ValidInt function in student Info


																									//GET STUDENT FORENAME 
		printf("\n\nEnter student forename: ");

		strcpy_s(studentInfo[numStudents].studentForname, 21, ValidStringEntry(20, studentInfo[numStudents].studentForname));	//This line calls Valid String length and copies whatever it returns into the StudentForename struct array.
																																//GET STUDENT SURNAME
		printf("\n\nEnter student surname: ");

		strcpy_s(studentInfo[numStudents].studentSurname, 21, ValidStringEntry(20, studentInfo[numStudents].studentSurname));	//Does the same as above except this time with student surname

																																//Get Assignment mark
		printf("\n\nEnter Assignment Mark: ");
		studentInfo[numStudents].assignementMark = ValidAssignmentMark(studentInfo);

		//Get Examination Mark 
		printf("\n\nEnter Examination Mark: ");
		studentInfo[numStudents].examinationMark = ValidExaminationMark(studentInfo);
		//Calculate mark and grade

		studentInfo[numStudents].moduleMark = CalculateModuleMark(numStudents, studentInfo);
		break;

	}
}
//This function exists to check if an integer is valid in 
int ValidIntID(int min, int max, struct STUDENTDATA *studentInfo, int numStudents) {

	//Local Variables
	int entry, uniqueID = FALSE, uniqueError, rangeError;

	//This loop will cause this to not end unless the value inputed is inside these parameters
	do {

		uniqueError = FALSE;
		rangeError = FALSE;

		scanf_s("%d", &entry);
		CleanIO();

		uniqueID = DupeIDCheck(entry, studentInfo, numStudents);
		//This calls a function which checks whether or not the ID which the user inputs is unique or taken.

		/*
		From line 201 to 221 Leave alone
		*/
		//This if statement will controll the UID error message
		if (entry >= min) {	//Only considers this error if the ID is greater than the minimuim allowed as it's irrelavat that the ID is not unique as it can never be valid. 

			if (uniqueID == TRUE) {
				printf("\n\nError. ID is not unique");
				Sleep(1500);

				uniqueError = TRUE;

			}
		}
		//This if statement will controll the range error message
		if ((entry < min) || (entry > max)) {
			printf("\n\nError. Input Outside accepted range");
			Sleep(1500);
			rangeError = TRUE;
		}

		//This loop will output the Enter Here message 
		if ((uniqueError == TRUE) || (rangeError == TRUE)) {
			printf("\n\nEnter Here:");
		}

	} while ((entry < min) || (entry > max) || (uniqueID == TRUE));			//This checks to ensure that the entry is within the valid parameters and is not taken already 


	return entry;
}

//This function will  ensure that a user's ID isn't taken already
int DupeIDCheck(int entry, struct STUDENTDATA *studentInfo, int numStudents) {
	/*
	Local Variables
	int entry is the variable which will be the SearchID
	*/
	int found = FALSE;
	int i = 101;			//i will start at 101 due to the first ID being 101 
	int j = 0;				//j will be used to access the correct records	
							//This while loop will search for a dupe ID
							//This variable will be used to check the amount of students that are in the system
							//If K == 0 then found is set to FALSE as it can be assumed that no entry's are inside the structure 

							//The below if statement will ensure that the first entry into the system will not be checked ot be unique as it can be assumed that it is unique
	if (numStudents == 0) {
		found = FALSE;
	}

	//The below statement will only execute if numStudent is greater than 1 
	if (numStudents > 0) {

		while ((i < 1000) && (found == FALSE)) {
			if (entry == studentInfo[j].studentUID) {		//If this statement is true then the UID has been found
				found = TRUE;
			}
			//If not found the variables need to be incremented 
			else {
				i++;		//this increments the variable which ID the ID search starts at
				j++;		//this increments the variable which allows us to access the correct studentID record
			}
		}

	}

	return found;
	//Needs to return FALSE to continue
}

//This function checks if a string is valid by checking the characters and the length 
char *ValidStringEntry(int maxString, char *stringToCheck) {

	//Local Variables
	int error = FALSE;
	int secondError = TRUE;		//True due to bug when set as False, my character checks sets everything as an invalid character
	int i, nameLength, secondErrorCounter = 0;

	//Loop that ensures the name grabber loops
	do {
		fflush(stdin);	//Added fflush here as CleanIO has compatibility issues 
		printf("\n");	//This ensures that the the IO steam contains the NewLine Symbol.
		gets_s(stringToCheck, 100);	//Buffer size is larger to allow an invalid input to be inputted

		nameLength = strlen(stringToCheck);		//Initiliase int nameLength to the length the string is 

		error = FALSE;						//Error will be the flag which will be checked at the end of the do while statement 
		secondError = TRUE;

		//Check length 	
		//Error message if the string entered is larger than the maximuim size, or smaller.
		if (nameLength > maxString) {
			printf("\n\nError. Name too long");
			error = TRUE;						//Set error flag to TRUE 
		}
		if (nameLength == 0) {
			printf("\n\nError. Please input a name");
			error = TRUE;
		}






		//ConvertNameTestingString To upper case for easier testing 

		//On each iteration of this loop it will capitalse the different characters inside the name
		for (i = 0; i < nameLength; i++) {
			stringToCheck[i] = toupper(stringToCheck[i]);

		}


		//The for statement here is used to ensure that all characters are being considered
		for (i = 0; i < nameLength; i++) {




			//This if statement compares the values inside the string to the accepted values that the system accepts 
			if ((stringToCheck[i] == 'A') || (stringToCheck[i] == 'B') || (stringToCheck[i] == 'C') || (stringToCheck[i] == 'D') || (stringToCheck[i] == 'E') || (stringToCheck[i] == 'F') || (stringToCheck[i] == 'G') || (stringToCheck[i] == 'H') || (stringToCheck[i] == 'I') || (stringToCheck[i] == 'J') || (stringToCheck[i] == 'K') || (stringToCheck[i] == 'L') || (stringToCheck[i] == 'M') || (stringToCheck[i] == 'N') || (stringToCheck[i] == 'O') || (stringToCheck[i] == 'P') || (stringToCheck[i] == 'Q') || (stringToCheck[i] == 'R') || (stringToCheck[i] == 'S') || (stringToCheck[i] == 'T') || (stringToCheck[i] == 'U') || (stringToCheck[i] == 'V') || (stringToCheck[i] == 'W') || (stringToCheck[i] == 'X') || (stringToCheck[i] == 'Y') || (stringToCheck[i] == 'Z') || (stringToCheck[i] == '-')) {


				secondErrorCounter++;

			}

			//If second Error counter is lesst then the amount of characters being checked then one must be an erroneous character
			if (secondErrorCounter == nameLength) {
				secondError = FALSE;
			}


		}

		//This if statement will output invalid character if secondError is true
		if (secondError == TRUE) {
			printf("\n\nError. Invalid Character");

		}

		//Output and error if the ERROR flag is set to true
		if ((error == TRUE) || (secondError == TRUE)) {
			Sleep(1200);
			printf("\n\nPlease Enter again: ");
		}




	} while ((error == TRUE) || (secondError == TRUE));

	return stringToCheck;

}


//This function will replace the fflush
void CleanIO()
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF)
	{
	}
}

//This function will accept an input for the Assignment Mark and validate it
int ValidAssignmentMark(struct STUDENTDATA *studentInfo) {

	//Local Variables
	int entry;
	int validMark;
	//Loop to ensure that an acceptable value is returned
	do {

		validMark = FALSE;

		scanf_s("%d", &entry);
		CleanIO();
		//If Statment to validate int as long as it's within the accepted parameters
		if ((entry >= MINMARK) && (entry <= MAXMARK)) {
			validMark = TRUE;

		}
		//If the mark is invalid this error message will be outputted
		else {
			printf("\n\nError. Invalid amount entered.");
			Sleep(1000);
			printf("\n\nPlease Re-Enter: ");

		}

	} while (validMark == FALSE);


	return entry;
}

//This function will accept an input for the examination mark
float ValidExaminationMark(struct STUDENTDATA *studentInfo) {

	//Local Variables
	float entry;
	int validMark;
	//Loop to ensure that an acceptable value is returned
	do {

		validMark = FALSE;

		scanf_s("%f", &entry);
		CleanIO();
		//If Statment to validate int as long as it's within the accepted parameters
		if ((entry >= MINMARK) && (entry <= MAXMARK)) {
			validMark = TRUE;

		}
		//If the mark is invalid this error message will	be outputted
		else {
			printf("\n\nError. Invalid amount entered.");
			Sleep(1000);
			printf("\n\nPlease Re-Enter: ");

		}

	} while (validMark == FALSE);


	return entry;
}
//This function will calculate the sutdents Module mark and also the students grade
float CalculateModuleMark(int numStudents, struct STUDENTDATA *studentInfo) {

	//Local variables
	float moduleMark = 0;
	char pass[5] = "PASS";
	char fail[5] = "FAIL";

	//First the module Mark will be calculate
	moduleMark = (studentInfo[numStudents].examinationMark * 0.4) + (studentInfo[numStudents].assignementMark * 0.6);


	//Assign Grade
	if (moduleMark >= PASSMARK) {
		strcpy_s(studentInfo[numStudents].moduleGrade, 5, pass);			//This will copy PASS into the module mark if they meet the requriements 
	}
	else {
		strcpy_s(studentInfo[numStudents].moduleGrade, 5, fail);
	}




	return moduleMark;

}

//This function will display all students that have been inputted so for
void DisplayAllStudents(int numStudents, struct STUDENTDATA *studentInfo) {
	//Local Variables
	int turnBasedDisplay, i = 0;

	if (numStudents >0) {
		printf("\n\nWould you like all the students to be displayed at once or one at a time?(0 for all at once, 1 for turn based): ");
		turnBasedDisplay = ValidInt(0, 1);

		// While which will enure the correct amount of students are outputted
		while (i < numStudents) {

			printf("\n\nFIRST NAME: %s\nLAST NAME: %s\nASSIGNMENT MARK: %3d\nEXAMINATION MARK: %3.2f\nMODULE MARK: %3.2f\nMODULE GRADE: %s", studentInfo[i].studentForname, studentInfo[i].studentSurname, studentInfo[i].assignementMark, studentInfo[i].examinationMark, studentInfo[i].moduleMark, studentInfo[i].moduleGrade);

			//If statement for turn based outputting
			if (turnBasedDisplay == TRUE) {
				printf("\n");
				system("pause");
				printf("\n");
			} //End of if
			i++;
		} //End of while
	}
	else {
		printf("\n\nNo Students inside system\n\n");
	}
}

//This function will check for a valid int input and return it
ValidInt(int min, int max) {
	//Local Variables
	int entry;
	int validInt;

	//This will validate the int
	do {
		printf("\n"); //Ensuring that the newline character is present 
		fflush(stdin);	//Added fflush back due to compatibility issue
		validInt = FALSE;
		printf("\n\n Please enter a valid whole number(between %d and %d): ", min, max);
		scanf_s("%d", &entry);
		fflush(stdin);	//Added fflush back due to compatibility issue
		if ((entry >= min) && (entry <= max)) {
			validInt = TRUE;
		}
		else {
			printf("\n\nError. Invalid Number.");
		}

	} while (validInt == FALSE);

	return entry;


}

//This funciton will be used to find a relevant student record and also will be passed a reference to numStudent from the main variable
void FindStudentRecord(int numStudent, struct STUDENTDATA *studentInfo) {
	//Local Variables
	int requestStudentID;
	char modify = 'N';
	int found = FALSE;
	int i = 101;			//i will start at 101 due to the first ID being 101 
	int j = 0;				//j will be used to access the correct records	
							//This while loop will search for a dupe ID

							//Prompt for student ID
	printf("\n\nEnter Student ID(101-999): ");
	requestStudentID = ValidInt(101, 999);

	//While loop which searches all ID's
	do {

		//If statment that checks each record of a student for relvant ID 
		if (requestStudentID == studentInfo[j].studentUID) {		//If this statement is true then the UID has been found
			printf("\n\nFIRST NAME: %s\nLAST NAME: %s\nASSIGNMENT MARK: %3d\nEXAMINATION MARK: %3.2f\nMODULE MARK: %3.2f\nMODULE GRADE: %s", studentInfo[j].studentForname, studentInfo[j].studentSurname, studentInfo[j].assignementMark, studentInfo[j].examinationMark, studentInfo[j].moduleMark, studentInfo[j].moduleGrade);
			found = TRUE;


			printf("\n\nWould you like to modify this record(Y/N): ");
			fflush(stdin);
			modify = YesOrNo();

			if (modify == 'Y') {

				ReEnterMarks(numStudent, studentInfo, j);
			}


		}
		else {
			i++;		//this increments the variable which ID the ID search starts at
			j++;		//this increments the variable which allows us to access the correct studentID record
		}
	} while ((i < 1000) && (found == FALSE));

	//Error Message for if found == FALSE still here 
	if (found == FALSE) {

		printf("\n\nError. Invalid ID\n\n");

	}

	//End of function 


}


//This function validates a Y/N
char YesOrNo() {

	//Local Variables
	int valid = FALSE;
	char entry = 'Z';

	//This do statement will accept and input and convert it
	do {

		scanf_s(" %c", &entry, 1);	//Space inside the scanf_f before the function modifier ensures it doesn't skip this statment 
									//Convert it to uppercase
		entry = toupper(entry);


		if ((entry == 'Y') || (entry == 'N')) {
			valid = TRUE;
		}
		else {
			printf("\n\nError. Invalid Character");
			Sleep(1000);
			printf("\n\nPlease enter a valid character(Y/N): ");
		}

		CleanIO();		//Clean down here as problematic at the top 

	} while (valid == FALSE);			//Do this while valid is false



	return entry;

}

//This function will be used to alter a students mark 
void ReEnterMarks(int numstudent, struct STUDENTDATA*studentInfo, int j) {
	//Local Variable
	int fieldChange;
	char entryContinue;
	int i = 0;
	int exit = FALSE;
	printf("\n\nAre you sure you want to continue?(Y/N): ");

	entryContinue = YesOrNo();	//Gets a return value from this function 
								//Switch Statement
	do {

		switch (entryContinue) {
			//If user wants to continue
		case 'Y':
			printf("\n\nWhich mark would you like to alter\n\nInput 1 for Assignment mark\n\nInput 2 for Examination mark\n\nInput 3 to Quit\n\nInput Here: ");
			fieldChange = ValidInt(1, 3);

			//Nested switch
			switch (fieldChange) {
			case 1:
				//ASSIGNMENT MARK 

				printf("\n\nStudent Forename:%s\nStudent Surname:%s\nAssignment Mark:%3d", studentInfo[j].studentForname, studentInfo[j].studentSurname, studentInfo[j].assignementMark);
				printf("\n\nPlease enter a valid Assignment Mark(0-100): ");
				studentInfo[j].assignementMark = ValidAssignmentMark(studentInfo);		//Redo assignment mark
				studentInfo[j].moduleMark = CalculateNewModuleMark(j, studentInfo);		//Recalculate module mark
				break;

			case 2: //EXAMINAtiON MARK
				printf("\n\nStudent Forename:%s\nStudent Surname:%s\nExamination Mark:%3.2f\nPlease enter new value for Examination Mark(0-100)", studentInfo[j].studentForname, studentInfo[j].studentSurname, studentInfo[j].examinationMark);
				printf("\n\nPlease enter a valid examination mark(0-100): ");
				studentInfo[j].examinationMark = ValidExaminationMark(studentInfo);
				studentInfo[j].moduleMark = CalculateModuleMark(j, studentInfo);
				break;
			case 3: //QUIT
				exit = TRUE;
				break;
				//End of nested switch
			}

			//If user wants to exit 
		case 'N':
			exit = TRUE; //Set exit to true so that the user can exit
			break;


		}				//End of primary switch

						//end of do
	} while (exit == FALSE);



}

//This function will recalculate the module mark for the student
float CalculateNewModuleMark(int j, struct STUDENTDATA*studentInfo) {
	//Local variables
	float moduleMark = 0;
	char pass[5] = "PASS";
	char fail[5] = "FAIL";

	//First the module Mark will be calculate
	moduleMark = (studentInfo[j].examinationMark * 0.4) + (studentInfo[j].assignementMark * 0.6);


	//Assign Grade
	if (moduleMark >= PASSMARK) {
		strcpy_s(studentInfo[j].moduleGrade, 5, pass);			//This will copy PASS into the module mark if they meet the requriements 
	}
	else {
		strcpy_s(studentInfo[j].moduleGrade, 5, fail);
	}




	return moduleMark;

}

//This function will calculate the average marks
void CalculateAverage(struct STUDENTDATA*studentInfo, int numstudent) {

	//Local Variables
	int switchControl, i;
	float num = 0;
	float average;

	//Prompt For Input

	printf("\n\n1.Display average Assignment Mark\n\n2.Display average Examination Mark\n\n3.Display average Module mark\n\nEnter Here: ");
	switchControl = ValidInt(1, 3);		//Call valid int function to get a user input 



	switch (switchControl) {


	case 1:	//Average Assignment Mark  

		if (numstudent == 0) {
			printf("\n\nError. No students inputted into the system\n\n");
		}
		else {

			for (i = 0; i < numstudent; i++) {

				num += studentInfo[i].assignementMark;
			}
			average = num / i;

			printf("\n\nAverage Assignment Mark: %3.2f\n\n", average);
		}

		break;


	case 2: //Examination Mark 

		if (numstudent == 0) {
			printf("\n\nError. No students inputted into the system\n\n");
		}
		else {
			for (i = 0; i < numstudent; i++) {

				num += studentInfo[i].examinationMark;
			}
			average = num / i;

			printf("\n\nAverage Examination Mark: %3.2f\n\n", average);

		}
		break;

	case 3:

		if (numstudent == 0) {
			printf("\n\nError. No students inputted into the system\n\n");
		}
		else {
			for (i = 0; i < numstudent; i++) {

				num += studentInfo[i].moduleMark;
			}
			average = num / i;

			printf("\n\nAverage Assignment Mark: %3.2f\n\n", average);

		}
		break;
	}

}
