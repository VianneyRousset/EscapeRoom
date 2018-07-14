#ifndef ARRAY_H_
#define ARRAY_H_

// fifo
typedef struct {
	// p: first element ptr, n: nb of elements, s: sizeof element in bytes
	// N: buffers total size in bytes
	unsigned short p, n, s, N;
	void* buffer;
} Queue_t;

// create queue with a buffer being able to store N elements of s bytes each
Queue_t queue_create(void* buffer, unsigned short N, unsigned short s);

// push data in the queue and return the new number of elements in the queue
// return -1 if the queue was full before writting 
int queue_push(Queue_t* queue, const void* data);

// pull data from queue and return the number of remaining elements in the queue
// return -1 if the queue was empty before reading
int queue_pull(Queue_t* queue, void* data);

class StringQueue {

	private:
		char* buffer;

		// pointer to first str
		unsigned short p;

		// number of characters
		unsigned short n;

		// size of the buffer in bytes 
		unsigned short N;

	public:
		// buffer size in byte
		StringQueue(unsigned short bufferSize);

		// push str to queue. Return nb of free buffer space in bytes.
		// In case of buffer overflow, str is not copied and return -1 
		int	push(const char* str);

		// get str ptr to str first string.
		const char* get(void);

		// remove first element. Return nb of free buffer space in bytes.
		// return -1 if the buffer was already empty before removing.
		int remove(void);
};

#endif
