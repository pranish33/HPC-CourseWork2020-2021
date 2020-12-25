#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <cuda_runtime_api.h>
#include <cuda_runtime.h>
#include <cuda.h>



__device__ int is_a_match(char *attempt){
	char normal_password1[]="HP21";

	char *a=attempt;

	char *np1= normal_password1;

	
	while (*a==*np1){
		if(*a=='\0'){
			printf("password: %s\n", normal_password1);
			return 1;
		}
		a++;
		np1++;	
	}

	
	return 0;
}

__global__ void kernel(){
	int p=0, q=0 ;
	char password[4];
	password[3]='\0';

	int i= blockIdx.x+65;
	int j= threadIdx.x+65;

	char firstmatch=i;
	char secondmatch=j;
	password[0]= firstmatch;
	password[1]= secondmatch;
	for(p='0'; p<='9';p++){
		for(q='0'; q<='9';q++){
					password[2]=p;
					password[3]=q;

					if(is_a_match(password)){
					}					
					
				}
	}
}

int time_difference(struct timespec *start, 
                    struct timespec *finish, 
                    long long int *difference) {
  long long int ds =  finish->tv_sec - start->tv_sec; 
  long long int dn =  finish->tv_nsec - start->tv_nsec; 

  if(dn < 0 ) {
    ds--;
    dn += 1000000000; 
  } 
  *difference = ds * 1000000000 + dn;
  return !(*difference > 0);
}

int main(int argc, char *argv[]){
  struct timespec start, finish;   
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

  kernel <<<26,26>>>();
  cudaThreadSynchronize();

  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
                                         (time_elapsed/1.0e9));

  return 0;
}
