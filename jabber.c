#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>

int bit_len = 0; // keep track of the bit-length
int index_count = 0; // keep track of overall index

// creating my own power function because the STL uses double's
int Pow(int x, int n){
	
	int number = 1;
	
	for(int i = 0; i < n; ++i){
		number *= x;
	}
	return number;
}

// This struct is used to store the various indexes of the binary
struct b_tree {
	
	int index;
	struct b_tree * right, * left;
};

typedef struct b_tree node; // use this to create other node objects

// insert puts a new node into the tree, if no tree one will be created
void insert(node * head, int bit){

	// increment bit_length as 2^bit_length 
        if(index_count > Pow(2, bit_len)){
                ++bit_len;
        }

	// bit_len of 0 obviously means it's the first bit (no pattern)
	if(bit_len == 0){
		node * temp_node = NULL;
		temp_node = (node *)malloc(sizeof(node));
		temp_node->left = temp_node->right = NULL;
		temp_node->index = index_count;
		++index_count; // always increment index
		head = temp_node;
		printf("Pattern at index %d: 0\n", head->index); 
	}
	// have a while loop here that terminates at largest known pattern
	else if(bit == 1){ 
		if(head->right != NULL){ 	
			head = head->right;
			head->index = index_count;
			++index_count;
		} else if(head->right == NULL){
			node * new_node = head->right;
			new_node->index = index_count;
			++index_count;
		}
	} else if(bit == 0){
		if(head->left != NULL){ 
			head = head->left;
			head->index = index_count;
			++index_count;
		} else if(head->left == NULL){
			node * new_node = head->left;
			new_node->index = index_count;
			++index_count;
		}
	}
}

// should we make a print function? or print as we add ^^?

// jabber reads in bits from file then puts it into the binary tree/table
void jabber( FILE * inputFile, FILE * outputFile ){
	
	node * top_node;
	int bit = 0;
	
	while( (bit = fgetc(inputFile)) != EOF){
		insert(top_node, bit);
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

