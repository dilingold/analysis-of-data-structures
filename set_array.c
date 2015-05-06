/*
set ADT for arrays
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#define INITIAL_SIZE 10

/******************************/
int binary_search(set_t *set, int search_val, int l, int r);

struct array_item
{
	int val;
};

/* typedef struct set set_t is defined in set.h */
struct set 
{
	int size;
	int count;
	struct array_item *item;
};

set_t *set_create(void)
{
	set_t *new_set;
	new_set = safe_malloc(sizeof(set_t));
	new_set->item = safe_malloc(sizeof(struct array_item) * INITIAL_SIZE);
	new_set->size = INITIAL_SIZE;
	new_set->count = 0;
	return new_set;
}
 
void set_destroy(set_t *set)
{
	free(set->item);
	free(set);
}

int set_insert(set_t *set, int new_val)
{
	struct array_item *new_item;
	struct array_item *current_item;
	struct array_item *next_item;
	int i;
	int j;
	
	if (set->size == set->count)
	{
		set->size*=2;
		set->item = realloc(set->item, sizeof(struct array_item)*(set->size));
	}
	if (set->count == 0)
	{
		new_item = (set->item);
		new_item->val = new_val;
		set->count++;
		return 1;
	}
	
	i = 0;
		
	current_item = (set->item);
	
	while (new_val > current_item->val && i < set->count)
	{
		i++;
		current_item = ((set->item) + i);
		
	}
	if (current_item->val == new_val)
	{
		return 0;
	}

	for (j = set->count; j > i; j--)
	{
		current_item = ((set->item) + (j-1));
		next_item = ((set->item) + j);
		next_item->val = current_item->val;
	}
	new_item = ((set->item) + i);
	new_item->val = new_val;

	set->count++;
	
	return 1;
}

int set_delete(set_t *set, int del_val)
{
	int i;
	struct array_item *delete_item;
	struct array_item *next_item;
	int j;
	
	i = 0;
	delete_item = set->item;
	while (del_val > delete_item->val && i < set->size)
	{
		i++;
		delete_item = ((set->item) + i);
	}
	if (del_val != delete_item->val)
	{
		return 0;
	}
	
	
	for (j = i; j < set->count; j++)
	{
		next_item = ((set->item) + (j+1));
		delete_item = ((set->item) + j);
		delete_item->val = next_item->val;
	}
	set->count--;
	
	
	return 1;
}

int set_search(set_t *set, int search_val)
{
	int l;
	int r;

	l = 0;
	r = set->count;
	return binary_search(set, search_val, l, r);	
}

int binary_search(set_t *set, int search_val, int l, int r)
{
	int m;
	struct array_item *item_m;
	
	if (l > r)
	{
		return 0;
	}
	m = (l + r) / 2;
	item_m = (set->item) + m;
	if (search_val == item_m->val)
	{
		return 1;
	}
	else if (search_val < item_m->val)
	{
		return binary_search(set, search_val, l, (m-1));
	}
	else
	{
		return binary_search(set, search_val, (m+1), r);
	}
	return 0;
}

void set_print(set_t *set)
{
	int i;
	struct array_item *item;
	
	i = 0;
	item = set->item;
	while (i < set->count)
	{
		printf("%d - ", item->val);
		i++;
		item = ((set->item) + i);
	}
	printf("\n");
}

