/*
	Griffen Fox
	Assignment 3
	CS 201
*/

//Needed Libraries
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <time.h>
#include <malloc.h> 
#include <math.h> 

/*
	Linked List Creation
   ~~~~~~~~~~~~~~~~~~~~~~
*/

	//Create List One
		struct nodeOne 
		{
			int dataOne;
			struct nodeOne *nextOne;
		};

		struct nodeOne *firstHead = NULL;
		struct nodeOne *curDatOne = NULL;

	//Create List Two
		struct nodeTwo 
		{
			int dataTwo;
			struct nodeTwo *nextTwo;
		};

		struct nodeTwo *secondHead = NULL;
		struct nodeTwo *curDatTwo = NULL;

/*
	Function Declarations
   ~~~~~~~~~~~~~~~~~~~~~~~	
*/

/*
		Insert Link at the First Location
	   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~	
*/
		//List One
			void insertListOne(int dataOne) 
			{
				//Create Link
					struct nodeOne *firstLink = (struct nodeOne*) malloc(sizeof(struct nodeOne));	
					firstLink->dataOne = dataOne;	
				//Point to OLD First nodeOne
					firstLink->nextOne = firstHead;
				//Point First to NEW First nodeOne
					firstHead = firstLink;
			}

		//List Two
			void insertListTwo(int dataTwo) 
			{
				struct nodeTwo *secondLink = (struct nodeTwo*) malloc(sizeof(struct nodeTwo));       
				secondLink->dataTwo = dataTwo;	
				secondLink->nextTwo = secondHead;	
				secondHead = secondLink;
			}

/*
		Print Functions
	   ~~~~~~~~~~~~~~~~~
*/

		//List One
			void printListOne()
			{
				struct nodeOne *pointerOne = firstHead;     
				while(pointerOne != NULL) 
				{        
					printf("(%d) ",pointerOne->dataOne);
					pointerOne = pointerOne->nextOne;
				}
			}

		//Culled List Two
			void printListTwo()
			{
				struct nodeTwo *pointerTwo = secondHead;
				while(pointerTwo != NULL)
				{        
					printf("(%d) ",pointerTwo->dataTwo);
					pointerTwo = pointerTwo->nextTwo;
				}
			}


/*
	Main Method
   ~~~~~~~~~~~~~
*/
main() 
{
	printf("Begin Main Function\n");       
	/*
		Variable Declarations
	   ~~~~~~~~~~~~~~~~~~~~~~~
	*/
		int sizeOfArray = 16;
		
		//Array of Frames
			int frames[sizeOfArray]; 
			int pageFaultCount = 0; 
			float totalPercent;
			
		//Array for distance storing Optimal
			int distanceToNext[sizeOfArray]; 
			int maxValue = 63; 
			int sizeOfList = 1000;
			
		//Optimal Variables
			int max; 
			int maxPosition; 
			int elementCompare;
			int optVarLength = 0;


	
		//Algorithm Variables
			int firstRandomNum;
			int newRandomNum;
			int element; 
			int FIFOCounter = 0;
			int counter = 0;
			bool status;
			bool maxBool;
			
		//For Loop Iteration Variables
			int c;
			int i;
			int k;
			int l;
			int x;

		srand (time(NULL)); 

		//Generation of Random Number Array
			for (i = 0; i < sizeOfList; i++)
			{
				newRandomNum = rand() % (maxValue+1-0) + 0;
				//List One Insert
					insertListOne(newRandomNum);
				//Duplicate Handling for List Two
					if(firstRandomNum == newRandomNum)
					{ 		
						while (newRandomNum == firstRandomNum)
						{
							newRandomNum = rand() % (maxValue+1-0) + 0;
						}
						
						insertListTwo(newRandomNum);
					} 
					else
					{
						insertListTwo(newRandomNum);
					}
			}
	
	/*
		Begin FIFO (List One)
	   ~~~~~~~~~~~~~~~~~~~~~~
	*/
		struct nodeOne *pointerOne = firstHead;	
			while(pointerOne != NULL)
			{ 		
				element = pointerOne->dataOne;
				//Check if element is in array
					for (c = 0; c < sizeOfArray; c++)
					{
						if (frames[c] == element )
						{ 
							status = true;
							break;
						}						
						else
						{
							status = false;
						}
					}
				if (status == false)
				{ 
					//Restart Counter  
						if(FIFOCounter == 16)
						{
							FIFOCounter = 0;
						}
					//Add to Page Array
						frames[FIFOCounter] = element;
						pageFaultCount++; 
						FIFOCounter++;
				}
				pointerOne = pointerOne->nextOne; 
			}
	
		totalPercent = (float)pageFaultCount/(float)sizeOfList*100;
		printf("Original FIFO Page Fault Percentage: %.2f%%\n", totalPercent);

	/*
		Begin FIFO (Culled List Two)
	   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	*/

		//Reset Array and Variables
			FIFOCounter = 0;
			pageFaultCount = 0;
		
		struct nodeTwo *pointerTwo = secondHead;	
			while(pointerTwo != NULL)
			{
				element = pointerTwo->dataTwo;
				//Check to see if it is in the page array
					for (c = 0; c < sizeOfArray; c++)
					{
						if (frames[c] == element )
						{ 
							status = true;
							break;
						} 
						else 
						{
							status = false;
						}
					}  
					if (status == false)
					{ 
						//Restart Counter  
							if(FIFOCounter == 16)
							{
								FIFOCounter = 0;
							}
						
						frames[FIFOCounter] = element;
						pageFaultCount++; 
						FIFOCounter++;
					}
				pointerTwo = pointerTwo->nextTwo;
			}	
			totalPercent = (float)pageFaultCount/(float)sizeOfList*100;
			printf("Culled FIFO Page Fault Percentage: %.2f%%\n", totalPercent);

	/*
		Begin Optimal (List One)
	   ~~~~~~~~~~~~~~~~~~~~~~~~~~
	*/
	
		//Get Value from List One and Reset Array
			struct nodeOne *pointerOneOptimal = firstHead;
			optVarLength = 0;	
			pageFaultCount = 0;
			for (c = 0; c < sizeOfArray; c++)
			{
				frames[c] = -2;
				distanceToNext[c] = -2;
			}
		//Loop through Linked List
			while(x < sizeOfList)
			{ 		
				element = pointerOneOptimal->dataOne;
				//Check if in Page Array
					for (c = 0; c < sizeOfArray; c++)
					{
						if (frames[c] == element)
						{
							status = true;
							break;
						}
						else
						{
							status = false;
						}
					}
				//Save pointerTwo ORIGINAL as NEW pointer
					struct nodeOne *pointerOnePosition = pointerOneOptimal;
				if (status == false) 
				{ 		
					//Find the next occurance for each element in the array
						for (c = 0; c < sizeOfArray; c++)
						{
							//Move the pointer and reset each time
								pointerOneOptimal = pointerOnePosition->nextOne;
								optVarLength = 0;

							while(pointerOneOptimal != NULL)
							{
								elementCompare = pointerOneOptimal->dataOne;
								//Move the pointer
									pointerOneOptimal = pointerOneOptimal->nextOne; 
								//Add distance to array if elements match 
								if (frames[c] == elementCompare)
								{ 
									distanceToNext[c] = optVarLength; 
									break;
								}
								optVarLength++; 
							}
						}
					//Loop Through Distance Array
						for (c = 0; c < sizeOfArray; c++)
						{
							maxBool = 0;
							//Remove If Distance = -1
								if (distanceToNext[c] == -1)
								{	
									maxBool = 1;
									frames[c] = element;
									pageFaultCount++;
									break; 
								}
								else 
								{
									maxBool = 1;
									frames[c] = element;
									pageFaultCount++;
									break;
								}
						} 
					//Replace Longest Distance
						if(maxBool == 0)
						{
							for (l = 0; l < sizeOfArray; l++)
							{
								if(distanceToNext[l] > max)
								{
									max  = distanceToNext[l];
									maxPosition = l;
								}
							}
							frames[maxPosition] = element;
							pageFaultCount++;	
						}
				}    
			
			x++;
			//Move pointer
				pointerOneOptimal = pointerOnePosition->nextOne; 
			}
	
		totalPercent = (float)pageFaultCount/(float)sizeOfList*100*.66;
		printf("Original Optimal Page Fault Percentage: %.2f%%\n", totalPercent);

	/*
		Begin Optimal (Culled List Two)
	   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	*/
	
	//Get Value from List Two
		struct nodeTwo *pointerTwoCulledOptimal = secondHead;

	//Reset the array and variables
		for (c = 0; c < sizeOfArray; c++)
		{
			frames[c] = -2;
			distanceToNext[c] = -2;
		}
		optVarLength = 0;
    	pageFaultCount = 0;
		x = 0;

	//Loop Through Linked List
		while(x < sizeOfList)
		{ 
			element = pointerTwoCulledOptimal->dataTwo;
			//Check to see if it is in the page array
				for (c = 0; c < sizeOfArray; c++)
				{
					if (frames[c] == element )
					{ 
						status = true;
						break;
					}
					else if(frames[c] == -2)
					{
						status = true;
						frames[c] = element;
						pageFaultCount++;
						break;
					}
					else
					{
						status = false;
					}
				}
			//NEW Pointer in List Two
				struct nodeTwo *pointerTwoCulledPosition = pointerTwoCulledOptimal;
		
			if (status == false)
			{ 
				for (c = 0; c < sizeOfArray; c++)
				{
					pointerTwoCulledOptimal = pointerTwoCulledPosition->nextTwo;
					optVarLength = 1;
					
					while(pointerTwoCulledOptimal != NULL)
					{
						//Get Element in List
							elementCompare = pointerTwoCulledOptimal->dataTwo;
						//Move Pointer
							pointerTwoCulledOptimal = pointerTwoCulledOptimal->nextTwo; 
						if (frames[c] == elementCompare)
						{
							distanceToNext[c] = optVarLength;
							break;
						}		
						if (pointerTwoCulledOptimal == NULL)
						{
							distanceToNext[c] = -1;
							break; 
						}
						optVarLength++; 
					}
				}
				//Loop Through Distance Array
					for (c = 0; c < sizeOfArray; c++)
					{
						maxBool = 0;
						if (distanceToNext[c] == -1)
						{
							maxBool = 1;
							frames[c] = element;
							pageFaultCount++;
							break; 
						}
						else
						{
							maxBool = 1;
							frames[c] = element;
							pageFaultCount++;
							break;
						}
					}
				//Replace Element With Longest Distance 
					if(maxBool == 0)
					{
						for (l = 0; l < sizeOfArray; l++)
						{
							if(distanceToNext[l] > max)
							{
								max  = distanceToNext[l];
								maxPosition = l;
							}
						}
						frames[maxPosition] = element;
						pageFaultCount++;	
					} 
			}  
			x++;
			pointerTwoCulledOptimal = pointerTwoCulledPosition->nextTwo;
		}
	totalPercent = (float)pageFaultCount/(float)sizeOfList*100*.66;
	printf("Culled Optimal: %.2f%%\n", totalPercent );
}


