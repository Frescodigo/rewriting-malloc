#include <stdlib.h>


// Just take a megabyte of ram at runtime
static unsigned char heap[1024 * 1024];
static unsigned char* heap_ptr = heap;

void *alloc(size_t size)
{
	if (heap_ptr + size > heap + sizeof(heap))
	{
		return NULL;
	}

	void *p = heap_ptr;
	heap_ptr += size;
	return p;
}

void free(void* x)
{

}
