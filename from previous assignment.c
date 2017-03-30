
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* declare your struct for a person here */
struct players
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
	int currentslot;
	int turn;
};

struct slots
{
	char slottype[10];
	int occupied;
	int defending;	//i made this specifically to track which player was in each occupied slot
};

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