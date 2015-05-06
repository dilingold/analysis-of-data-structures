/*
set ADT for binary trees
*/

#include "set.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

/******************************/


struct tree_node {
	struct tree_node *rc_node;
	struct tree_node *lc_node;
	struct tree_node *p_node;
	int val;
};
void delete_node(struct tree_node *);
void print_node(struct tree_node *);
/* typedef struct set set_t is defined in set.h */
struct set {
	struct tree_node *parent_node;
};

set_t *set_create(void)
{
	set_t *new_set;
	new_set = safe_malloc(sizeof(set_t));
	new_set->parent_node = NULL;
	return new_set;
}

void set_destroy(set_t *set)
{
	delete_node(set->parent_node);
	free(set);
}

void delete_node(struct tree_node *node)
{
	if(node == NULL)
	{
		return;
	}
	else
	{
		delete_node(node->lc_node);
		delete_node(node->rc_node);
		free(node);
	}
}

int set_insert(set_t *set, int new_val)
{
	struct tree_node **node;
	struct tree_node *parent_node;
	struct tree_node *new_node;
	
	node = &set->parent_node;
	
	while (*node)
	{
		if (new_val > (*node)->val)
		{
			parent_node = *node;
			node = &((*node)->rc_node);
		}
		else if (new_val < (*node)->val)
		{
			parent_node = *node;
			node = &((*node)->lc_node);
		}
		else if (new_val == (*node)->val)
		{
			return 0;
		}
	}
	new_node = safe_malloc(sizeof(struct tree_node));
	new_node->val = new_val;
	new_node->p_node = parent_node;
	*node = new_node;
	
	return 1;
}

int set_delete(set_t *set, int del_val)
{
	struct tree_node **node;
	struct tree_node *del_node;
	struct tree_node **replace_node;
	
	node = &set->parent_node;
	while (*node && (del_val > (*node)->val || del_val < (*node)->val))
	{
		if (del_val > (*node)->val)
		{
			node = &((*node)->rc_node);
		}
		else if (del_val < (*node)->val)
		{
			node = &((*node)->lc_node);
		}
	}
	if (!(*node) || (*node)->val != del_val)
	{
		return 0;		
	}
	del_node = *node;
	if (!del_node->rc_node && !del_node->lc_node)
	{

		return 1;
	}
	else if (del_node->rc_node && !del_node->lc_node)
	{
		replace_node = &(del_node->rc_node);
		node = &(del_node->p_node);
		if ((*replace_node)->val > (*node)->val)
		{
			(*node)->rc_node = *replace_node;
		}
		if ((*replace_node)->val < (*node)->val)
		{
			(*node)->lc_node = *replace_node;
		}
		(*replace_node)->p_node = (*node);

		return 1;
	}
	else if (!del_node->rc_node && del_node->lc_node)
	{
		replace_node = &(del_node->lc_node);
		node = &(del_node->p_node);
		if ((*replace_node)->val > (*node)->val)
		{
			(*node)->rc_node = *replace_node;
		}
		if ((*replace_node)->val < (*node)->val)
		{
			(*node)->lc_node = *replace_node;
		}
		(*replace_node)->p_node = (*node);

		return 1;
	}
	else 
	{
		node = &((*node)->rc_node);
		if ((*node)->lc_node)
		{
			while ((*node)->lc_node)
			{
				node = &((*node)->lc_node);
			}
		}
		if ((*node)->rc_node)
		{
			del_node->val = (*node)->val;
			del_node = *node;
			
			replace_node = &((*node)->rc_node);
			node = &((*node)->p_node);
			if ((*replace_node)->val > (*node)->val)
			{
				(*node)->rc_node = *replace_node;
			}
			if ((*replace_node)->val < (*node)->val)
			{
				(*node)->lc_node = *replace_node;
			}
			(*replace_node)->p_node = (*node);

			return 1;
		}
		del_node->val = (*node)->val;

		return 1;
	}
}

int set_search(set_t *set, int search_val)
{
	struct tree_node *search_node;
	
	search_node = set->parent_node;
	while(search_node)
	{
		if (search_val > search_node->val)
		{
			search_node = search_node->rc_node;
		}
		else if (search_val < search_node->val)
		{
			search_node = search_node->lc_node;
		}
		else if (search_val == search_node->val)
		{
			return 1;
		}
	}
	return 0;
	
}

void set_print(set_t *set)
{
	print_node(set->parent_node);
}

void print_node(struct tree_node *node)
{
	if (node == NULL)
	{
		return;
	}
	else
	{
			print_node(node->lc_node);
			print_node(node->rc_node);
			printf("%d ", node->val);
			if (node->rc_node)
			{
				printf("-- %d\n", node->rc_node->val);
			}
			if (node->lc_node)
			{
				printf(" |\n %d\n", node->lc_node->val);
			}
			printf("\n");
	}
}
