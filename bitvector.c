#include <math.h>
#include <stdio.h>
#include <time.h>

//[My,Dog,has,Fleas,Cat,Hamster,Hiccups]
int size = 7;
unsigned int MyDogHasFleas = 0b1111000;
unsigned int MyCatHasFleas = 0b1011100; 
unsigned int MyNotDogHasNotFleas = 0b1010000; //-1 becomes 0
unsigned int MyHamsterHasHiccups = 0b1010011;

/*
Function BitCount() finds https://en.wikipedia.org/wiki/Hamming_weight for an unsigned int
From: https://web.archive.org/web/20151229003112/http://blogs.msdn.com/b/jeuge/archive/2005/06/08/hakmem-bit-count.aspx
Explained: https://tekpool.wordpress.com/category/bit-count/
*/
unsigned int magnitude(unsigned int u)
    {
         unsigned int uCount;

         uCount = u - ((u >> 1) & 033333333333) - ((u >> 2) & 011111111111);
         return ((uCount + (uCount >> 3)) & 030707070707) % 63;
    }

void printBinary (unsigned int number){
  for (int i = 0; i < 32; ++i) {
  if (number >> i & 0x1) putchar('1');
  else putchar('0');
  }
  putchar('\n');
}

unsigned int dotproduct(unsigned int a, unsigned int b){
  unsigned int product ;
  unsigned int Mask = (a|b);
  //printBinary(a);
  //printBinary(b);
  product = ~(a^b); //XNOR! 
  product = (product & Mask);
  //printBinary(product);
  return magnitude(product); //magnitude is the sum of all the 1s 
}

unsigned int active_dimensions(unsigned int a, unsigned int b){ 
  unsigned int actives = (a|b);
  return magnitude(actives); //magnitude is the sum of all the 1s 
}


float cosine_simularity(unsigned int a, unsigned int b){
   unsigned int ma,mb,dp,sz;
   float mt,result;
   ma = magnitude(a);
   mb = magnitude(b);
   mt = (float) ma * (float) mb;  
   
   //average # of active dimensions seems to return more expected results than just counting combined actives
   sz = (ma+mb)/2; 
   //sz = active_dimensions(a,b); 
   if(mt!=0){
     dp = dotproduct(a,b); 
     result = sz * (float) dp/ mt;
     return result;
   } else { 
     return 0;
   }
}

int main(){
  float csin; 
  int sims = 10000000;
  printf("\nTesting Bit Vectors:\n\n");
  
  struct timespec tstart={0,0}, tend={0,0};
      csin = cosine_simularity(MyDogHasFleas,MyCatHasFleas);
      printf("MyDogHasFleas*MyCatHasFleas cosine=%f\n",csin);

      csin = cosine_simularity(MyDogHasFleas,MyHamsterHasHiccups);
      printf("MyDogHasFleas*MyHamsterHasHiccups cosine=%f\n",csin);
      printf("We lose the ability to have negative dimensions.. but that's ok..\n'");
      csin = cosine_simularity(MyDogHasFleas,MyNotDogHasNotFleas);
      printf("MyDogHasFleas*MyNotDogHasNotFleas cosine=%f\n",csin);

   
  clock_gettime(CLOCK_MONOTONIC, &tstart);

  for(int c=0; c<sims; c++){
      csin = cosine_simularity(MyDogHasFleas,MyCatHasFleas);
      //printf("MyDogHasFleas*MyCatHasFleas cosine=%f\n",csin);
      
      csin = cosine_simularity(MyDogHasFleas,MyNotDogHasNotFleas);
      //printf("MyDogHasFleas*MyNotDogHasNotFleas cosine=%f\n",csin);
      
      csin = cosine_simularity(MyDogHasFleas,MyHamsterHasHiccups);
      //printf("MyDogHasFleas*MyHamsterHasHiccups cosine=%f\n",csin);
 }


    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("Computation of %d cosines took about %.5f seconds\n",
           3*sims,
           ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - 
           ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
    printf("\n\n");
}


 
