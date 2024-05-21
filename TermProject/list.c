/*
 * File: list.c
 *
 * Author: Riley Heike
 *
 * Description: Implements a circular doubly-linked list data structure 
 * where each node contains a circular array of void ** elements that 
 * dynamically increase in size with each new node added, and delete
 * when the array is emptied
 *
 */


#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "list.h"

int initE = 10;

typedef struct node {

	void **elts;
	int index;
	struct node *prev;
	struct node *next;
	int count;
	int max;


}NODE;

struct list {

	int ncount;
	int itemCount;
	struct node *head;

};

/*
 * Create List
 *
 * Complexity: O(n)	
 *
 * Description: Creates the list and initializes counters and 
 * sentinel node
 *
 */

LIST *createList(void){

	LIST *lp = malloc(sizeof(LIST));
	assert(lp);
	lp->ncount = 0;
	lp->itemCount = 0;
	lp->head = malloc(sizeof(NODE));
	assert(lp->head);
	lp->head->next = lp->head;
	lp->head->prev = lp->head;
	return lp;

}

/*
 * Destroy List
 *
 * Complexity: O(log n) average
 *
 * Description: Traverses list and frees each node and 
 * respective void pointer array
 *
 */

void destroyList(LIST *lp){

	assert(lp);
	NODE *head = lp->head->next;
	NODE *next;
	while(head != lp->head){

		free(head->elts);
		next = head->next;
		free(head);
		head = next;

	}

	free(lp);

}


/*
 * Num Items
 *
 * Complexity: O(1) 
 *
 * Description: Returns total number of items in list
 *
 */

int numItems(LIST *lp){

	assert (lp);
	return lp->itemCount;

}

/*
 * Add First
 *
 * Complexity: O(1)
 *
 * Description: Adds item to front of list, creating new
 * node if neccessary
 *
 */

void addFirst(LIST *lp, void *item){

	assert(lp && item);

	NODE *f = lp->head->next;
	if(lp->ncount == 0){

		NODE *new = malloc(sizeof(NODE));
		assert(new);
	
		new->max = initE;

		new->elts = malloc(sizeof(void *) * new->max);
		assert(new->elts);

		new->count = 1;
		new->index = 0;

		new->elts[0] = item;
		new->prev = lp->head;
		lp->head->next = new;
		new->next = lp->head;
		lp->ncount++;
		lp->head->prev = new;
	}



	else if(f->count == f->max){

		NODE *old = f;
		NODE *new = malloc(sizeof(NODE));
		assert(new);

		initE *= 2;
		new->max = initE;

		new->elts = malloc(sizeof(void *) * new->max);
		assert(new->elts);

		new->index = 0;
		new->elts[0] = item;
		new->prev = lp->head;
		new->next = lp->head->next;
		old->prev = new;
		lp->head->next = new;
		lp->ncount++;
		new->count = 1;

	}
	else {
		f->elts[((f->index + f->count) % (f->max))] = item;
		f->count++;

	}
	lp->itemCount++;

}


/*
 * Add Last
 *
 * Complexity: O(1) 
 *
 * Description: Adds item to end of list, creating a new node
 * if neccessary
 *
 */

void addLast(LIST *lp, void *item){

	assert(lp && item);
	NODE *l = lp->head->prev;

	if(lp->ncount == 0){

		NODE *new = malloc(sizeof(NODE));
		assert(new);
	
		new->max = initE;

		new->elts = malloc(sizeof(void *) * new->max);
		assert(new->elts);

		new->count = 1;
		new->index = 0;
		new->elts[0] = item;
		new->prev = lp->head;
		lp->head->next = new;
		new->next = lp->head;
		lp->ncount++;
		lp->head->prev = new;

	}

	else if(l->count == l->max){

		
		NODE *old = l;
		NODE *new = malloc(sizeof(NODE));
		assert(new);

		initE *= 2;
		new->max = initE;
		new->elts = malloc(sizeof(void *) * new->max);
		assert(new->elts);

		new->index = 0;
		new->elts[0] = item;
		new->next = lp->head;
		new->prev = old;
		old->next = new;
		lp->head->prev = new;
		lp->ncount++;
		new->count = 1;

	}


	else{

		l->elts[(l->index + l->count) % l->max] = item;
		l->count++;
	}
	lp->itemCount++;
}


/*
 * Remove First
 *
 * Complexity: O(1)
 *
 * Description: Removes first item from the list and returns
 * it, deleting node if neccessary
 *
 */
void *removeFirst(LIST *lp){

	assert(lp);
	assert(lp->ncount > 0);
	NODE *f = lp->head->next;

	void *value = f->elts[f->index];

	if(f->count == 1){

		NODE *old = f;
		NODE *new = f->next;
		lp->head->next = new;
		new->prev = lp->head;
		free(old->elts);
		free(old);
		lp->ncount--;
		
	}

	else {

		f->index = ((f->index + 1) % f->max);
		f->count--;
			
	}
	
	lp->itemCount--;
	return value;
}


/*
 * Remove Last
 *
 * Complexity: O(1)
 *
 * Description: Removes the last item from the list
 * and returns it, deleting node if neccessary
 *
 */

void *removeLast(LIST *lp){

	assert(lp);
	assert(lp->ncount > 0);
	NODE *l = lp->head->prev;

	void *value = l->elts[(l->index + l->count - 1) % l->max];

	if(l->count == 1){

		NODE *old = l;
		NODE *new = l->prev;
		lp->head->prev = new;
		new->next = lp->head;
		free(old);
		lp->ncount--;
			
	}

	else {

		l->count--;
			
	}

	lp->itemCount--;
	return value;

}


/*
 * Get First
 *
 * Complexity: O(1)
 *
 * Description: Retrieves and returns the first item in the list
 *
 */

void *getFirst(LIST *lp){

	assert(lp && lp->ncount > 0);
	return lp->head->next->elts[lp->head->next->index];

}

/*
 * Get Last
 *
 * Complexity: O(1)
 *
 * Description: Retrieves and returns last item in the list
 *
 */

void *getLast(LIST *lp){

	assert(lp && lp->ncount > 0);
	return lp->head->prev->elts[(lp->head->prev->index + lp->head->prev->count - 1) % lp->head->prev->max];

}


/*
 * Get Item
 *
 * Complexity: O(log n)
 *
 * Description: Given index traverses over nodes and then locates
 * item at given index within node and returns it 
 *
 */

void *getItem(LIST *lp, int index){

	
	NODE *current = lp->head->next;
	int i = index;
	while(current->max <= i){

		i -= current->max;

		current = current->next;

	}

	return current->elts[i];

}


/*
 * Set Item
 *
 * Complexity: O(log n)
 *
 * Description: Same as get item but replaces with item passed
 * into function rather than returning item at index
 *
 */

void setItem(LIST *lp, int index, void *item){


	NODE *current = lp->head->next;
	int i = index;
	while(current->max <= i){

		i -= current->max;

		current = current->next;

	}

	current->elts[i] = item;

}
