#include "array.hpp"
#include <string.h>

Queue_t queue_create(void* buffer, unsigned short N, unsigned short s)
{
	Queue_t q = {0, 0, s, N, buffer};
	return q;
}

int queue_push(Queue_t* q, const void* data)
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

StringQueue::StringQueue(unsigned short bufferSize) : buffer(new char[bufferSize])
{
	this->p = 0;
	this->n = 0;
	this->N = bufferSize;
}

int	StringQueue::push(const char* str)
{
	const unsigned short end = (this->p+this->n) % this->N;
	const unsigned short len = strlen(str)+1;
	
	// can be placed at the end
	if (end+len <= this->N) {
		memcpy(this->buffer+end, str, len);
		this->n += len;
		return this->N - this->n;
	}

	// has to be place at beginning
	if (len > p) { // no enough place at beginning
		return -1;
	}

	memset(this->buffer+end, '\0', this->N-end);
	this->n += this->N-end;
	memcpy(this->buffer, str, len);
	this->n += len;
	return this->N - this->n;
}

const char* StringQueue::get(void)
{
	if (this->n == 0)
		return NULL;
	return this->buffer + p;
}

int StringQueue::remove(void)
{
	unsigned short len = strlen(this->buffer+this->p)+1;

	if (this->n == 0) { // trying to remove element in empty buffer
		return -1;
	}

	if (this->buffer[p+len] == '\0') {
		len = this->N - this->p;
		this->p = 0;
	} else {
		this->p += len;
	}

	if (len > n) {
		this->n = 0;
	} else {
		this->n -= len;
	}

	if (this->n == 0)
		this->p = 0;

	return this->N - this->n;
}
