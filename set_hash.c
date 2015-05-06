/*
set ADT for hash tables with separate chaining
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/
int hash(int num)
{
	int remainder;
	int sum = 0;
	
	while (num)
	{
		remainder = num % 10;
		num = num / 10;
		sum = sum + remainder;
	}

	return sum;
}

struct bucket_lnode
{
	int val;
	struct bucket_lnode *next;
};

struct bucket_list
{
	struct bucket_lnode *head;
};

/* typedef struct set set_t is defined in set.h */
struct set 
{
	struct bucket_list *list;
};

set_t *set_create(void)
{
	set_t *new_set;
	struct bucket_list *b_list;
	
	int i;
	
	new_set = safe_malloc(sizeof(set_t));
	new_set->list = safe_malloc(sizeof(struct bucket_list)*10);

	for (i = 0; i < 10; i++)
	{
		b_list = ((new_set->list) + i);
		b_list->head = NULL;
	}
	return new_set;
}

void set_destroy(set_t *set)
{
	struct bucket_list *b_list;
	struct bucket_lnode *node;
	struct bucket_lnode *del_node;
	int i;
	
	for (i = 0; i < 10; i++)
	{
		b_list = ((set->list) + i);
		node = b_list->head;
		while (node)
		{
			del_node = node;
			node = node->next;
			free(del_node);
		}
	}
	free(set->list);
	free(set);
	
	return;	
}

int set_insert(set_t *set, int new_val)
{
	int index;
	struct bucket_list *b_list;
	struct bucket_lnode **node;
	struct bucket_lnode *new_node;
	
	index = (hash(new_val) % 10);
	b_list = ((set->list) + index);
	node = &b_list->head;
	while (*node && (*node)->val < new_val)
	{
		node = &((*node)->next);
	}
	if (*node && (*node)->val == new_val)
	{
		return 0;
	}
	new_node = safe_malloc(sizeof(struct bucket_lnode));
	new_node->val = new_val;
	new_node->next = *node;
	*node = new_node;
	
	return 1;
}

int set_delete(set_t *set, int del_val)
{
	int index;
	struct bucket_list *b_list;
	struct bucket_lnode **node;
	struct bucket_lnode *del_node;
	
	index = (hash(del_val) % 10);
	b_list = ((set->list) + index);
	
	node = &b_list->head;
	while (*node && del_val > (*node)->val)
	{
		node = &((*node)->next);
	}
	if (*node && del_val == (*node)->val)
	{
		del_node = *node;
		*node = (*node)->next;
		free(del_node);
		return 1;
	}	
	return 0;	
}

int set_search(set_t *set, int search_val)
{
	int index;
	struct bucket_list *b_list;
	struct bucket_lnode *node;
	
	index = (hash(search_val) % 10);
	b_list = ((set->list) + index);
	node = b_list->head;
	while (node && search_val > node->val)
	{
		node = node->next;
	}
	if (node && search_val == node->val)
	{
		return 1;
	}
	return 0;	
}

void set_print(set_t *set)
{
	int i;
	struct bucket_list *b_list;
	struct bucket_lnode *node;
	for (i = 0; i < 10; i++)
	{
		b_list = ((set->list) + i);
		node = b_list->head;
		printf("bucket %d\n", i);
		while(node)
		{
			printf("%d - ", node->val);
			node = node->next;
		}
		printf("\n");
	}
	printf("\n");
}
