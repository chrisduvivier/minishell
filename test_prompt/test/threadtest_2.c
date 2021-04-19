/*
	thread guarenteed to work until completion, AND atomic.
	Key is that, One thread can have the lock at a time.

	BUT, the thread might work in concurency (both working without waiting
	the other until completion), but is not working in PARALEL
	-> Extremely slow
 */

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

# define BIG 100000000UL
uint32_t counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void	*count_to_big(void *arg) {
	for (uint32_t i=0; i < BIG; i++) {
		pthread_mutex_lock(&lock);		// thread grab lock before inc
		counter ++;
		pthread_mutex_unlock(&lock);	// thread release lock after inc
	}
	return NULL;
}

int main(void) {
	pthread_t t;
	pthread_create(&t, NULL, count_to_big, NULL);
	count_to_big(NULL);
	printf("Done. Counter= %u\n", counter);
	pthread_join(t, NULL); // to guarentee the thread to complete
}

