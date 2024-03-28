#include <math.h>
#include <stdio.h>
#include <time.h>

//CHANGE BITVECTOR.. XNOR and population count


//[My,Dog,has,Fleas,Cat,Hamster,Hiccups]
int size = 7;
float MyDogHasFleas[] = {1,1,1,1,0,0,0};
float MyCatHasFleas[] = {1,0,1,1,1,0,0};
float MyNotDogHasNotFleas[] = {1,-1,1,-1,0,0,0};
float MyHamsterHasHiccups[] = {1,0,1,0,0,1,1};

float dotproduct(float a[],float b[]){
  float product = 0;
  for(int i=0;i<size;i++){
    product += (a[i] * b[i]);
  }
  return product;
}

float magnitude(float a[]){
      float product = 0;
      for(int i=0;i<size;i++){
        product += (a[i] * a[i]);
      }
      return sqrt(product);
}

float cosine_simularity(float a[],float b[]){
   float ma,mb,mt,dp,result;
   ma = magnitude(a);
   mb = magnitude(b);
   mt = ma * mb;
   if(mt!=0){
     dp = dotproduct(a,b);
     result = dp/mt;
     return result;
   } else { 
     return 0;
   }
}

int main(){
  float csin;
  int sims = 10000000;
  printf("\nTesting Float Vectors:\n\n");
  struct timespec tstart={0,0}, tend={0,0};

      csin = cosine_simularity(MyDogHasFleas,MyCatHasFleas);
      printf("MyDogHasFleas*MyCatHasFleas cosine=%f\n",csin);
      
      csin = cosine_simularity(MyDogHasFleas,MyNotDogHasNotFleas);
      printf("MyDogHasFleas*MyNotDogHasNotFleas cosine=%f\n",csin);
      
      csin = cosine_simularity(MyDogHasFleas,MyHamsterHasHiccups);
      printf("MyDogHasFleas*MyHamsterHasHiccups cosine=%f\n",csin);

   
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


 
