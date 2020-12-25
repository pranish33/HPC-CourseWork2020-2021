#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// use 4 for a quad processor, but try also with 1 and 2 threads
// to check the running time and the system load

// matrix dimension
#define dim 1024

int thread_count;

struct param {
  int start_line, end_line;
};

int a[dim][dim], b[dim][dim], c[dim][dim];

void init_matrix(int m[dim][dim]) {
   int i, j;
   for (i = 0; i < dim; i++)
     for (j = 0; j < dim; j++)
       m[i][j] = rand() % 5;
}

void* thread_function(void *v) {
  struct param *p = (struct param *) v;

  int i, j, k;
  for (i = p->start_line; i < p->end_line; i++)
    for (j = 0; j < dim; j++) {
      int s = 0;
      for (k = 0; k < dim; k++)
        s += a[i][k] * b[k][j];
      c[i][j] = s;
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
int main() {
  struct timespec start, finish;
  long long int time_elapsed;
  int i;
  int start_time, end_time;

  printf("Enter the number of thread: ");
  scanf("%d",&thread_count);
  struct param params[thread_count];
  pthread_t t[thread_count];


  clock_gettime(CLOCK_MONOTONIC, &start);
  init_matrix(a);
  init_matrix(b);



  for (i = 0; i < thread_count; i++) {
    int code;
    params[i].start_line = i * (dim / thread_count);
    params[i].end_line = (i + 1) * (dim / thread_count);

    code = pthread_create(&t[i], NULL, thread_function, &params[i]);
    if (code != 0)
      printf("Error starting thread %d\n", i);
  }

  for (i = 0; i < thread_count; i++)
    pthread_join(t[i], NULL);

	printf("\nThe results is…\n");
	for(int i=0; i<dim; i++) {
	 for(int j=0; j<dim; j++) {
	   printf("%d  ", c[i][j]);
	  }
	printf("\n");
	}
  clock_gettime(CLOCK_MONOTONIC, &finish);
  time_difference(&start, &finish, &time_elapsed);
  printf("Time taken was %lldns or %0.9lfs\n", time_elapsed,
         (time_elapsed/1.0e9));

}
