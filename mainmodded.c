// ASSIGNMENT - COMP10050 (SOFTWARE ENGINEERING PROJECT)
// GROUP MEMBERS:
// Colm Tang (16760705) & Lorenzo Battilocchi (16341353)

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "header.h"
/* declare your struct for a person here */

int main(void) 
{									 //main function
//declation of the arrays
		struct players player[10];
  	int n;
  	printf("Enter the # of players\n");
  	scanf("%d", &n);
	
	while (n>6 || n<2)
	{							 // in case of too many players
    	printf("Error: player numbers invalid. Choose a number between 6 and 2 palyers and try again.\n");
  		scanf("%d", &n);
	}

	int i=0;
			//n-1 because i starts at 0 so ends at 5
	while (i < n) //max 6 players and respective type
	{	//n = number of players
		printf("Enter player name:\n");
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
// SECTION B: RANDOM ALLOCATION OF PLAYER CAPABILITIES

	for (i=0; i<n; i++){
		switch(player[i].type)
		{
			case 1: player[i].type = struct human(player[i]);
				break; 	//HUMAN

			case 2: player[i].type =struct ogre(player[i]);
				break; //OGRE
			case 3: player[i].type =struct elf(player[i]);
				break;//ELF
			case 4: player[i].type = struct wizard(player[i]);
				break;//WIZARD

/*// *** SECTION B ***
	srand ( time(NULL)); 
	for(i=0;i<n;i++)
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
	*/	for(i=0; i<n ;i++)
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
		printf("Proceeding to slot selection\n");

	struct slots slot[20];
	int num_slots;

	printf("Enter the amount of slots you want to have on the game board: ");//prompt for number of slots for game board.

	scanf("%d", &num_slots);

	while (num_slots < 2 || num_slots > 20 || num_slots < n)
	{
		printf("Please choose a value less than 20 and greater than 1. This value must be greater than the number of players you selected above. Try again.\n");

		scanf("%d", &num_slots);

	}

	printf("You have selected %d slots to be on the board.\n\n", num_slots); 
	int j; //for loop counter
	for (j=0; j<num_slots; j++)
	{		 //for loop to assign the slot types to the various slots (number selected by user)
		int random_R= rand()%3; // random seed for random allocation of slots
			if (random_R==0)
			{
				strcpy(slot[j].slottype, "LEVEL GROUND");
				printf("Slot %d is type \"LEVEL GROUND\"\n", j+1);
			} 		//("LEVEL GROUND");
			else if (random_R == 1)
			{
				strcpy(slot[j].slottype, "CITY");
				//slottype = ("CITY");
				printf("Slot %d is type \"CITY\"\n", j+1);
			}
			else if (random_R == 2)
			{
				strcpy(slot[j].slottype, "HILL");
				//slottype = ("HILL");
				printf("Slot %d is type \"HILL\"\n", j+1);
			}
			else{}
	}
	for(i = 0;i < num_slots; i++)
	{
		slot[i].occupied = 0;	//Need to assign each slot occupied to 0 before filling them
	}
			//This allocates players to random slots
	for(i = 0;i < n;i++)	
	{
		player[i].currentslot= (rand() % num_slots);
	}
	for(i=0;i<n;i++)	//makes sure they dont occupy same spot
	{
		for(j=i+1;j<n;j++)
		{	//i+1 because it starts after i
			if(player[i].currentslot == player[j].currentslot)
			{
				player[i].currentslot = (rand() % num_slots);
				i=-1;	//i=-1 so that when it returns to the
				
			}			//outer for loop, i=0
			else{}
		}
	}
	printf("\n"); 
	for(i = 0;i < n; i++)
	{
		slot[player[i].currentslot].occupied = 1;
		slot[player[i].currentslot].defending = i; //this tells us which player is each occupied slot
		printf("%s is on slot %d(%s)\n", player[i].name, player[i].currentslot +1,slot[player[i].currentslot].slottype);
	}
	//SECTION C
	int move;
	int turnend;

	for(i=0;i<n;i++)
	{	
		turnend=0;
		printf("\nIt is %s's turn\n", player[i].name);
		while(player[i].currentslot == 0 && turnend == 0) //in the case where player is at the first slot 
		{
			if(slot[1].occupied == 1)
			{
				printf("The slot behind is off the board and the slot ahead is occupied\n");
				printf("You may only attack %s ahead of you\n",player[slot[player[i].currentslot +1].defending].name);
				if(player[slot[player[i].currentslot +1].defending].strength <=70)
						{
							player[slot[player[i].currentslot +1].defending].health -= 0.5*(player[slot[player[i].currentslot +1].defending].strength);
						}
						else
						{
							player[i].health -= 0.3*(player[slot[player[i].currentslot +1].defending].strength);
						}
			}
			else
			{			//checks whether the slot is hill, city or level ground type
				printf("The slot behind is off the board and the slot ahead is empty\n");
				printf("You may only move forward\n");
				if(strcmp(slot[player[i].currentslot +1].slottype, "HILL")== 0)
				{
					slot[player[i].currentslot].occupied = 0;
					player[i].currentslot += 1;				//update the occupied slots each movement
					slot[player[i].currentslot].occupied = 1;
					if(player[i].dexterity < 50)
					{
						player[i].strength -=10;
					}
					else if(player[i].dexterity >=60)
					{
						player[i].strength +=10;
					}
				}
				else if(strcmp(slot[player[i].currentslot +1].slottype, "CITY")== 0)
				{	
					slot[player[i].currentslot].occupied = 0;
					player[i].currentslot += 1;
					slot[player[i].currentslot].occupied = 1;
					if(player[i].smartness <= 50)
					{
						player[i].magic -=10;
					}
					else if(player[i].smartness >60)
					{
						player[i].magic +=10;
					}
				}
				else if(strcmp(slot[player[i].currentslot +1].slottype, "LEVEL GROUND")== 0)
				{
					slot[player[i].currentslot].occupied = 0;
					player[i].currentslot += 1;
					slot[player[i].currentslot].occupied = 1;
				}
			}
			turnend=1;
			break;
		}
		while(player[i].currentslot == num_slots-1 && turnend == 0) //in the case where player is in the last slot
		{
			if(slot[player[i].currentslot -1].occupied == 1)
			{
				printf("The slot behind is occupied and the slot ahead is off the board\n");
				printf("You may only attack %s behind you\n",player[slot[player[i].currentslot -1].defending].name);
				if(player[slot[player[i].currentslot -1].defending].strength <=70)	//This is where i first use .defending to figure out which
						{														//player is in the adjacent slots to current player
							player[slot[player[i].currentslot -1].defending].health -= 0.5*(player[slot[player[i].currentslot -1].defending].strength);
						}
						else
						{
							player[i].health -= 0.3*(player[slot[player[i].currentslot -1].defending].strength);
						}							
			}						//I also used slot[...].defending in any case where an adjacent player had to be referenced
			else					//It seemed to be the easiest way to use an adjacent players stats or alter their stats
			{			
				printf("the slot behind is empty and the slot ahead is off the board\n");
				printf("You may only move backwards\n");
				if(strcmp(slot[player[i].currentslot -1].slottype, "HILL")== 0)
				{
					slot[player[i].currentslot].occupied = 0;
					player[i].currentslot -= 1;
					slot[player[i].currentslot].occupied = 1;
					if(player[i].dexterity < 50)
					{
						player[i].strength -=10;
					}
					else if(player[i].dexterity >= 60)
					{
						player[i].strength +=10;
					}
				}
				else if(strcmp(slot[player[i].currentslot -1].slottype, "CITY")== 0)
				{	
					slot[player[i].currentslot].occupied = 0;
					player[i].currentslot -= 1;
					slot[player[i].currentslot].occupied = 1;
					if(player[i].smartness <= 50)
					{
						player[i].magic -=10;
					}
					else if(player[i].smartness >60)
					{
						player[i].magic +=10;
					}
				}
				else if(strcmp(slot[player[i].currentslot -1].slottype, "LEVEL GROUND")== 0)
				{
					slot[player[i].currentslot].occupied = 0;
					player[i].currentslot -= 1;
					slot[player[i].currentslot].occupied = 1;
				}
			}
			turnend=1;
			break;
		}
		while(player[i].currentslot >= 1 && player[i].currentslot <= num_slots-2 && turnend == 0)
		{			//players in all slots bar the last slot and first slot
			if(slot[player[i].currentslot -1].occupied == 1 && slot[player[i].currentslot +1].occupied == 1)
			{
				printf("Both slot ahead of you is occupied by %s and behind you is occupied by %s\n",player[slot[player[i].currentslot +1].defending].name,player[slot[player[i].currentslot -1].defending].name);
				do
				{
					printf("Enter 1 to attack %s ahead you, 2 to attack %s behind you\n",player[slot[player[i].currentslot +1].defending].name,player[slot[player[i].currentslot -1].defending].name);
					scanf("%d",&move);
					if(move == 1)
					{
						if(player[slot[player[i].currentslot +1].defending].strength <=70)
						{
							player[slot[player[i].currentslot +1].defending].health -= 0.5*(player[slot[player[i].currentslot +1].defending].strength);
						}
						else
						{
							player[i].health -= 0.3*(player[slot[player[i].currentslot +1].defending].strength);
						}
					}
					else
					{
						if(player[slot[player[i].currentslot -1].defending].strength <=70)
						{
							player[slot[player[i].currentslot -1].defending].health -= 0.5*(player[slot[player[i].currentslot -1].defending].strength);
						}
						else
						{
							player[i].health -= 0.3*(player[slot[player[i].currentslot -1].defending].strength);
						}
					}
				}while(move < 1 || move > 2);
			}
			else if(slot[player[i].currentslot -1].occupied == 0 && slot[player[i].currentslot +1].occupied == 0)
			{
				printf("Both slots behind you and ahead of you are empty\n");
				do
				{
					printf("Enter 1 to move ahead a slot, 2 to move back a slot\n");
					scanf("%d",&move);
					if(move == 1)
					{
						if(strcmp(slot[player[i].currentslot +1].slottype, "HILL")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot += 1;
							slot[player[i].currentslot].occupied = 1;
							if(player[i].dexterity < 50)
							{
								player[i].strength -=10;
							}
							else if(player[i].dexterity >= 60)
							{
								player[i].strength +=10;
							}
						}
						else if(strcmp(slot[player[i].currentslot +1].slottype, "CITY")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot += 1;
							slot[player[i].currentslot].occupied = 1;
							if(player[i].smartness <= 50)
							{
								player[i].magic -=10;
							}
							else if(player[i].smartness >60)
							{
								player[i].magic +=10;
							}
						}
						else if(strcmp(slot[player[i].currentslot +1].slottype, "LEVEL GROUND")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot += 1;
							slot[player[i].currentslot].occupied = 1;
						}
					}
					else
					{
						if(strcmp(slot[player[i].currentslot -1].slottype, "HILL")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot -= 1;
							slot[player[i].currentslot].occupied = 1;
							if(player[i].dexterity < 50)
							{
								player[i].strength -=10;
							}
							else if(player[i].dexterity >= 60)
							{
								player[i].strength +=10;
							}
						}
						else if(strcmp(slot[player[i].currentslot -1].slottype, "CITY")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot -= 1;
							slot[player[i].currentslot].occupied = 1;
							if(player[i].smartness <= 50)
							{
								player[i].magic -=10;
							}
							else if(player[i].smartness >60)
							{
								player[i].magic +=10;
							}
						}
						else if(strcmp(slot[player[i].currentslot -1].slottype, "LEVEL GROUND")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot -= 1;
							slot[player[i].currentslot].occupied = 1;
						}
					}
				}while(move < 1 || move > 2); //making sure the move is an available option
			}
			else if(slot[player[i].currentslot -1].occupied == 0 && slot[player[i].currentslot +1].occupied == 1)
			{
				printf("The slot behind is empty and the slot ahead is occupied by %s\n",player[slot[player[i].currentslot +1].defending].name);
				do
				{
					printf("Enter 1 to attack %s ahead of you, 2 to move backwards\n",player[slot[player[i].currentslot +1].defending].name);
					scanf("%d",&move);
					if(move == 1)
					{
						if(player[slot[player[i].currentslot +1].defending].strength <=70)
						{
							player[slot[player[i].currentslot +1].defending].health -= 0.5*(player[slot[player[i].currentslot +1].defending].strength);
						}
						else
						{
							player[i].health -= 0.3*(player[slot[player[i].currentslot +1].defending].strength);
						}
					}
					else
					{
						if(strcmp(slot[player[i].currentslot -1].slottype, "HILL")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot -= 1;
							slot[player[i].currentslot].occupied = 1;
							if(player[i].dexterity < 50)
							{
								player[i].strength -=10;
							}
							else if(player[i].dexterity >= 60)
							{
								player[i].strength +=10;
							}
						}
						else if(strcmp(slot[player[i].currentslot -1].slottype, "CITY")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot -= 1;
							slot[player[i].currentslot].occupied = 1;
							if(player[i].smartness <= 50)
							{
								player[i].magic -=10;
							}
							else if(player[i].smartness >60)
							{
								player[i].magic +=10;
							}
						}
						else if(strcmp(slot[player[i].currentslot -1].slottype, "LEVEL GROUND")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot -= 1;
							slot[player[i].currentslot].occupied = 1;
						}
					}
				}while(move < 1 || move > 2);
			}
			else if(slot[player[i].currentslot -1].occupied == 1 && slot[player[i].currentslot +1].occupied == 0)
			{
				printf("The slot behind is occupied by %s and the slot ahead is empty\n",player[slot[player[i].currentslot -1].defending].name);
				do
				{
					printf("Enter 1 to attack %s behind you, 2 to move forwards\n",player[slot[player[i].currentslot -1].defending].name);
					scanf("%d",&move);
					if(move == 1)
					{
						if(player[slot[player[i].currentslot -1].defending].strength <=70)
						{
							player[slot[player[i].currentslot -1].defending].health -= 0.5*(player[slot[player[i].currentslot -1].defending].strength);
						}
						else
						{
							player[i].health -= 0.3*(player[slot[player[i].currentslot -1].defending].strength);
						}
					}
					else
					{
						if(strcmp(slot[player[i].currentslot +1].slottype, "HILL")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot += 1;
							slot[player[i].currentslot].occupied = 1;
							if(player[i].dexterity < 50)
							{
								player[i].strength -=10;
							}
							else if(player[i].dexterity >= 60)
							{
								player[i].strength +=10;
							}
						}
						else if(strcmp(slot[player[i].currentslot +1].slottype, "CITY")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot += 1;
							slot[player[i].currentslot].occupied = 1;
							if(player[i].smartness <= 50)
							{
								player[i].magic -=10;
							}
							else if(player[i].smartness >60)
							{
								player[i].magic +=10;
							}
						}
						else if(strcmp(slot[player[i].currentslot +1].slottype, "LEVEL GROUND")== 0)
						{
							slot[player[i].currentslot].occupied = 0;
							player[i].currentslot += 1;
							slot[player[i].currentslot].occupied = 1;
						}
					}
				}while(move < 1 || move > 2);
			}
			turnend= 1;
			break;
		}
	}

	printf("Updated stats and positions\n");
	for(i=0;i<n;i++)
	{
		printf("\nplayer %d\n",i+1);
		printf("name: %s\n", player[i].name);
		printf("class: %s\n",player[i].class);
		printf("health: %d\n",player[i].health);
		printf("smartness = %d\n",player[i].smartness);
		printf("magic = %d\n",player[i].magic);
		printf("strength = %d\n",player[i].strength);
		printf("dexterity = %d\n",player[i].dexterity);
		printf("luck = %d\n",player[i].luck);
	}
return 0;
}
}
}