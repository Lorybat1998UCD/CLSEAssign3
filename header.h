#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//STRUCTS ARE DECLARED HERE
struct players
{
	char name[200];
	char classp[100];
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
//RANSOM NUMBER GENERATOR USED IS DECLARED HERE
int rand(void);


//PLAYER STATS ASSIGNATION FUNCTIONS DECLARED BELOW
//typedef struct players playerstype;
struct human(players player){ //errors here (ASK)
	strcpy(player.class, "Human");
				{
		while((player.dexterity + player.magic + player.smartness + player.strength + player.luck) > 300)
			{
				player.luck = (rand() %100 +1);
				player.smartness = (rand() %100 +1);
				player.strength = (rand() %100 +1);
				player.dexterity = (rand() %100 +1);
				player.magic = (rand() %100 +1);
				player.health = 100;
			// +1 makes a minimum and then
		}
		return player;
}
}
struct elf(players player){
			strcpy(player.class, "Elf");

			player.luck = (rand() %41 +60);
			player.smartness = (rand() %31 +70);
			player.strength = (rand() %51 +1);
			player.dexterity = (rand() %99 +1);
			player.magic = (rand() %29 +51);//she said 50 < magic instead of
			player.health = 100; 		//50 <= magic so set to 51-100
		return player;
	}

struct wizard(players player){
	
		strcpy(player.class, "Wizard");
			player.smartness = (rand() %11 +90);
			player.dexterity = (rand() %100 +1);
			player.strength = (rand() %20+1);
			player.luck = (rand() %51 +50);
			player.magic = (rand() %21 +80);	
			player.health = 100;
		return player;
	 
}

struct ogre(players player){
		strcpy(player.class, "Ogre");
			player.strength = (rand() %21 +80);
			player.dexterity = (rand() %21 +80);
			player.health = 100;
			player.magic = 0;	
			
			while((player.luck + player.smartness) >= 50){
				player.smartness = (rand() %20 +1);
				player.luck = (rand() %50 +1);	
			}
			return player;
	}

int printplayersummary(struct players player, int n){
			
		for(int i=0; i<n; i++){
			//printing all of the stats by struct
			printf("name: %s\n", player.name);
			printf("class: %s\n",player.class);
			printf("health: %d\n",player.health);
			printf("smartness = %d\n",player.smartness);
			printf("magic = %d\n",player.magic);
			printf("strength = %d\n",player.strength);
			printf("dexterity = %d\n",player.dexterity);
			printf("luck = %d\n\n",player.luck);
		}
	}