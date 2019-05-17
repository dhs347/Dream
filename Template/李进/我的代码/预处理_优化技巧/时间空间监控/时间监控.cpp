#define Time_In clock_t _t_=clock()
#define Time_Out printf("\n\n\ntime used is:  %lf seconds.\n\n",(double)(clock()-_t_)/CLOCKS_PER_SEC)



int main() {
	//Time_In;
    file_put();
 
	//Time_Out;
    return 0;
}




//例程
/* clock example: frequency of primes */

#include <stdio.h>      /* printf */
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */
#include <math.h>       /* sqrt */

int frequency_of_primes (int n) {
  int i,j;
  int freq=n-1;
  for (i=2; i<=n; ++i) for (j=sqrt(i);j>1;--j) if (i%j==0) {--freq; break;}
  return freq;
}

int main ()
{
  clock_t t;
  int f;
  t = clock();
  printf ("Calculating...\n");
  f = frequency_of_primes (99999);
  printf ("The number of primes lower than 100,000 is: %d\n",f);
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  return 0;
}