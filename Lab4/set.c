#include "set.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "list.h"

typedef struct set{

	LIST **elts;
	int length;
	int count;
	int (*compare)();
	unsigned (*hash)();

}SET;



/* Create Set
 *
 * Complexity: O(n)
 *
 * Description: Allocates memory and creates list for each 
 * location in hash table
 *
 */

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){

	assert((*hash) && (*compare));

	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp);
	sp->elts = malloc(sizeof(void*) * maxElts);
	assert(sp->elts);
	sp->compare = compare;
	sp->hash = hash;
	sp->length = maxElts;
	sp->count = 0;

	int i;
	for(i = 0; i < sp->length; i++) sp->elts[i] = createList(sp->compare);

	return sp;

}

/* Destroy Set
 *
 * Complexity: O(n)
 *
 * Description: Deletes set by freeing each list, and
 * then entire set
 *
 */

void destroySet(SET *sp){

	assert(sp);

	int i;
	for(i = 0; i < sp->length; i++){

		destroyList(sp->elts[i]);

	}

	free(sp->elts);
	free(sp);
	
}


/* Number of Elements
 *
 * Complexity: O(1)
 *
 * Description: Returns number of elements in the set
 *
 */

int numElements(SET *sp){

	assert(sp);
	return sp->count;

}


/* Add Element
 *
 * Complexity: O(n)
 *
 * Description: Determines whether item is already
 * in set by going through list located at hashing key,
 * adds element if it is not
 *
 */

void addElement(SET *sp, void *elt){

	unsigned locn;

	assert(elt && sp);
	assert(sp->count < sp->length);
	locn = (sp->hash)(elt) % sp->length;

	if(findItem(sp->elts[locn], elt) == NULL){
		addFirst(sp->elts[locn], elt);
		sp->count++;

	}
}

/* Remove Element
 * 
 * Complexity: O(n)
 *
 * Description: Utilizes findItem function to locate item
 * if it is in the lsit located at the hashing key
 *
 */

void removeElement(SET *sp, void *elt){

	assert(sp && elt);
	int key = (sp->hash)(elt) % sp->length;

	if(findItem(sp->elts[key], elt) != NULL){
		removeItem(sp->elts[key], elt);
		sp->count--;
	}

}

/* Find Element
 *
 * Complexity: O(n)
 *
 * Description: Goes through list of elements located
 * at hashing key to determine if exists, returns the 
 * item if found
 *
 */

void *findElement(SET *sp, void *elt){

	assert(sp && elt);
	
	int i = (sp->hash)(elt) % sp->length;
	return findItem(sp->elts[i], elt);
	

}


/* Get Elements
 *
 * Complexity: O(n)
 *
 * Description: Copies every element cotained in the set
 * to a new void pointer that is returned
 *
 */

void *getElements(SET *sp){

	assert(sp && (sp->count > 0));
	void **elts;
	void **temp;	

	elts = malloc(sizeof(void *) * sp->count);
	assert(elts);

	int index = 0;

	int i;
	for(i = 0; i < sp->length; i++){

		temp = getItems(sp->elts[i]);
		memcpy(elts+index, temp, sizeof(void *) * numItems(sp->elts[i]));	
	
		index += numItems(sp->elts[i]);
		free(temp);

	}

	return elts;
}
