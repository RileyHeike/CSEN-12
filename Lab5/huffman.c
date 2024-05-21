
/*
 * File: huffman.c
 *
 * Author: Riley Heike
 *
 * Date: 3/8/2023
 *
 * Description: Creates huffman tree from input file
 *
 */

#include "pqueue.h"
#include "pack.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#define P ((i-1)/2)
#define R ((i*2)+1)
#define L ((i*2)+2)

struct node *createNode(){

	struct node *leaf = malloc(sizeof(struct node));
	assert(leaf);
	leaf->parent = NULL;
	leaf->count = 0;
	return leaf;

}


/*
 * Node Compare
 *
 * Runtime Complexity: O(1)
 *
 * Description: Compares two nodes pased into function
 * and returns -1, 0, or 1
 *
 */

int nodecmp(struct node *n1, struct node *n2){

	assert(n1 && n2);
	return (n1->count < n2->count ? -1 : (n1->count > n2->count));

}


/*
 * Depth
 *
 * Runtime Complexity: O(log n)
 *
 * Description: Returns height/depth of tree
 *
 */

int depth(struct node *n){

	assert(n);
	int h = 0;
	while(n != NULL){

		h++;
		n = n->parent;

	}

	return h;
}


/*
 * mkNode
 *
 * Runtime Complexity: O(1)
 *
 * Description: Creates a new node and sets itself as 
 * parent of nodes passed into function
 *
 */

struct node *mkNode(int data, struct node *l, struct node *r){

	assert(l && r);
	struct node *new = malloc(sizeof(struct node));
	assert(new);
	new->count = data;
	l->parent = new;
	r->parent = new;
	return new;

}


/*
 * Main
 *
 * Runtime Complexity: O(nlogn)
 *
 * Description: Reads input file and constructs huffman tree
 * using all previously defined functions, compresses using pack()
 *
 */

int main(int argc, char *argv[]){

	FILE *input;
	struct node *leaves[257] = {NULL};
	PQ *pq;

	if(argc < 2){
		
		return 0;
		printf("Incorrect Argument");

	}

	char *infp = argv[1];
	char *outfp = argv[2];

	input = fopen(infp, "r");

	if(input == NULL){
		
		return 0;
		printf("Cannot open file");
	
	}

	int c;

	while((c = fgetc(input)) != EOF){

		if(leaves[c] == NULL) leaves[c] = createNode();
		leaves[c]->count++;

	}

	
	leaves[256] = createNode();
	pq = createQueue(nodecmp);


	int i;
	for(i = 0; i<257; i++){

		if(leaves[i] != NULL) addEntry(pq, leaves[i]);

	}


	struct node *i1, *i2;

	while(numEntries(pq) > 1){

		i1 = removeEntry(pq);
		i2 = removeEntry(pq);

		int total = i1->count + i2->count;
		struct node *combo = mkNode(total, i1, i2);
		addEntry(pq, combo);		

	}


	for(c = 0; c < 257; c++){

		if(leaves[c] != NULL){

			int length = depth(leaves[c]);
			int count = leaves[c]->count;

			if(isprint(c)){

				printf("'%c' : %d x %d bits = %d bits\n", c, count, length, count*length);

			}
			else printf("%o: %d x %d bits = %d bits\n", c, count, length, count*length);
		}


	}

	pack(infp, outfp, leaves);
	fclose(input);
	return 0;


}
