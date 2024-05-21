#include "set.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct set{

	void **elts;
	int length;
	int count;
	char *flags;
	int (*compare)();
	unsigned (*hash)();

};


/* Search
 *
 * Complexity: 
 * 	Worst Case: O(n)
 * 	Average Case: O(1)
 *
 * Description: Searches for element passed into function 
 * within set passed into function, modifies address of bool
 * passed into funtion to convey whether it was found or not,
 * returns address of element if found
 *
 */


static int search(SET *sp, void *elt, bool *found){

	assert(elt);
	int dkey;
	bool foundD = false;
	unsigned key = (*sp->hash)(elt);
	int loc;

	int i;
	for(i = 0; i < sp->length; i++){
		loc = (i+key) % sp->length;
	
		if(sp->flags[loc] == 'E'){
			*found = false;
			if(foundD) return dkey;
			return loc;
		
		}
		
		else if((sp->flags[loc] == 'D')){

			if(!foundD) dkey = loc;
			foundD = true;
			
		}

		else if ((*sp->compare)(sp->elts[loc], elt) == 0){

			*found = true;
			return loc;
	
		}
		

	}
	*found = false;
	return dkey;

}

/* Create Set
 *
 * Complexity: O(1)
 *
 * Description: Allocates memory and creates set based
 * on set struct, returns set pointer
 *
 */

SET *createSet(int maxElts, int (*compare)(), unsigned (*hash)()){

	SET *sp;
	sp = malloc(sizeof(SET));
	assert(sp);
	sp->elts = malloc(sizeof(void*) * maxElts);
	sp->flags = malloc(sizeof(char) * maxElts);
	assert(sp->elts);
	assert(sp->flags);
	sp->compare = compare;
	sp->hash = hash;
	sp->length = maxElts;
	sp->count = 0;

	int i;
	for(i = 0; i < sp->length; i++) sp->flags[i] = 'E';

	return sp;

}

/* Destroy Set
 *
 * Complexity: O(1)
 *
 * Description: Deletes set by freeing all memory associated
 *
 */

void destroySet(SET *sp){

	assert(sp);
	free(sp->elts);
	free(sp->flags);
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
 * Complexity: 
 * 	Worst Case: O(n)
 * 	Average Case: O(1)
 *
 * Description: Uses search function to determine whether
 * element already exists in set. If not, element is added
 * to end of set
 *
 */

void addElement(SET *sp, void *elt){

	bool found;
	int locn;

	assert(elt && sp);
	assert(sp->count < sp->length);
	locn = search(sp, elt, &found);

	if(!found){
		sp->elts[locn] = elt;
		sp->flags[locn] = 'F';
		sp->count++;

	}
}

/* Remove Element
 * 
 * Complexity: 
 * 	Worst Case: O(n)
 * 	Average Case: O(1)
 *
 * Description: Utilizes search function to locate index
 * of element passed in as parameter, and deletes element 
 * from set, moves memory at end of set to take its place
 *
 */

void removeElement(SET *sp, void *elt){

	assert(sp && elt);
	bool found = false;
	int key = search(sp, elt, &found);

	if(found){
		sp->flags[key] = 'D';
		sp->count--;
	}

}

/* Find Element
 *
 * Complexity:  
 * 	Worst Case: O(n)
 * 	Average Case: O(1)
 *
 * Description: Uses search function to search for 
 * element in array, returns element if found and NULL
 * if not found
 *
 */

void *findElement(SET *sp, void *elt){

	assert(sp && elt);
	
	bool found = false;
	int i = search(sp, elt, &found);
	if(found) return sp->elts[i];
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

void *getElements(SET *sp){

	assert(sp);
	void **elts;
	elts = malloc(sizeof(void*)*(sp->count));
	assert(elts);
	int eCount = 0;

	int i;
	for(i = 0; i < sp->length; i++){

		if(sp->flags[i] == 'F'){
			elts[eCount++] = sp->elts[i];
		}
	}

	return elts;


}
