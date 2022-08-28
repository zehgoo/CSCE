#include <stdio.h>
#include <stdlib.h>

int main(void) {

  int *ptr;
  int *intPtr;

  intPtr = (int *) malloc(sizeof(int)*2);
  if (intPtr == NULL){
    fprintf(stderr,"Error faied to allocate memory\n");
    exit(0);
  }  

  printf("Enter first integer: ");
  scanf("%d",&intPtr[0]);

  printf("Enter second integer: ");
  scanf("%d",&intPtr[1]);

  printf("Original Values: 1st = %d  2nd = %d\n", intPtr[0], intPtr[1]);

  intPtr[0] = intPtr[0] ^ intPtr[1];
  intPtr[1] = intPtr[0] ^ intPtr[1];
  intPtr[0] = intPtr[0] ^ intPtr[1];

  printf("Swapped Values: 1st = %d  2nd = %d\n", intPtr[0], intPtr[1]);

  free(intPtr);   

  return 0;
}