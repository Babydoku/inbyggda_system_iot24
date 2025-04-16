#include <stdio.h>
#include "printer.h"

namespace ovning_2 {


int func(void) {
   return 42;
}

/*Skapa en komponent med funktioner för följande:
void printNumbers (int start, int stop) 
void takeTimeAndPrintEverySecond (int time)
int multiply (int a, int b)*/

void printNumbers(int start, int stop) {
   for(int i = start; i < stop; i++) {
      printf("%d", i);
   }
   return;   
}

void takeTimeAndPrintEverySecond(int time) {
   for(int i = 0; i < time; i++) {
      if(i % 2 == 0) {
       printf("%d", i);
      }
   }
   return;
}

int multiply(int a, int b) {
   return a * b;
}


} // namespace ovning_2

int main(){
   ovning_2::printNumbers(1, 10);
      ovning_2::takeTimeAndPrintEverySecond(10);
         printf("%d", ovning_2::multiply(2, 3));
   
   return 0;
}