Please note the files which compile correctly are those with "ok" at the end. 

 Please ignore the folder contained in this repo, it contains a copy of the code files that were put up on moodle.

*******
##### READ ME #####
	  *******


Team: 8
Members: Colm Tang (16760705) and Lorenzo Battilocchi (16341353)

Project: COMP 10050 (Software Engineering Project I) - CrossFire Board Game

Subdivision of Tasks Summary
****************************

We subdivided the tasks between us. I did the modification to the original code and proposed using header files to tidy up 
the main() function file. 

The main part of the coding was done by my partner, Colm, although he wasn't able to commmit to GitHub due to technical
problems with his account on the GitHub.

Part A: Design Choices
**********************


	For this assignment, we chose to use two header files (CFedit.h and CFPlayers.h) linked to the main file (mainedit.c). In these header file, 
	we placedall the functions that were then called from mainedit.c (the main program file). 
	
	Unfortunately, we found it impossible to place the player capabilities  allocation section of the code into the header file, since it does 
	not seem to be possible to return values to a structure in C from a function.

Part B: Code Step-through
*************************

	We included all necessary standard libraries and the custom header file in lines 1-5. 
	At  line 7, flow control is transferred to main(void), and the random number generator is initialised, like the structure "players". We use 
	two variables, namely "row" and "column" to define the board size for the game, and two more structs for the currentslot and foundSlots, 
	which keep the current slot the player is in and the slots that they have visited respectively. 

	At line 15, the function getboardsize() is called, which queries the user to input dimensions for the board. These dimensions can be max 7x7 
	and min 1*1. 

	Another 4 pointers are created for board co-ordinates, namely "*topleft", "*topright", "*bottomleft" and "*bottomright".

	Following is a call to function getplayeramount. This time the value returned by the function is assigned to the variable "playeramount" 
	which is then used throughout the code at various stages.

	We proceed to physically creating the board where our characters will interact with each other. We therefore call the createboard() function, 
	which takes in the boardsize and the four aforementioned pointers as arguments.

	We then print a summary of the values received by the program thus far in line 26.

	A call is made to the function getDesiredElement, which takes as input the boardsize and the pointers to the row and column of the slot that 
	the user wants to retrieve.

	A choice mechanism is used to choose from which corner to start the search (ie to find the quickest path to the desired slot).

	We then query the user for the amount of players in the game, as in previouse Assignment 2. The game asks for the number of players in the 
	game, their name and respectaive type, which is stored in a structure (player) declared in header file CFedit.h. 
	
	Similarly to previous Assignment, the player's capabilities are randomly assigned according to the constraints given, and a plaayer summary 
	is printed at the end.

	We randomised the player placement on the board using the for loop at line 145.
9
	A menu for gameplay is provided in lines 152-177, where the player can choose the desired action depending on the game status.

Part C: Detailed Break-down of function operations
**************************************************
	
	1. int getboardsize(): 
	**********************
		This function takes no arguments and returns an integer. 

		It queries the user for a size of the board, and this is assigned to the integer 
		variable "boardsize". An error checking is performend, which checks the value of "boardsize" is between 1 and 7. If it is not conformant 
		to those constraints, the program will keep asking for input until it is conformant. This value is then returned to the main() function.

	2. int getplayeramount():
	*************************
		This function again takes no arguments and returns an integer. 

		It queries the user for the number of players that will play the game, and 
		this value is stored in the integer variable "playeramount". An error checking is performed, which checks the value of "playeramount" is 
		between 2 and 6. If this is not the case, it will keep asking for input until it is conformant. 

		This value will be returned to main() function.

	3. void createboard():
	**********************
		This function takes as arguments the integer value "boardsize", and a set of pointers to the structure "slot" (namely "**topleft", 
		"**topright", "**bottomleft" and "**bottomright").
		
		A variable lenght array (VLA) is created using the malloc function with parameter "(boardsize * sizeof(struct slot))". After the creation 
		of the array, the board is indexed and filled with the corresponding co-ordinates. These co-ordinates are then randomly allocated a slot 
		type (LEVEL GROUND, HILL or CITY).	
		
		This function doesn't return any value (void).

	4. void getDesiredElement():
	****************************
		This function takes as argument the integer maxsize, and two pointers to integers (namely "*row" and "*col") and returns void.

		The user is prompted to enter a set of co-ordinates of a slot on the board. The function then finds the slot on the board. If the 
		inputted value is outside of the board, the query for input is repeated until the value is within acceptable range.

		The function returns no value (void).

	5. reachDesiredElement():
	*************************
		This function takes in three arguments. These are "int row", "int column" and the structure component "slot *initialSlot". 

		It traveerses the board to reach the inputted element starting at the player's current position, displaying the move at each iteration.

		It returns struct slot*.

	6. void instructions(int i):
	****************************
		This function displays the options available to each player at their turn. 

		It does not return anything (void).

	7.  void playermove(int *currentrow, int *currentcol):
	******************************************************
		This function takes in two pointers to ints and does the movement of the players. It provides the player with 4 options to move in the 
		four directions. 

		A switch statement takes care of the selection process. Error checking is present in line 358 of CFedit.h.

	8. void quitting(int *i, int *playerhealth):
	********************************************

		This function gives the player the option to leave the game, in which case their health is brough down to 0 and they are eliminated from the game. 

	9. attack:
	**********
