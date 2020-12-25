#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  struct timespec start, finish;
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  int N,M,P;
  printf("\nEnter size of first Matrix\n");
  scanf("%d%d", &N,&P);
  printf("\nEnter the size second of matrix\n");
  scanf("%d%d",&P,&M);	
  //int SizeOfArray = *Value;
  int A[N][P], B[P][M], C[N][M];
  int i,j,k;
  printf("\nEnter values for First Matrix\n");
  for (i = 0; i < N; i++)
  {
     for (j = 0; j < P; j++)
     {
	scanf("%10d",&A[i][j]);
     }
  }
  
  printf("\n");
  
  printf("Enter values for  Second Matrix\n");
  for (i = 0; i < P; i++)
  {
     for (j = 0; j < M; j++)
     {
	scanf("%10d",&B[i][j]);
     }
  }
	
  for (i = 0; i < N; i++)
  {
     for (k = 0; k < P; k++)
     {
	C[i][j] = 0;

	for (k = 0; k < P; k++)
	{
	   C[i][j] = C[i][j] + A[i][k] * B[k][j];
	}
     }
  }
  printf("\nThe results is: \n");
  for (i = 0; i < N; i++)
  {
     for (j = 0; j < M; j++)
     {
	printf("%10d  ", C[i][j]);
     }
     printf("\n");//
   }
   int time_difference(struct timespec *start,struct timespec *finish,long long int *difference)
   {
     long long int ds = finish->tv_sec - start->tv_sec;
     long long int dn = finish->tv_nsec - start->tv_nsec;

     if (dn < 0)
     {
	ds--;
	dn += 1000000000;
     }
     *difference = ds * 1000000000 + dn;
     return !(*difference > 0);
    }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    time_difference(&start, &finish, &time_elapsed);
    printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed / 1.0e9));
    return 0;
}
