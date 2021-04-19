/*
	thread guarenteed to work until completion, but not atomic.
	counter ++; is done simultaneously so it overwrites itself with potentially same value
	in both function call.
 */

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

# define BIG 100000000UL
uint32_t counter = 0;

void	*count_to_big(void *arg) {
	for (uint32_t i=0; i < BIG; i++) {
		counter ++;
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

