// CS 350                                                                      
//Lab 03                                                                       
//Raman Walwyn-Venugopal - Section 01                                         
//Illinois Institute of Technology   

#include <stdio.h>




int main(){
  printf("CS 350 Lab 5 for Raman Walwyn-Venugopal Section 01\n");
  unsigned int x=1; 
  int left;//the left endoint for the bitstring that the user desires
  int right;//the right endpoint for the bitstring that the user desires
  //loop to continue unitl the user enters 0 for a hex value
  while (x!=0){
    printf("\nPlease enter X in hex (0 to stop): ");//prompts user to enter hex value
    scanf("%x", &x);//reads the hex value
    if (x!=0){
      printf("Please enter left and right end points: ");//prompts the user to enter end points
      scanf("%d %d", &left, &right);//reads the endpoints
      if (left>-1 && right <32 && left<=right){
	x=x<<left;//this shifts the hex value bitstring left amount of bits
	x=x>>(31-right+left);//this shifts the hex value the correct amount of right bits once taking the left bitshift into consideration
	printf("X [%d:%d] = %X = %d", left, right, x, x);
      }
      //informing user whether their endpoints are illegal
      if (left<0){
	printf("\n%d is an illegal endpoint", left);
      }
      if (right>31){
	printf("\n%d is an illegal endpoint", right);
      }
    }
  }
}
  
