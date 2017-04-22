#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "CFedit ok.h"

int main(void)
{	
srand ( time(NULL));
	struct player player[6];
	int row,column;
	struct slot *currentslot = NULL;
	struct slot *foundslots;
	int boardsize = getboardsize();
	bool explored[7][7];
	int count = 0;
	
	struct slot *topleft; // (0,0)
	struct slot *topright; // (0,boardsize-1)
	struct slot *bottomleft; // (boardsize-1,0)
	struct slot *bottomright; // (boardsize-1, boardsize-1)
	
	int playeramount = getplayeramount();
	
	createboard(boardsize, &topleft, &topright, &bottomleft, &bottomright);
	printf("players: %d, boardsize: %d\n\n", playeramount,boardsize);
	
	getDesiredElement(boardsize, &row,&column);
	
	if(row > boardsize/2)
	{
		if(column > boardsize/2)
			/*If the the required slot is closer to the topright
		corner, the search starts at (boardsize -1, boarSize -1)*/
		currentslot = reachDesiredElement(row,column,bottomright);
		else
		/*If the the required slot is closer to the topright
		corner, the search starts at (boardSize-1, 0)*/
			currentslot = reachDesiredElement(row,column,bottomleft);
	} else 
	{
		/*If the the required slot is closer to the topright
		corner, the search starts at (0, boarSize -1)*/
		if(column > boardsize/2)
		{
			currentslot = reachDesiredElement(row,column, topright);
		}
		/*If the the required slot is closer to the topright
		corner, the search starts at (0, 0)*/
		else currentslot = reachDesiredElement(row,column,topleft);
	}	
	int i,j;
	for(i=0; i<boardsize; i++)
	{
		for(j=0; j<boardsize;j++)
		{
			explored[i][j] = false;
		}
	}

	foundslots = malloc(boardsize * boardsize * sizeof(struct slot ));
	
		i=0;
			
	while (i < playeramount) //max 6 players and respective type
	{	//n = number of players
		printf("\nEnter player name:\n");
		scanf("%s", &player[i].name);
		
		printf("Enter this player's type:\n1.Human 2.Ogre 3.Elf 4.Wizard\n");
		scanf("%d", &player[i].type);
		while (player[i].type < 1 || player[i].type > 4)
		{
			printf("Enter this player's type:\n1.Human 2.Ogre 3.Elf 4.Wizard\n");
			scanf("%d", &player[i].type);
		}	
		i++;
	}

	//COULDN'T MAKE STRUCT FUNCTION IN THE SAME WAY AS SLOTS WAS DONE
	
	for(i=0;i<playeramount;i++)
	{
		if (player[i].type == 1)
		{ 						//human
			strcpy(player[i].class, "Human");
//randomly allocate capabilities while respecting the constraints provided in the line below.
			do
			{
			player[i].luck = (rand() %100 +1);
			player[i].smartness = (rand() %100 +1);
			player[i].strength = (rand() %100 +1);
			player[i].dexterity = (rand() %100 +1);
			player[i].magic = (rand() %100 +1);
			player[i].health = 100;	// +1 makes a minimum and then
			}while((player[i].dexterity + player[i].magic + player[i].smartness + player[i].strength + player[i].luck) < 300);
		}
		else if (player[i].type == 2)
		{ 						//ogre
			strcpy(player[i].class, "Ogre");
			player[i].strength = (rand() %21 +80);
			player[i].dexterity = (rand() %21 +80);
			player[i].health = 100;
			player[i].magic = 0;	
			do
			{
			player[i].smartness = (rand() %20 +1);
			player[i].luck = (rand() %50 +1);
			}while((player[i].luck + player[i].smartness) >= 50);
		}	
		else if (player[i].type == 3) //elf
		{
			strcpy(player[i].class, "Elf");
			player[i].luck = (rand() %41 +60);
			player[i].smartness = (rand() %31 +70);
			player[i].strength = (rand() %51 +1);
			player[i].dexterity = (rand() %99 +1);
			player[i].magic = (rand() %29 +51);//she said 50 < magic instead of
			player[i].health = 100; 		//50 <= magic so set to 51-100
		}
		else if (player[i].type == 4) //wizard
		{
			strcpy(player[i].class, "Wizard");
			player[i].smartness = (rand() %11 +90);
			player[i].dexterity = (rand() %100 +1);
			player[i].strength = (rand() %20+1);
			player[i].luck = (rand() %51 +50);
			player[i].magic = (rand() %21 +80);	
			player[i].health = 100;
		} 
	}	
	
	for(i=0; i<playeramount ;i++)
	{
			//printing all of the stats by struct
		printf("name: %s\n", player[i].name);
		printf("class: %s\n",player[i].class);
		printf("health: %d\n",player[i].health);
		printf("smartness = %d\n",player[i].smartness);
		printf("magic = %d\n",player[i].magic);
		printf("strength = %d\n",player[i].strength);
		printf("dexterity = %d\n",player[i].dexterity);
		printf("luck = %d\n\n",player[i].luck);
	}
	
	for(i=0;i<playeramount;i++) //randomising player location
	{
		player[i].currentrow = (rand() %7);
		player[i].currentcol = (rand() %7);
	}
	
	int leavegame,check;
	for(i=0;i<playeramount;i++)
	{
		check = i;	//needed to check for false moves ie walking off the map
		printf("Player %d turn:\nPlayer positions:\n",i);
		for(j=0;j<playeramount;j++)
		{
		//	currentpositions(j,player[j].currentrow,player[j].currentcol);
		}
		
		int choice;
		instructions(i);
		scanf("%d",choice);
		
		switch(choice)
		{
			case 1: //movement
				playermove(i,&player[i].currentrow, &player[i].currentcol);
				
				if(check == i) //if there's an error, i returns as "i-1"
				{ //ERROR HERE (SUBSCRIPT)
					
				break;
			}

			case 2: {
				int choiceattack;
				printf("Choose your attack type:\n 1. Near attack\n 2. Distant attack \n 3. Magic attack");
				scanf("%d", &choiceattack);
				switch (choiceattack){
					case 1:
						printf("You have chosen the Near attack mode. \n");
						
				}
			}
				
				
				break;
			
			case 3: //quit
				quitting(i,&player[i].health);
				break;
		
			default:
				printf("Invalid choice, try again\n");
				i--;
				break;
		}
	}

	
	
	return 0;
}