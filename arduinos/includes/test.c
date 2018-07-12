#include "array.h"
#include <stdio.h>
#include <stdbool.h>

typedef short TestType;

TestType buffer[8];

void main()
{
	TestType a = 0;
	int number;
	Queue_t q = queue_create(buffer, 8, sizeof(TestType));
	char str[64];

	while (true) {
		scanf("%s", str);
		if (sscanf(str, "%i", &number) > 0) {
			a = number;
			int n = queue_push(&q, &a);
			printf("Adding %d to queue with now %d elements\n", number, n);
		} else {
			int n = queue_pull(&q, &a);
			printf("Getting %d from queue with %d remaining elements\n", a, n);
		}
	}

}
