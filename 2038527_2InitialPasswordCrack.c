#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <unistd.h>
#include <time.h>


int counter=0;     


void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void crackPassword(char *salt_and_encrypted){
  int p, r, a;    
  char salt[7];    
  char plain[7];   
  char *enc;       

  substr(salt, salt_and_encrypted, 0, 6);


  for(p='A'; p<='Z'; p++){
    for(r='A'; r<='Z'; r++){
      for(a=0; a<=99; a++){
        sprintf(plain, "%c%c%02d",p, r, a);
        enc = (char *) crypt(plain, salt);
        counter++;
        if(strcmp(salt_and_encrypted, enc) == 0){
	    printf("#%-8d%s %s\n", counter, plain, enc);
			
        }else{
	    printf("%-8d%s %s\n", counter, plain, enc);
        }
      }
    }
  }
}


int time_difference(struct timespec *start, struct timespec *finish,
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
  crack("$6$AS$gnjzTs539N0Ly5zdQrpW3a9QdXCfWVJ/FtSdR/9/OkV9YPVPLg4H2k/J8lUGEALdxikWnCRz1sj21rqGe7SY51");	

  printf("%d solutions explored\n", counter);
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time taken was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9));
  return 0;
}

