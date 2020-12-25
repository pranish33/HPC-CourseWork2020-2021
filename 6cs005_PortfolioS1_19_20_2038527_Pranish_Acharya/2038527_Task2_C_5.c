
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <pthread.h>




  /*Compile with:
    cc -o Task2C5 Task2C5.c -lcrypt
    */


    // A counter used to track the number of combinations explored so far
int n_passwords = 1;
int counter = 0;


char *encrypted_password[]={"$6$AS$5MUX6oD4KOSmVBi5yCmu.8FTv1EgYaX09sO49BVt7CutV9Y1KWJVmjqSHoeub/AnfQU4eEV6NeIaDUf.OG7XK/" };
			         

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void runThread(){
	int i;
	pthread_t PA1, PA2;
	
	void *kernel_function_1();
	void *kernel_function_2();
	for(i=0; i<n_passwords;i<i++){
	
	pthread_create(&PA1, NULL, kernel_function_1, encrypted_password[0]); //(thread_name, attribute, start_routine, argument)
	pthread_create(&PA2, NULL, kernel_function_2, encrypted_password[0]);
	
	pthread_join(PA1, NULL);
	pthread_join(PA2, NULL);
	
}
}

void *kernel_function_1(char *salt_and_encrypted){
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;       // Pointer to the encrypted password
  int counter=0; 
  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='M' ; x++){
    for(y='A'; y<='Z'; y++){
       for(z=0; z<=99; z++){
      	
    
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        counter++;
        if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", counter, plain, enc);
		
        }
        else{
            printf("#%-8d%s %s\n", counter, plain, enc);
            	
        } 
       }
      }
    }
    printf("%d solutions explored\n", counter);
} 


void *kernel_function_2(char *salt_and_encrypted){
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
  char plain[7];   // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
  char *enc;       // Pointer to the encrypted password
  int counter=0; 
  substr(salt, salt_and_encrypted, 0, 6);

  for(x='N'; x<='Z' ; x++){
    for(y='A'; y<='Z'; y++){
       for(z=0; z<=99; z++){
      	
    
        sprintf(plain, "%c%c%02d", x, y, z); 
        enc = (char *) crypt(plain, salt);
        counter++;
        if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", counter, plain, enc);
		
        } 
        else{
           printf("#%-8d%s %s\n", counter, plain, enc);
           
        }
       }
      }
    }
    printf("%d solutions explored\n", counter);
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

int main(){
int i;
  struct timespec start, finish;   
  long long int time_elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  
  runThread();
  clock_gettime(CLOCK_MONOTONIC, &finish);
  
  printf("%d solutions explored\n", counter);
  
  time_difference(&start, &finish, &time_elapsed);
  printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,(time_elapsed/1.0e9));
  return 0;
}

