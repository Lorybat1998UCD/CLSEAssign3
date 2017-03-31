
#ifndef CROSSFIREOPERATIONS_H_
#define CROSSFIREOPERATIONS_H_
#endif /* CROSSFIREOPERATIONS_H_ */


/*
 * Definition of boolean types
 * This avoids using <stdbool.h>
 */
//typedef int bool;
// enum { false, true };

/*
 * The slot template
 */
struct slot{
	//row number
	int row;
	//column number
	int column;

	// adjacent left slot
	struct slot *left;
	// adjacent right slot
	struct slot *right;
	// adjacent up slot
	struct slot *up;
	// adjacent down slot
	struct slot *down;
}slot;


void createBoard(int boardSize, struct slot **upLeft, struct slot **upRight, struct slot **downLeft, struct slot **downRight);
