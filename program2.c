/*

*/

//include necessary libraries 
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <malloc.h>

//declare global array so it can be used by both threads
int* array = 0;

//prepare for the linked list in thread two
typedef struct a{
  struct a* prev;
  struct a* next;
  int array;
}item;

//thread1 receives count as argument
void *myThreadOne(void* arg){
  printf("Thread One Process\n");
  //declare other variables used for generating random numbers
  int i;
  int randomNum;
  int min=0;
  int max=33;
  //count is the argument passed in
  int* count = (int*)arg;
  //generate the random numbers and put them in the global array for thread two to process
  const size_t num_items = count;
  array = malloc(sizeof(int) * num_items);
  for(i=0; i<count; i++) {
     randomNum=(rand() % (max-min)) + min;
     array[i] = randomNum;
     /* test that numbers are inserted into array
	printf("%d\n", array[i]); */
  }
  printf("Array has been filled...\n");
  return NULL;
}//end thread one

//thread2 reads array, inserts values into linked list, then prints them
void *myThreadTwo(void* arg) {
  printf("Thread Two Process\n");
  item* head;
  item* tail;
  item* temp;
  int* count = (int*)arg;
  int i = 0;
  head = (item*)malloc(sizeof(item));
  head -> prev = NULL;
  head -> next = NULL;
  tail = head;
  //count is the size of the array, so it can be used again in thread two in the creation of the linked list
  for(i=0; i<count; i++){
    temp = tail;
    tail -> next = (item*)malloc(sizeof(item));
    tail = tail -> next;
    tail -> next = NULL;
    tail -> array = array[i];
    tail -> prev = temp;
 }
  printf("Linked list of numbers has been created:\n");
  //go through and print the linked list
  for(temp = head -> next; temp != NULL; temp = temp -> next)
    printf("%d\n", temp -> array);
  return 0;
}//end thread two

//takes argument count and argument vector
int main( int argc, char *argv[] ) {
 
  //initialize count variable for main
  int count;

  /*If argc is true (count has been entered) converts the string to an integer with atoi function*/
  /*Only works if argc is not false: (argc != 1). Could not get program working by saying argc is true: (argc = 0)*/
  if((argc != 1)) {
       
    //set count equal to the inputted count
    count = atoi(argv[1]);
       
    //display error message if count is too high, exit the program
    if(count > 32) {  
      printf("Count is too high! Please enter a number between 1 and 32.\n");
      exit(0);
    }//end if

    //display message letting user know count is zero, exit the program
    if(count == 0){
      printf("Count is zero! Please enter a number between 1 and 32.\n");
      exit(0);
    }//end if
       
    //display message letting user know they entered a negative count, exit the program
    if(count < 0) {
      printf("You entered a negative count! Please enter a number between 1 and 32.\n");
      exit(0);
    }//end if

    //if everything is good...
    else {
             
      //run srand once to initialize the pseudo-random number generator (rand function)
      srand (time(NULL));
             
      //generate random numbers in thread one
      pthread_t tid;
      printf("Before Thread One\n");
      pthread_create(&tid, NULL, myThreadOne, (void*)(count));
      pthread_join(tid, NULL);
      printf("After Thread One\n");

      //print them in thread two
      printf("Before Thread Two\n");
      pthread_create(&tid, NULL, myThreadTwo, (void*)(count));
	 pthread_join(tid, NULL);
      printf("After Thread Two\n");
      exit(0);

    }//end else
  }//end if
 
  //display error message if no count present
  else {
    printf("Count has not been entered! Please try again.\n");
  }//end else
}//end main

