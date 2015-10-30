// CS 350
//Lab 03
//Raman Walwyn-Venugopal - Section 01
//Illinois Institute of Technology

#include <stdio.h>
#include <math.h>

//prototypes

int  find_blank(char  bitstring[], int empty, int bool, int LEN);
int  bitflip(char bitstring[], int empty, int position);
int  check_val(char bitstring[], int empty,int checkval,  int bool);
int convert_deci(char bitstring[], int empty);
void print_neg(char bitstring[], int empty, int position);
int main() {

  printf("CS 350 Lab 3 for Raman Walwyn-Venugopal Section 01");
  int LEN=100;//the maximum length for the array of charcters is 100
  char bitstring[LEN];//creates an array of 100 Length
 while (bitstring[0]!='q'){
  printf("\nPlease enter your bitstring or (q) to quit\n");
  scanf("%s" ,bitstring);
  int position=0;
  int power=0;
  int empty=0;
  int bool=0;
  int decimal=0;
  int checkval=0;
  empty = find_blank( bitstring, empty, bool, LEN);//calls funtion to find the first empty space
  bool=0;
  bool = check_val(bitstring, empty, checkval, bool);//checks to see if all the values are '1's and 0's'\


  //the if statements below determine if it is a negative or positive number for 2's copmlement
  if (bitstring[0]=='0' && bool==0)//positive
    {    
      decimal = convert_deci(bitstring, empty);
      printf("\nThe conversion to decimal is %d", decimal);
      printf ("\nThe negative reverse is \n");
      print_neg(bitstring, empty, position);
    }
  else if (bitstring[0]=='1' && bool==0){//negative
    decimal  = bitflip(bitstring, empty, position);
    printf("\nThe conversion to decimal is %d", decimal);
    printf ("\nThe negative reverse is \n");
    int i;
    //note the bitstring is already flipped so thats why the function was not used. 
    for (i=0; i<empty; i++)
      {
	printf("%c", bitstring[i]);
      }
  }
}
}


//This function below iterates through the array until it finds an empty space that was not assigned a value, it then returns that position
int find_blank(char bitstring[], int empty, int bool, int LEN)
{    
    while (empty<LEN && bool==0)
      {
	if (bitstring[empty]=='\0')
	  {
	    bool=1;
	  }
	empty++;
      }
    return empty-1;
}


// This is a boolean method to determine whether all of the values are 1's and 0's, the first non binary value it sees, will stop the iteration and inform the user that it is not a appropiate option. It only iterates towards the empty space. 
int check_val(char bitstring[], int empty, int checkval, int bool){
  while (bool !=1 && checkval < empty)
  {
  
    if (bitstring[checkval]=='0'|| bitstring[checkval]=='1')
      {
	checkval++;
      }
    else 
      {
	//since q is quit, it checks to see if that is what the user entered, so therefroe it won't display the error message unecessarily
	if (bitstring[0]!='q')
	  {
	    printf("\nThe char %c is not accepted\n", bitstring[checkval]);//errror message
	  }
	bool=1;
      }
    checkval++;
  }
  return bool;
}

//This function is the bitflip for 2's complement, so it first starts from the right side of the array (before the empty position) and searches for the one in reverse. When it finds that 1, it marks the position and then decides to flip all teh bits before that position. It also calls the convert to decimal function one time. 
int  bitflip(char bitstring[], int empty, int position){
  int bool=0;
  int counter=empty-1;
  while (counter>-1 && bool==0){
    if (bitstring[counter]=='1')
      {
	position = counter;
	bool=1;
      }
    counter--;
  }
  int i;
  for ( i=0; i< position; i++){
    if(bitstring[i]=='1')
      {
	bitstring[i]='0';
      }
    else{
      bitstring[i]='1';
    }
  }
 
 int deci = convert_deci(bitstring, empty);
 return deci*-1;
}


//This function turns the binary number into decimal form. This is done by iterating from the right side of the array and multiplying the values by 2 to their respective power. 
int convert_deci(char bitstring[], int empty){
  int i;
  int decimal = 0;
  int power = 0;
  for( i=empty-1; i >= 0 ; i--)
    {
      decimal = decimal + (bitstring[i] - 48)* pow(2, power++); 
    }
  return decimal;
}


//This function below just prints out the negative 2's complement of the bitstring
void print_neg(char bitstring[], int empty, int position){
  int bool=0;
  int counter=empty-1;
  while (counter>-1 && bool==0){
    if (bitstring[counter]=='1')
      {
        position = counter;
        bool=1;
      }
    counter--;
  }
  int i;
  for ( i=0; i< position; i++){
    if(bitstring[i]=='1')
      {
        bitstring[i]='0';
      }
    else{
      bitstring[i]='1';
    }
  }

  for ( i=0; i<empty; i++)
    {
      printf("%c", bitstring[i]);
    }
}


