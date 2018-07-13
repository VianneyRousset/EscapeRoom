#ifndef ARRAY_H_
#define ARRAY_H_

// fifo
typedef struct {
	unsigned short p, n, s, N;
	void* buffer;
} Queue_t;

// create queue with a buffer being able to store N elements of s bytes each
Queue_t queue_create(void* buffer, unsigned short N, unsigned short s);

// push data in the queue and return the new number of elements in the queue
// return -1 if the queue was full before writting 
int queue_push(Queue_t* queue, void* data);

// pull data from queue and return the number of remaining elements in the queue
// return -1 if the queue was empty before reading
int queue_pull(Queue_t* queue, void* data);

#endif
