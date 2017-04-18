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
void insert(node * head, int index){
	node * temp = NULL;
	if(head == NULL){
		temp = (node *)malloc(sizeof(node));
		temp->left = temp->right = NULL;
		temp->index = index;
		head = temp;
		return; // breaks out of function
	}
}

void jabber( FILE * inputfile, FILE * outputFile ){
	/*
	
	read in all of file, then begin going through	

	*/

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
        //jabber(ifp, ofp);
        end_time = clock();
        time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
        fprintf(stderr, "Time usage = %17.13f\n", time_used);

        fclose(ifp);
        fclose(ofp);

        return 0;
}

















