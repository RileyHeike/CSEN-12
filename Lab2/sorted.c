/*
 * File: sorted.c
 *
 * Name: Riley Heike
 *
 * Date: 1/25/23
 *
 * Description: Program contains methods to create a
 * set, and modify elements in the set, similarly to
 * unsorted.c. However, this file uses methods to modify
 * elements in set to keep them sorted
 *
 */


#include "set.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct set {

	char **elts;
	int length;
	int count;

};


/* Search
 *
 * Complexity: O(log n)
 *
 * Description: Performs binary search over sorted set,
 * and returns the index of slot element should be at if 
 * not already in array, modifys boolean found to determine
 * if match was found within set
 *
 */

static int search(SET *sp, char *elt, bool *found){


	int hi = sp->count-1;
	int low = 0;
	int comp;
	int mid;
	while(low<=hi){
	
		mid = (hi+low)/2;
		comp = strcmp(sp->elts[mid], elt);

		if(comp == 0){

			*found = true;
			return mid;

		}

		else if(comp > 0)hi = mid-1;
	
		else low  = mid+1;
		
	}

	*found = false;
	return low;

}


/* Create Set
 *
 * Complexity: O(1)
 *
 * Description: Allocates memory and creates set based
 * on set struct, returns pointer to set
 *
 */

SET *createSet(int maxElts){

	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp);
	sp->elts = malloc(sizeof(char*) * maxElts);
	assert(sp->elts);
	sp->length = maxElts;
	sp->count = 0;


	return sp;

}

/* Find Element
 *
 * Complexity: O(log n)
 *
 * Description: Utilizes search function to locate element 
 * in set, returns element if found and NULL if not found
 *
 */

char *findElement(SET *sp, char *elt){
	
	bool found;
	int index = search(sp, elt, &found);	

	if(found) return elt;
	return NULL;

}


/* Get Elements
 *
 * Complexity: O(n)
 *
 * Description: Creates another set with length = count
 * of first set, uses for loop to populate second set, 
 * returns set
 *
 */

char **getElements(SET *sp){


	SET *sp2;
	sp2 = malloc(sizeof(SET));
	assert(sp2);
	sp2->elts = malloc(sizeof(char*) * sp->count);
	assert(sp->elts);

	int i;
	for(i = 0; i < sp->count; i++){

		sp2->elts[i] = sp->elts[i];

	}

	return sp2->elts;


}


/* Remove Element
 *
 * Complexity: O(n)
 *
 * Description: Uses search function to locate element,
 * then frees memory for that element and shifts all 
 * elements in array down 1 slot
 *
 */

void removeElement(SET *sp, char *elt){

	bool found;
	int index = search(sp, elt, &found);
	
	if(found){
			
		free(sp->elts[index]);
		int i;
		for(i = index; i < sp->count; i++){
		
			sp->elts[i] = sp->elts[i+1];
		
		}

		sp->count--;
		
	}

}


/* Destroy Set
 *
 * Complexity: O(1)
 *
 * Description: Frees memory associated with set
 *
 */

void destroySet(SET *sp){

	free(sp);

}

/* Add Element
 *
 * Complexity: O(n)
 *
 * Description: Uses search element to determine index to 
 * be inserted at, shifts all elements by 1 and inserts
 * element at index determined by search
 *
 */

void addElement(SET *sp, char *elt){

	assert(elt);
	assert(sp->count < sp->length);
	bool found;
	int index = search(sp, elt, &found);	

	if(!found){
	
		int i;
		for(i = sp->count; i > index; i--){
			sp->elts[i] = sp->elts[i-1];
		}
		sp->elts[index] = strdup(elt);
		sp->count++;
	}
}


/* Number Elements
 *
 * Complexity: O(1)
 *
 * Description: Returns number of elements in set
 *
 */

int numElements(SET *sp){

	return sp->count;

}
 
