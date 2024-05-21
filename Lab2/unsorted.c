/*
 * File: unsorted.c
 *
 * Name: Riley Heike
 *
 * Date: 1/25/23
 *
 *
 * Description: Program contains methods to create set,
 * as well as modify elements inside set including adding
 * and removing, as well as functions to return copy of set
 * and search elements in the set. Set is unsorted
 *
 */



#include "set.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

struct set {

	char **elts;
	int length;
	int count;

};

/* Search
 *
 * Complexity: O(n)
 *
 * Description: Performs linear search over entire array,
 * returning index of element if found, and -1 if not found
 *
 */ 

static int search(SET *sp, char *elt){

	int i;
	for(i = 0; i <= sp->count-1; i++){

		if(strcmp(sp->elts[i], elt) == 0) return i;

	}

	return -1;

}

/* Create Set
 *
 * Complexity: O(1)
 *
 * Description: Allocates memory and creates set based
 * on set struct, returns set pointer
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
 * Complexity: O(n)
 *
 * Description: Uses search function to search for 
 * element in array, returns element if found and NULL
 * if not found
 *
 */

char *findElement(SET *sp, char *elt){

	if(search(sp, elt) != -1) return elt;
	return NULL;

}


/* Get Elements
 *
 * Complexity: O(n)
 *
 * Description: Creates another set with length equal
 * to count of original set and populates with data from
 * original set, returns copy set
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
 * Description: Utilizes search function to locate index
 * of element passed in as parameter, and deletes element 
 * from set, moves memory at end of set to take its place
 *
 */

void removeElement(SET *sp, char *elt){

	int index = search(sp, elt);
	
	if(index != -1){
			
		free(sp->elts[index]);
		sp->elts[index] = sp->elts[--sp->count]; 
		
		
	}

}


/* Destroy Set
 *
 * Complexity: O(1)
 *
 * Description: Deletes set by freeing all memory associated
 *
 */

void destroySet(SET *sp){

	free(sp);

}


/* Add Element
 *
 * Complexity: O(n)
 *
 * Description: Uses search function to determine whether
 * element already exists in set. If not, element is added
 * to end of set
 *
 */

void addElement(SET *sp, char *elt){

	assert(elt);
	assert(sp->count < sp->length);

	if(search(sp, elt) == -1){
		sp->elts[sp->count++] = strdup(elt);
	}
}


/* Number of Elements
 *
 * Complexity: O(1)
 *
 * Description: Returns number of elements in the set
 *
 */

int numElements(SET *sp){

	return sp->count;

}
 
