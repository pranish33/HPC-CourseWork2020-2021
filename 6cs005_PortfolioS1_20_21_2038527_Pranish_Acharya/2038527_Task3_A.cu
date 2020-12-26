#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__device__ char* CudaCrypt(char* rawPassword){

	 
	 char * newPassword = (char *) malloc(sizeof(char) * 11);

	newPassword[0] = rawPassword[0] + 2;
	newPassword[1] = rawPassword[0] - 2;
	newPassword[2] = rawPassword[0] + 1;
	newPassword[3] = rawPassword[1] + 3;
	newPassword[4] = rawPassword[1] - 3;
	newPassword[5] = rawPassword[1] - 1;
	newPassword[6] = rawPassword[2] + 2;
	newPassword[7] = rawPassword[2] - 2;
	newPassword[8] = rawPassword[3] + 4;
	newPassword[9] = rawPassword[3] - 4;
	newPassword[10] = '\0';

	for(int i =0; i<10; i++){
		if(i >= 0 && i < 6){ 
			if(newPassword[i] > 122){ 
				newPassword[i] = (newPassword[i] - 122) + 97;
			}else if(newPassword[i] < 97){
				newPassword[i] = (97 - newPassword[i]) + 97;
			}
		}else{ 
			if(newPassword[i] > 57){
				newPassword[i] = (newPassword[i] - 57) + 48;
			}else if(newPassword[i] < 48){
				newPassword[i] = (48 - newPassword[i]) + 48;
			}
		}
		
	}
         
       
        
	return newPassword; 
}

__device__ int is_password(char* Encrypted){
      
       char Password[]="pa15";
       
       char *a=Encrypted;
       
       char *p=CudaCrypt(Password);
  
	while (*a == *p){
	
	if (*a == '\0')
	{
	printf("Encrypted Password: %s\n",Encrypted);
	printf("Password Found: %s\n",Password);
	break;
	}
	a++;
	p++;
	}
	return 0;
}

__global__ void crack(char * alphabet, char * numbers){ 
    
   char genRawPass[4];

   genRawPass[0] = alphabet[blockIdx.x];
   genRawPass[1] = alphabet[blockIdx.y];

   genRawPass[2] = numbers[threadIdx.x];
   genRawPass[3] = numbers[threadIdx.y];
   
   char *generated=CudaCrypt(genRawPass);
	
   is_password(generated);
   
  
        

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

int main(int argc, char ** argv){
  struct timespec start, finish;   
  long long int time_elapsed;
  clock_gettime(CLOCK_MONOTONIC, &start);

  char cpuAlphabet[26] =  {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
  char cpuNumbers[26] = {'0','1','2','3','4','5','6','7','8','9'};

  char * gpuAlphabet;
  cudaMalloc( (void**) &gpuAlphabet, sizeof(char) * 26); 
  cudaMemcpy(gpuAlphabet, cpuAlphabet, sizeof(char) * 26, cudaMemcpyHostToDevice);

  char * gpuNumbers;
  cudaMalloc( (void**) &gpuNumbers, sizeof(char) * 26); 
  cudaMemcpy(gpuNumbers, cpuNumbers, sizeof(char) * 26, cudaMemcpyHostToDevice);

  crack<<< dim3(26,26,1), dim3(10,10,1) >>>( gpuAlphabet, gpuNumbers);  
  
  cudaDeviceSynchronize();
  
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed, (time_elapsed/1.0e9));
  return 0;
}













