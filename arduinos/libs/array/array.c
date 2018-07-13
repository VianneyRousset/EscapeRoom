#include "array.h"
#include <string.h>

Queue_t queue_create(void* buffer, unsigned short N, unsigned short s)
{
	Queue_t q = {0, 0, s, N, buffer};
	return q;
}

int queue_push(Queue_t* q, void* data)
{
	// buffer full
	if (q->n == q->N)
		return -1;

	const unsigned short p = (q->p+q->n) % q->N;
	memcpy(q->buffer + p*q->s, data, q->s);
	q->n++;
	return q->n;
}

int queue_pull(Queue_t* q, void* data)
{
	memcpy(data, q->buffer + q->p*q->s, q->s);
	
	// buffer empty
	if (q->n == 0)
		return -1;

	q->n--;
	q->p = (q->p+1) % q->N;
	return q->n;
}

