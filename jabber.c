#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

/*
This struct is used to store the various indexes of the binary
*/
struct b_tree {

	int index;
	
	struct b_tree * right, * left;
};

typedef struct b_tree node; // create node


// insert puts a new node into the tree, if no tree one will be created
// head is the top of the tree, index is the next index to be added
void insert(node * head, int index){
	node * temp = NULL;

	// if tree is empty
	if(head == NULL){
	// initialize first row to pattern 0, index 0, bit 0,
	// then head will never be NULL
		temp = (node *)malloc(sizeof(node));
		temp->left = temp->right = NULL;
		temp->index = index;
		head = temp;
	}
	else{ //if tree is not empty 

	/*
	you must go down the tree, left for 0 bit, right for 1 bit
	*/
	
	{
	
}

/* 
you need a table to hold the pattern, index, and bit-length, should I use
a 3 dimensional array / what else is there?
*/

// jabber reads in bits from file then puts it into the binary tree/table
void jabber( FILE * inputfile, FILE * outputFile ){
	
	char ch = NULL;
	while ( (ch = fgetc(inputFile)) != EOF){
		// do you test what pattern you have an read in that way
		// or read in first ch then see if it matches a pattern?

		/* 
		once pattern is read you add the pattern and bit into 
		next pattern, increment index, increment bit-length by
		powers of two
		*/
	}
}


int main( int argc, char * argv[] ){

        FILE *ifp, *ofp;
        clock_t begin_time, end_time;
        double time_used;

        if(argc < 3){
                fprintf(stderr, "Not enough arguments\n");
        }
        if(!(ifp = fopen(argv[1], "r"))){
                fprintf(stderr, "Cannot open file %s\n", argv[1]);
        }
        if(!(ofp = fopen(argv[2], "w"))){
                fprintf(stderr, "Cannot open file %s\n", argv[2]);
        }

        begin_time = clock();
        jabber(ifp, ofp);
        end_time = clock();
        time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
        fprintf(stderr, "Time usage = %17.13f\n", time_used);

        fclose(ifp);
        fclose(ofp);

        return 0;
}

















