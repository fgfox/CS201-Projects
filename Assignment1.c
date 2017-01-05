/* 	CS201: Assignment 1
	Random Letters
	Griffen Fox
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char *argv[])
{
	int count , randNum, i;
	int min = 65;
	int max = 90;

	if(argc != 1)
	{
		count = atoi(argv[1]);
		if(count > 32)
		{
			printf("Invalid count. Maximum count is 32\n");
		}	
  
	else
	{
		srand (time(NULL));
		for(i=0; i<count; i++)
		{
			randNum =(int) ( rand() % (max-min) ) + min;
			printf("%c\n", randNum);
			randNum = 0;
		}
	}
	}
	
	else
	{	
	printf("Invalid command line arguement. You must enter the count\n");
	}
	
	return 0;
}