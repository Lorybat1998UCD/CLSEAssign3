#ifndef CROSSFIREOPERATIONS_H_
#define CROSSFIREOPERATIONS_H_

#endif /* CROSSFIREOPERATIONS_H_ */
#include <stdio.h>
#define boardsize 7;
#define reqDist 3;

typedef int bool;
enum { false, true };

struct slot
{
	int row;
	int column;
	char slottype[10];
	struct slot *left;
	struct slot *right;
	struct slot *up;
	struct slot *down;
}slot;

struct player
{
	char name[20];
	char class[10];
	int type; 
    int health;
	int smartness;
	int magic;
	int strength;
	int dexterity;
	int luck;
	int currentrow;
	int currentcol;
	int turn;
	int attakcer;
	int defender;
}player;

int getboardsize();

int getplayeramount();

void createboard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);

void getDesiredElement(int maxsize, int * row, int * col); 

struct slot *  reachDesiredElement(int row, int column, struct slot * initialSlot);

void findSlots(int reqDist, int currDist,  struct slot *currSlot, struct slot *foundSlots, int *count,  bool explored[7][7]); //not complete



void instructions(int i);

void playermove(int currentrow, int currentcol);

void quitting(int i, int *playerhealth);
//--------------------------------------------------------------------------------
int getboardsize()
{
	int boardsize;
	printf("Enter a size for the board, it will be in the format NxN:\n");
	printf("A number between 1 and 7\n");
	scanf("%d",&boardsize);
	while(boardsize <1 || boardsize >7)
	{
		printf("A number between 1 and 7\n");
		scanf("%d",&boardsize);
	}
	return boardsize;
}

void getDesiredElement(int boardsize, int *row, int *col)
{
	printf("Please enter the column and the Row of the desired slot \n");
	printf("Note that size of the board is %dx%d\n", boardsize,boardsize);

	printf("Row: ");
	scanf("%d", row);	//cycles in cases where the point is off the board
	while(*row < 0 || *row >= boardsize)
	{
		printf("Error: Incorrect row dimension\n");
		scanf("%d", row);
	}

	printf("Column: ");
	scanf("%d", col);
		
	while(*col < 0 || *col >= boardsize)
	{
		printf("Error: Incorrect column dimension\n");
		scanf("%d", col);
	}
}

void createboard(int boardsize, struct slot **topleft, struct slot **topright, struct slot **bottomleft, struct slot **bottomright)
{	
	int i,j;
	struct slot **board = malloc(boardsize * sizeof(struct slot*));
	
	for(i=0;i<boardsize;i++)
	{
		board[i] = malloc(boardsize * sizeof(struct slot));
		
		for(j=0;j<boardsize;j++)
		{
			board[i][j].row = i;
			board[i][j].column = j;
		}
	}
	
	for(i=1;i<boardsize-1;i++)
	{
		for(j=1;j<boardsize-1;j++) //fills adj spots of slots
		{					//that are not on the outer ring
			board[i][j].up = &board[i-1][j];
			board[i][j].right = &board[i][j+1];
			board[i][j].left = &board[i][j-1];
			board[i][j].down = &board[i+1][j];
		}
	}
	
	for(j=1;j<boardsize-1;j++) //fills adj spots of slots
	{					//that are on the 1st and last row but not corners
		board[0][j].up = NULL;
		board[0][j].right = &board[0][j+1];
		board[0][j].left = &board[0][j-1];
		board[0][j].down = &board[1][j];
		
		board[boardsize-1][j].up = &board[boardsize-2][j];
		board[boardsize-1][j].right = &board[boardsize-1][j+1];
		board[boardsize-1][j].left = &board[boardsize-1][j-1];
		board[boardsize-1][j].down = NULL;
	}
	
	for(i=1;i<boardsize-1;i++)
	{
		board[i][0].up = &board[i][1];
		board[i][0].right = &board[i-1][0];
		board[i][0].left = NULL;
		board[i][0].down = &board[i+1][0];
		
		board[i][boardsize-1].up = &board[i-1][boardsize-1];
		board[i][boardsize-1].right = NULL;
		board[i][boardsize-1].left = &board[i][boardsize-2];
		board[i][boardsize-1].down = &board[i+1][boardsize-1];
	}
	
	board[0][0].right = &board[0][1]; //adj slots to topleft corner
	board[0][0].down = &board[1][0];
	
	board[0][boardsize-1].left = &board[0][boardsize-2]; //adj slots to topright corner
	board[0][boardsize-1].down = &board[1][boardsize-1];
	
	board[boardsize-1][0].up = &board[boardsize-2][0]; //adj slots to bottomleft corner
	board[boardsize-1][0].right = &board[boardsize-1][1];
	
	board[boardsize-1][boardsize-1].up = &board[boardsize-2][boardsize-1]; //adj slots to bottomright corner
	board[boardsize-1][boardsize-1].left = &board[boardsize-1][boardsize-2];
	
	*topleft = &board[0][0];
	*topright = &board[0][boardsize-1];
	*bottomleft = &board[boardsize-1][0];
	*bottomright = &board[boardsize-1][boardsize-1];
	
	for(i=0;i<boardsize;i++)
	{		
		for(j=0;j<boardsize;j++)
		{
			int random_R= rand()%3; // random seed for random allocation of slots
			if (random_R==0) //LEVEL GROUND 
			{
				strcpy(board[i][j].slottype, "LEVEL GROUND");
				printf("Board %d,%d is type \"LEVEL GROUND\"\n", i+1,j+1);
			} 	
			else if (random_R == 1) //CITY
			{
				strcpy(board[i][j].slottype, "CITY");
				printf("Board %d,%d is type \"CITY\"\n", i+1,j+1);
			}
			else if (random_R == 2) // HILL
			{
				strcpy(board[i][j].slottype, "HILL");
				printf("Board %d,%d is type \"HILL\"\n", i+1,j+1);
			}
			else{} //not really necessary, but just in case
		}
	}
}

struct slot *reachDesiredElement(int row, int column, struct slot * initialSlot)
{
	bool found = false;
						//current slot
	struct slot *currentSlot = initialSlot;

	printf("\nFunction reachDesiredElement invoked\n");

	//prints the column and the row of the initial slot from which the search starts
	printf("Initial slot (%d, %d) -> \n",initialSlot->row+1,initialSlot->column+1);


	//while the slot is not found
	while(found == false){


		//if the row of the current slot is > of the row of the desired slot,
		//we move up
		if(currentSlot->row > row){
			//the current slot now points to the slot one row up
			currentSlot = currentSlot->up;
			//prints the column and the row of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);
		}
		//if the row of the current slot is < of the row of the desired slot,
		//we move down
		if(currentSlot->row < row){
			//the current slot now points to the slot one row down
			currentSlot = currentSlot->down;
			//prints the row and the column of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);

		}
		//if the column of the current slot is > of the column of the desired slot,
		//we move left
		if(currentSlot->column > column){

			//the current slot now points to the slot one column left
			currentSlot = currentSlot->left;
			//prints the row and the column of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);
		}

		//if the column of the current slot is < of the column of the desired slot,
		//we move right
		if(currentSlot->column < column){

			//the current slot now points to the slot one column right
			currentSlot = currentSlot->right;
			//prints the row and the column of the current slot
			printf("Current slot (%d, %d) -> \n",currentSlot->row,currentSlot->column);

		}
		//if the current slot is at a column and a row equal to the desired column and row, respectively
		// we found the slot
		if(currentSlot->column == column && currentSlot->row == row){
			printf("Found\n");
			found = true;
		
		}
	
	}
	//returns the found slot
	return currentSlot;
}

void findSlots(int reqDist, int currDist,  struct slot * currSlot, struct slot * foundSlots, int * count,  bool explored[7][7])
{
	//The base case: the current slot is at the required distance from the starting slot
	if(currDist == reqDist)
	{
		//the current slot was not explored
		if(explored[currSlot->row][currSlot->column] == false)
		{
			//The next available position (indicated by count) at foundSlots points to the current slot
			*(foundSlots + *count) = *currSlot;
			//the counter is incremented
			(*count)++;
			//the matrix of the explored slots set to true the element at the row and column of the current slot
			explored[currSlot->row][currSlot->column] = true;
		}
	}
	//The recursive call: the current slot is at a distance that is less than the required distance (more slots still have to be traversed)
	else{
		//if the current slot has the up slot != NULL (i.e. the slot is not in the first row)
		if(currSlot->up != NULL)
		{
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the up slot
			findSlots(reqDist, currDist +1,  currSlot->up, foundSlots, count, explored);
		}
		//if the current slot has the right slot != NULL (i.e. the slot is not in the last column)
		if(currSlot->right != NULL)
		{
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the right slot
			findSlots(reqDist, currDist +1,  currSlot->right, foundSlots, count, explored);
		}
		//if the current slot has the down slot != NULL (i.e. the slot is not in the last row)
		if(currSlot->down != NULL)
		{
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the down slot
			findSlots(reqDist, currDist +1,  currSlot->down, foundSlots, count, explored);
		}
		//if the current slot has the left slot != NULL (i.e. the slot is not in the first column)
		if(currSlot->left != NULL)
		{
			//invokes function find slots incrementing the current Distance (currDist) and setting the current slot to the left slot
			findSlots(reqDist, currDist +1,  currSlot->left, foundSlots, count, explored);
		}
	}
}


int getplayeramount()
{
	int playeramount;
	printf("Enter amount of players between 2 and 6\n");
	scanf("%d", &playeramount);
	
	while(playeramount<2 || playeramount>6)
	{
		printf("between 2 and 6:\n");
		scanf("%d", &playeramount);
	}
	
	return playeramount;
}

void instructions(int i)
{
	printf("Player %d: \n",i);
	printf("Enter 1 to move to adjacent slot"
			"Enter 2 to attack"
			"Enter 3 to quit the game\n");
}

void playermove(int *currentrow, int *currentcol)
{
	int choice;
	printf("Enter 1 to move up, 2 to move right,"
			"Enter 3 to move down, 4 to move left\n");
	do
	{
	scanf("%d",choice);
	
		switch(choice)
		{
			case 1: // move up
				*currentrow -=1;
				
				break; 
				
			case 2: // move right
				*currentcol +=1;
				
				break;
			
			case 3: // move down
				*currentrow +=1;
				
				break;
		
			case 4: // move left
				*currentcol -=1;
				
				break;
	
	}
	}while(choice < 1 || choice > 4)
}

void quitting(int *i,int *playerhealth)
{
	int leavegame;
	printf("Are you sure you want to quit? 1 for yes, 2 for no");
				scanf("%d",leavegame);
				while(leavegame != 1 && leavegame != 2)
				{
					printf("Guess you're not sure,Try again");
					scanf("%d",leavegame);
				}
				

				if(leavegame == 1)
				{
					*playerhealth = 0;
				}
				else
				{
					printf("Back to the previous choice\n");
					*i--;
				}
}

void near_Attack(struct players * attacker)
{
	/*
	 * This function only tells us the adjecent players to the attacker.
	 *
	 */

	//printf("\n%d---(%d, %d)\t", attacker->place->player_Identifier, attacker->place->row, attacker->place->column);
	if(attacker->place->row!=0 && attacker->place->up->player_Identifier!= -1)
	{
		printf("%s We have found %s above you!\n",cases[attacker->player_Identifier -20].name_one, cases[attacker->place->up->player_Identifier -20].name_one);
		printf("%d found Over %d!\n", attacker->place->up->player_Identifier,attacker->player_Identifier );
	}
	if(attacker->place->row!=6 && attacker->place->down->player_Identifier !=-1)
	{
		printf("%s We have found %s under you!\n",cases[attacker->player_Identifier -20].name_one, cases[attacker->place->down->player_Identifier -20].name_one);
		printf("%d found Under %d!\n", attacker->place->down->player_Identifier,attacker->player_Identifier );
	}
	if(attacker->place->column!=0 && attacker->place->left->player_Identifier !=-1)
	{
		printf("%s We have found  %s to the left you!\n",cases[attacker->player_Identifier -20].name_one, cases[attacker->place->left->player_Identifier -20].name_one);
		printf("%d found to the left of %d!\n",attacker->place->left->player_Identifier,attacker->player_Identifier );
	}
	if(attacker->place->column!=6 && attacker->place->right->player_Identifier !=-1){
		printf("%s We have found  %s to the right of you!\n",cases[attacker->player_Identifier -20].name_one, cases[attacker->place->right->player_Identifier -20].name_one);
		printf("%d found to the right of %d!\n", attacker->place->right->player_Identifier,attacker->player_Identifier );
}