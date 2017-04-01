#ifndef PLAYERS_H
#define PLAYERS_H
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

#endif


//randomly allocate capabilities while respecting the constraints provided in the line below.
int rand(void);
	// HUMAN

	struct players human(struct players player){
		strcpy(player.class, "Human");
			//rand(time(NULL)); 
			player.luck = (rand() %100 +1);
			player.smartness = (rand() %100 +1);
			player.strength = (rand() %100 +1);
			player.dexterity = (rand() %100 +1);
			player.magic = (rand() %100 +1);
			player.health = 100;
		// +1 makes a minimum and then
		
		while((player.dexterity + player.magic + player.smartness + player.strength + player.luck) < 300);
		
		return player;
	}
	struct players ogre(struct players player){
		//OGRE
		strcpy(player.class, "Ogre");
			//rand(time(NULL)); 
			player.strength = (rand() %21 +80);
			player.dexterity = (rand() %21 +80);
			player.health = 100;
			player.magic = 0;	
			player.smartness = (rand() %20 +1);
			player.luck = (rand() %50 +1);
				while((player.luck + player.smartness) >= 50);
		return player;
		}
	struct players elf(struct players player){
		//ELF
		strcpy(player.class, "Elf");
			//rand(time(NULL)); 
			player.luck = (rand() %41 +60);
			player.smartness = (rand() %31 +70);
			player.strength = (rand() %51 +1);
			player.dexterity = (rand() %99 +1);
			player.magic = (rand() %29 +51);//she said 50 < magic instead of
			player.health = 100; 		//50 <= magic so set to 51-100
		return player;
		}
	struct players wizard(struct players player)	
	//WIZARD
		{
		strcpy(player.class, "Wizard");
			//rand(time(NULL)); 
			player.smartness = (rand() %11 +90);
			player.dexterity = (rand() %100 +1);
			player.strength = (rand() %20+1);
			player.luck = (rand() %51 +50);
			player.magic = (rand() %21 +80);	
			player.health = 100;
		return player;
		} 