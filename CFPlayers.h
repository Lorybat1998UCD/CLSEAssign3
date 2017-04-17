#define CROSSFIRE_PLAYERS
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
