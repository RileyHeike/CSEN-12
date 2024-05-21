/*
 * File: pqueue.c
 *
 * Author: Riley Heike
 *
 * Date: 3/1/2023
 *
 * Description: creates priority queue using struct pqueue
 * with functions such as addEntry, removeEntry, createQueue,
 * numEntires, etc.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pqueue.h"

#define p(x) (((x)-1)/2)
#define l(x) ((x)*2+1)
#define r(x) ((x)*2+2)
#define START_LENGTH 10;

typedef struct pqueue {

	int count;
	int length;
	void **data;
	int (*compare)();

}PQ;

/*
 * Create Queue
 *
 * Runtime Complexity: O(1)
 *
 * Description: Creates priority queue using struct pqueue
 * and initializes count, length, data, (*compare)
 *
 */

PQ *createQueue(int (*compare)()){

	assert(compare != NULL);

	PQ *pq;
	pq = malloc(sizeof(PQ));
	assert(pq);
	pq->compare = compare;
	pq->length = START_LENGTH;
	pq->count = 0;
	pq->data = malloc(sizeof(void *)* pq->length);
	assert(pq->data);
	return pq;

}


/*
 * Destroy Queue
 *
 * Runtime Complexity: O(1)
 *
 * Description: Destroys queue by freeing data and then 
 * freeing rest of queue
 *
 */


void destroyQueue(PQ *pq){

	assert(pq);
	free(pq->data);
	free(pq);

}


/*
 * Num Entries
 *
 * Runtime Complexity: O(1)
 *
 * Description: Returns number of elements in the queue
 *
 */

int numEntries(PQ *pq){

	assert(pq);
	return pq->count;

}


/*
 * Add Entry
 *
 * Runtime Complexity: O(log n)
 *
 * Description: Adds entry to the queue and re-sizes if necessary
 *
 */

void addEntry(PQ *pq, void *entry){

	assert(pq && entry);

	if(pq->length == pq->count){

		pq->length *= 2;
		pq->data = realloc(pq->data, sizeof(void *)* pq->length);
		assert(pq->data);

	}

	int i = pq->count ++;
	while(i > 0 && (*pq->compare)(entry, pq->data[p(i)]) < 0){

		pq->data[i] = pq->data[p(i)];
		i = p(i);

	}

	pq->data[i] = entry;

}


/*
 * Remove Entry
 *
 * Runtime Complexity: O(log n)
 *
 * Description: Removes entry at top of priority queue and 
 * re-adjusts
 *
 */

void *removeEntry(PQ *pq){

	assert(pq->count > 0 && pq);
	void *root = pq->data[0];

	pq->data[0] = pq->data[pq->count-1];
	pq->count--;

	int i = 0;
	while(l(i) < pq->count){

		int cMin;

		if(r(i) < pq->count && pq->compare(pq->data[r(i)], pq->data[l(i)]) < 0){

			cMin = r(i);

		}
		else cMin = l(i);

		if(pq->compare(pq->data[i], pq->data[cMin]) >= 0){

			PQ *temp = pq->data[cMin];	
			pq->data[cMin] = pq->data[i];
			pq->data[i] = temp;
			i = cMin;
	
		}
		else break;

	}
	
	return root;

}

