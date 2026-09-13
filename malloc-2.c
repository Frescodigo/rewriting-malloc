#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ALIGN_UP_POW2(n, p) (((size_t)(n) + ((size_t)(p) - 1)) & ( ~((size_t)(p) - 1)))

#define CAPACITY 1024 * 1024

unsigned char heap[CAPACITY];

struct block
{
	size_t size;
	int free;
	struct block* next;
};

void create_block(unsigned char* pos, size_t size)
{
	struct block new_block = { size, 0, NULL };
	memcpy(pos, &new_block, sizeof(struct block));
}

struct block* blocks = NULL;

void* alloc(size_t size)
{
	if (blocks == NULL)
	{
		blocks = (struct block*) heap;
		create_block(heap, size);
		return heap + sizeof(struct block);
	}

	// find first free block with enough space or last block
	struct block* b = blocks;
	while (b->next)
	{
		if (b->free == 1 &&
				((b->next != NULL && (unsigned char*) b + size + sizeof(struct block) < (unsigned char*) b->next)
				 || (b->next == NULL && (unsigned char*) b + size < heap + CAPACITY))
			)
		{

			// size is big enough if 

			b->size = size;
			b->free = 0;
			return (unsigned char*) b + size;
		}
		b = b->next;
	}

	// b is a block with no next
	// next available spot is b + size of header + size of body
	unsigned char* new_pos = (unsigned char*) ALIGN_UP_POW2(
			(size_t)b + sizeof(struct block) + b->size,
			sizeof(void*)
	);
	create_block(new_pos, size);
	b->next = (struct block*) new_pos;
	return new_pos + sizeof(struct block);
}

void free(void* addr)
{
	// should probably check if the addr actually points to a block
	struct block* block_to_delete = addr - sizeof(struct block);

	for (struct block* b = blocks; b; b = b->next)
	{
		if (b == block_to_delete)
		{
			b->free = 1;
			return;
		}
	}

	// if nothing is found, crash the program lol
	fprintf(stderr, "fucked up\n");
	exit(1);
}

