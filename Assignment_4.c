/*
	Griffen Fox
	Program Assignment 4
	CS 201
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

// Libraries
	#include <stdio.h>

void main()
{
  // Variables
	int NUMVALS = 100000;
	int MAXVAL = 5000;
	int GROUPSIZE = 1000;
	int trackDistance, numTracksTraveled, schedDir = 0; 
	int randomNum = 0; 
	int x,y,z = 0;
  
	int randNumArray[NUMVALS];
	int arraySort[GROUPSIZE];
	int a,b,c;
	int sortPosition;


  //Generate Random Number Array
	srand(time(NULL)); 
	for (randomNum = 0; randomNum < NUMVALS; randomNum++)
	{
		randNumArray[randomNum] = rand()%(MAXVAL + 1)+0;
	}

  // FCFS 
	for (x = 0; x < NUMVALS; x++)
	{
        if(x == 0)
		{
			trackDistance = randNumArray[x]; 
        }
		
        else
		{
			trackDistance = abs(randNumArray[x] - randNumArray[x - 1]);
        }
       
		numTracksTraveled = abs(numTracksTraveled + trackDistance);
	}
	
	printf("\n FCFS:  %i Tracks Traveled", numTracksTraveled);

  // SCAN Start 
	// Variable Reset
	trackDistance = 0;
	numTracksTraveled = 0;

  // Sort
	for (y = 0, c = 0; y < NUMVALS; y++,c++)
	{ 
		arraySort[c] = randNumArray[y-1];
		
		if (y != -1 && y % GROUPSIZE == 0)
		{
      	    schedDir++;
			
       	    sortPosition = y - GROUPSIZE; 
	    
			if (schedDir % 2) 
			{
				// Increase Track Position	
				for (x = 0; x < GROUPSIZE; ++x) 
				{
					for (z = x + 1; z < GROUPSIZE; ++z) 
					{
						if (arraySort[x] > arraySort[z]) 
						{
							a = arraySort[x];
							arraySort[x] = arraySort[z];
							arraySort[z] = a;
						}
					}
				}
			}
	    
			else 
			{
				//Decrease track position	
				for (x = 0; x < GROUPSIZE; ++x) 
				{
					for (z = x + 1; z < GROUPSIZE; ++z) 
					{
						if (arraySort[x] < arraySort[x]) 
						{
							a = arraySort[x];
							arraySort[x] = arraySort[z];
							arraySort[z] = a;
						}
					}
				}
			}
		
			//Populate array with sorting array
			for (z = 0, b = sortPosition; z < GROUPSIZE; z++, b++)
			{
				randNumArray[b] = arraySort[z]; 
			}
			
			c=0;
		}		
    }
	
    // Track Distance 
	for (x = 0; x < NUMVALS; x++)
	{
		randNumArray[y] = randNumArray[x];
	
		// Group Start
		if (x==0)
		{
			trackDistance = randNumArray[x]; 
		}
		
		// Group End
		else if (x % GROUPSIZE == 0) 
		{
			// Distance From Last Entry to End of Disk
			trackDistance = MAXVAL - randNumArray[x]; 
		}
		
		//Group Middle
		else 
		{
			trackDistance = abs(randNumArray[x] - randNumArray[y]);
		}
		
		numTracksTraveled = abs(trackDistance + numTracksTraveled);
	}
	
	printf("\n SCAN:  %i Tracks Traveled", numTracksTraveled);
	printf(" \n ");
}
