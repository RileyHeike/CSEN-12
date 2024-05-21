/*
 *File:		WordCounter.c
 *
 *Name: 	Riley Heike
 *
 *Date: 	1/11/23
 *
 *
 *Description:	Program reads text from file and
 *		returns the word count of the file
 *
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_WORD_LENGTH 30

/* 	Main (only function) 
 *
 *	Opens file, uses fscanf to store each word
 *	in character array of length MAX_WORD_LENGTH
 *	and counts number of words, prints count
 *
 * */

int main(int argc, char *argu[]){

	if(argc != 2) return;

	FILE *info;
	int count = 0;
	char word[MAX_WORD_LENGTH];

	if((info = fopen(argu[1], "r")) == NULL){
		printf("Cannot open file\n");
		return;
	}

	while(fscanf(info, "%s", &word) != EOF){
		count++;
	}

	fclose(info);
	printf("%d total words\n", count);

}
