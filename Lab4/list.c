#include <stdlib.h>
#include "list.h"
#include <assert.h>

typedef struct list{

	int count;
	struct node *head;
	int (*compare)();

}LIST;

typedef struct node {
	
	void *data;
	struct node *next;
	struct node *prev;

}NODE;

/* Create List
 *
 * Complexity: O(1)
 *
 * Description: Creates doubly-linked list with 
 * sentinel node set as the head
 *
 */

extern LIST *createList(int (*compare)()){

	LIST *nlist = malloc(sizeof(LIST));
	assert(nlist);
	nlist->count = 0;
	nlist->compare = compare;

	NODE *sent = malloc(sizeof(NODE));
	assert(sent);

	nlist->head = sent;
	sent->next = nlist->head;
	sent->prev = nlist->head;		

	return nlist;
}


/* Destroy List
 *
 * Complexity: O(n)
 *
 * Description: Traverses entire list to free
 * each individual node
 *
 */

extern void destroyList(LIST *lp){
	
	assert(lp);

	NODE *cdel = lp->head->next;
	while(lp->head != cdel){

		NODE *temp = cdel;
		cdel = cdel->next;
		free(temp);	

	}

	free(lp->head);
	free(lp);

}


/* Num Items
 *
 * Complexity: O(1)
 *
 * Description: Returns the number of nodes in the
 * linked list
 *
 */

extern int numItems(LIST *lp){

	assert(lp);
	return lp->count;

}


/* Add First
 *
 * Complexity: O(1)
 *
 * Description: Creates a node and inserts into the linked
 * list immediately following the sentinel node with 
 * data passed in as a parameter
 *
 */

extern void addFirst(LIST *lp, void *item){

	assert(lp && item);
	lp->count++;
		
	NODE *new = malloc(sizeof(NODE));
	assert(new);
	new->data = item;
	
	lp->head->next->prev = new;
	new->next = lp->head->next;
	new->prev = lp->head;
	lp->head->next = new;

	return;

}


/* Add Last
 *
 * Complexity: O(1)
 *
 * Description: Creates a new node and inserts into
 * linked list at the end, with data as passed in as 
 * parameter
 *
 */

extern void addLast(LIST *lp, void *item){

	assert(lp && item);

	
	NODE *new = malloc(sizeof(NODE));
	assert (new);
	new->data = item;
	lp->count++;	

	lp->head->prev->next = new;
	new->next = lp->head;
	new->prev = lp->head->prev;
	lp->head->prev = new;

	return;

}


/* Remove First
 *
 * Complexity: O(1)
 *
 * Description: Removes the node at the beginning
 * of the list, and returns the data in that node
 *
 */

extern void *removeFirst(LIST *lp){

	assert(lp && (lp->count > 0));

	NODE *cdel = lp->head->next;
	void *tdat = cdel->data;
	lp->head->next = cdel->next;
	cdel->next->prev = lp->head;

	free(cdel);
	lp->count--;

	return tdat;
}


/* Remove Last
 *
 * Complexity: O(1)
 *
 * Description: Removes the last node in the list, 
 * resets pointers and returns the data in the node
 *
 */

extern void *removeLast(LIST *lp){

	assert(lp && (lp->count > 0));

	NODE *cdel = lp->head->prev;
	void *tdat = cdel->data;
	lp->head->prev = cdel->prev;
	cdel->prev->next = lp->head;

	free(cdel);
	lp->count--;

	return tdat;
}


/* Get First
 *
 * Complexity: O(1)
 *
 * Description: Returns the data of the first node
 * in the list following the sentinel
 *
 */

extern void *getFirst(LIST *lp){

	assert(lp);
	return lp->head->next->data;

}

/* Get Last
 *
 * Complexity: O(1)
 *
 * Description: Returns the data of the last node
 * in the list
 *
 */

extern void *getLast(LIST *lp){

	assert(lp);
	return lp->head->prev->data;

}


/* Remove Item
 *
 * Complexity: O(n)
 *
 * Description: Traverses through entire list and 
 * checks with item passed into function, removes node
 * if data matches item
 *
 */

extern void removeItem(LIST *lp, void *item){

	assert(lp && lp->compare);
	assert(lp->count > 0);
	
	NODE *temp = lp->head->next;
	while(temp != lp->head){

		if((lp->compare)(temp->data, item) == 0){

			temp->prev->next = temp->next;
			temp->next->prev = temp->prev;
			free(temp);
			lp->count--;
			return;
		}
	
		temp = temp->next;

	}


}


/* Find Item
 *
 * Complexity: O(n)
 *
 * Description: traverses entire list and compares
 * node data with item passed in, returns data if matches 
 * and NULL if item was never found
 *
 */

extern void *findItem(LIST *lp, void *item){

	assert(lp && item);

	NODE *temp = lp->head->next;
	while(temp != lp->head){

		if((lp->compare)(temp->data, item) == 0) return temp->data;	
	
		temp = temp->next;
	}

	return NULL;

}


/* Get Items
 *
 * Complexity: O(n)
 *
 * Description: Traverses entire linked list and
 * copies data from each node into a void * pointer
 * which gets returned at end of the function
 *
 */

extern void *getItems(LIST *lp){

	assert(lp);
	void **dataList = malloc(sizeof(void*) * lp->count);
	NODE *temp = lp->head->next;

	int i;
	for(i = 0; i < lp->count; i++){

		dataList[i] = temp->data;
		temp = temp->next;

	}
	
	return dataList;

}
