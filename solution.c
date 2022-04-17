#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <sys/sysinfo.h>
#include <string.h>
#include <semaphore.h>
#include <unistd.h>



int piece = 0;
int begin = 0;
int finish = 0;
long sum = 0;
long primeCounter = 0;
pthread_mutex_t lock;



int isPrime(int num) {
   int c;
   if (num <= 1) {
	   return 0;
   }
   for (c = 2; c <= sqrt(num); c++)
   {
      if (num%c == 0)
     return 0;
   }
   return 1;
}

void* calculation() {
	int start = begin;
	int end = finish;
	begin += piece;
	finish += piece;
	int random = 0;
	for (int i=start; i < end; i++){
		random = rand();
		if (isPrime(random)){
			pthread_mutex_lock(&lock);
			sum = sum + random;
			primeCounter++;
			pthread_mutex_unlock(&lock);
		}	
    }
	return NULL;
}



int main(int argc, char *argv[]) {
	srand(atoi(argv[1]));
    int err;
	int i=0;
	int z = get_nprocs_conf();
	pthread_t tid[z];
	piece = atoi(argv[2]) / z;
	finish += piece;
	while(i < z) {
        err = pthread_create(&(tid[i]), NULL, &calculation, NULL);
        if (err != 0) printf("\ncan't create thread :[%s]", strerror(err));
        i++;
    }
	for (int j = 0; j < z; j++)
	{
		pthread_join(tid[j], NULL);
	}
	
	printf("%ld,%ld \n", sum, primeCounter);
    exit(0);
}
