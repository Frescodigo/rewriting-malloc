#include "malloc-2.c"
#include <stdio.h>

typedef struct Node {
	struct Node* next;
	int data;
} Node;

Node* create_node(int data)
{
	Node* new_node = alloc(sizeof(Node));
	new_node->data = data;
	new_node->next = NULL;
	return new_node;
}

void append(Node* head, int data)
{
	Node* new_node = create_node(data);
	Node* node = head;
	while (node->next)
	{
		node = node->next;
	}
	node->next = new_node;
}

void remove(Node* head, int data)
{
	if (head->data == data)
	{
		head = head->next;
		return;
	}

	Node* node = head;
	while (node->next)
	{
		if (node->next->data == data)
		{
			node->next = node->next->next;
			return;
		}
		node = node->next;
	}

}

void print_list(Node* head)
{
	for (Node* n = head; n; n = n->next)
	{
		printf("%d -> ", n->data);
	}
	printf("\n");
}

void print_list_p(Node* head)
{
	for (Node* n = head; n; n = n->next)
	{
		printf("-%d\t @ %p\n |\n V\n", n->data, n);
	}
}

void free_list(Node* head)
{
	if (head)
	{
		free_list(head->next);
		free(head);
	}
}

int main()
{
	Node* head = create_node(69);
	print_list(head);

	append(head, 420);
	print_list(head);

	append(head, 1337);
	print_list(head);

	print_list_p(head);

	free_list(head);
}
