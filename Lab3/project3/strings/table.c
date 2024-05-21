#include "set.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct set{

	char **elts;
	int length;
	int count;
	char *flags;
};



/* String Hash
 *
 * Complexity: O(n) (for string length n)
 *
 * Description: Creates a hash key for a string 
 * passed into function, returns hash key
 *
 */

unsigned strhash(char *s){

	unsigned hash = 0;
	while(*s != '\0') hash = 31 * hash * *s ++;
	return hash;

}


/* Search
 *
 * Complexity:
 * 	Worst Case: O(n)
 * 	Average Case: O(1)
 *
 * Description: Searches set passed into function
 * looking for element elt passed into function, modifies
 * boolean found passed into function based on whether or
 * not it was located, returns address of elt if found
 *
 */

static int search(SET *sp, char *elt, bool *found){

	int dkey;
	bool foundD = false;
	unsigned key = strhash(elt);
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

		else if (strcmp(sp->elts[loc], elt) == 0){

			*found = true;
			return loc;
	
		}
		

	}
	*found = false;
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
	sp->flags = malloc(sizeof(char) * maxElts);
	assert(sp->elts);
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

	int i;

	assert(sp != NULL);
	
	for(i = 0; i < sp->length; i++){

		if(sp->flags[i] == 'F') free(sp->elts[i]);

	}
	free(sp->flags);
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

void addElement(SET *sp, char *elt){

	bool found = false;
	int locn;

	assert(elt && sp);
	assert(sp->count < sp->length);
	locn = search(sp, elt, &found);

	if(!found){
		char *copy;
		copy = strdup(elt);
		assert(copy);
		sp->elts[locn] = copy;
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

void removeElement(SET *sp, char *elt){

	bool found;
	int key = search(sp, elt, &found);

	if(found){
		free(sp->elts[key]);
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

char *findElement(SET *sp, char *elt){
	
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

char **getElements(SET *sp){


	char **elts;
	elts = malloc(sizeof(char*) * sp->count);
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
