#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>

int bit_len = 0; // keep track of the bit-length
int index_count = 0; // keep track of overall index
int bit_counter = 0; // debug method to make sure I'm getting throught the entire file, 
// wherever you read in another bit, increment this and print it out

// creating my own power function because the STL uses double's
int Pow(int base, int exp){
	
	int number = 1;
	
	for(int i = 0; i < exp; ++i){
		number *= base;
	}
	return number;
}

// This struct is used to store the various indexes of the binary
struct b_tree {
	
	int index;
        struct b_tree * right, * left;
};

typedef struct b_tree node; // node object


void printToBinary(int integer, int bitLen, FILE *outputFile){
  while(bitLen > 0 ){
    fprintf(outputFile, "%d\n", (integer>>bitLen)&1);
    --bitLen;
  }
  return;
}


// insert puts a new node into the tree, if no tree one will be created
void insert(node * head, char bit, FILE * inputFile, FILE * outputFile){

	//first case
	if(index_count == 0){
		node * temp_node = NULL;
		temp_node = (node *)malloc(sizeof(node));
		temp_node->left = temp_node->right = NULL;
		temp_node->index = index_count;
		++index_count; // always increment index
		head = temp_node;

		if(bit == '1'){
			node * new_node = NULL;
			new_node = (node *)malloc(sizeof(node));
			new_node->left = new_node->right = NULL;
			new_node->index = index_count;
			++index_count;	
			head->left = new_node;
		} else if(bit == '0'){	
			node * new_node = NULL;
			new_node = (node *)malloc(sizeof(node));
			new_node->left = new_node->right = NULL;
			new_node->index = index_count;
			++index_count;
			head->left = new_node;
		}
			 
	}
	// have a while loop here that terminates at largest known pattern
	while((bit = fgetc(inputFile)) != EOF){			
		if(bit == '\n') break; // without this the while loop doesn't terminate
	
		printf("bit %i: %c\n", bit_counter, bit);
	        ++bit_counter;

		// increment bit_length as 2^bit_length
		if(index_count > Pow(2, bit_len)){
			++bit_len;
		}

		bool done = false;
		while(done == false){ //each new pattern
			if(bit == '1'){ 
				if(head->right){ 
					head = head->right;
					bit = fgetc(inputFile);
	
					printf("bit %i: %c\n", bit_counter, bit);
				        ++bit_counter;

				} else if(!(head->right)){ // if pattern ends, set the bit
					node * new_node = NULL;
					new_node = (node *)malloc(sizeof(node));		
					new_node->left = new_node->right = NULL;
					new_node->index = index_count;
					++index_count;
					head->right = new_node;
					done = true;
				}
			} else if(bit == '0'){
				if(head->left){ 
					head = head->left;
					bit = fgetc(inputFile);

					printf("bit %i: %c\n", bit_counter, bit);
				        ++bit_counter;

				} else if(!(head->left)){ // if pattern ends, set the bit
				        int b = fgetc(inputFile);
				        printToBinary(head->index, bit_len, outputFile);
					fprintf(outputFile, "%d\n", b);
				        node * new_node = NULL;	
					new_node = (node *)malloc(sizeof(node));
					new_node->left = new_node->right = NULL;
					new_node->index = index_count;
					++index_count;
					head->left = new_node;
					done = true;
				}
			}
		}
	}
	printf("EOF\n");
}

// jabber reads in bits from file then puts it into the binary tree/table
void jabber( FILE * inputFile, FILE * outputFile ){
	
	node * top_node;
	char bit;
	bit = fgetc(inputFile);
	printf("bit %i: %c\n", bit_counter, bit);
	++bit_counter;
	insert(top_node, bit, inputFile, outputFile);
	// we might think about combining the jabber and insert function, this doesn't 
	// really do anything too crazy that can't quickly be added to insert
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

