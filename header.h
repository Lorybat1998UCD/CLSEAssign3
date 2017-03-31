#ifndef PLAYERS_H
#define PLAYERS_H

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