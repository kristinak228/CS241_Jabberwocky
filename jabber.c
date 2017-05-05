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
  //fprintf(outputFile, "int = %i\n", integer);
  //fprintf(outputFile, "bit_len = %i\n", bitLen);
  bitLen--;
  while(bitLen >=  0){
    //fprintf(outputFile, "Index to Binary: ");
    fprintf(outputFile, "%d", (integer>>bitLen)&1);
    --bitLen;
  }
  return;
}

void jabber(FILE * inputFile, FILE * outputFile){
  node * head;
  char bit;
  bit = fgetc(inputFile);
  printf("bit1 %i: %c\n", bit_counter, bit);
  ++bit_counter;
  
  //First Case
  if(index_count == 0){
    node * temp_node = NULL;
    temp_node = (node *)malloc(sizeof(node));
    temp_node->left = temp_node->right = NULL;
    temp_node->index = index_count;
    ++index_count; //always increment index
    head = temp_node;
    
    if(bit == '1'){
      fprintf(outputFile, /*"First Case: */"%c", bit);
      node * new_node = NULL;
      new_node = (node *)malloc(sizeof(node));
      new_node->left = new_node->right = NULL;
      new_node->index = index_count;
      ++index_count;
      head->right= new_node;
    }else if(bit == '0'){
      fprintf(outputFile, /*"First Case:*/ "%c", bit);
      node * new_node = NULL;
      new_node = (node *)malloc(sizeof(node));
      new_node->left = new_node->right = NULL;
      new_node->index = index_count;
      ++index_count;
      head->left = new_node;
    }
  }
  int passes = 1;
  node * temp_node;
  while(!feof(inputFile)){
    //int passes = 1;
    printf("pass = %i\n", passes);
    passes = passes + 1;;
    bit = fgetc(inputFile);
    
    if(bit == '\n' || bit == EOF) break;

    printf("bit2 %i: %c\n", bit_counter, bit);
    ++bit_counter;

    if(index_count > Pow(2, bit_len)){
      ++bit_len;
    }

    temp_node = head;

    bool done = false;
    while(done == false){ //each new pattern
      printf("temp_node indedx = %i\n", temp_node->index);
      if(bit == '\n' || bit == EOF) break;
      if(bit == '1'){
	
	if(temp_node->right){
	  temp_node = temp_node->right;
	  bit = fgetc(inputFile);
	  printf("bit3 %i: %c\n", bit_counter, bit);
	  printf("temp_node indedx = %i\n", temp_node->index);
     	  ++bit_counter;
	  
	}else if(!(temp_node->right)){
	  printToBinary(temp_node->index, bit_len, outputFile);
	  fprintf(outputFile, /*"bit = 1:*/ "%c", bit);
	  printf("temp_node indedx = %i\n", temp_node->index);
	  node * new_node = NULL;
	  new_node = (node *)malloc(sizeof(node));
	  new_node->left = new_node->right = NULL;
	  new_node->index = index_count;
	  ++index_count;
	  temp_node->right = new_node;
	  done = true;
	}
      }else if(bit == '0'){
	if(temp_node->left){
	  temp_node = temp_node->left;
	  bit = fgetc(inputFile);
	  printf("bit4 %i: %c\n", bit_counter, bit);
	  printf("temp_node indedx = %i\n", temp_node->index);
     	  ++bit_counter;

	}else if(!(temp_node->left)){
	  printToBinary(temp_node->index, bit_len, outputFile);
	  fprintf(outputFile, /*"bit = 0:*/ "%c", bit);
	  printf("temp_node indedx = %i\n", temp_node->index);
	  node * new_node = NULL;
	  new_node = (node *)malloc(sizeof(node));
	  new_node->left = new_node->right = NULL;
	  new_node->index = index_count;
	  ++index_count;
	  temp_node->left = new_node;
	  done = true;
	}
      }
    }
  }
  printf("temp_node indedx = %i\n", temp_node->index);
  printf("bit_len  = %i\n", bit_len);
  printToBinary(temp_node->index, bit_len, outputFile);

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
  fprintf(ofp, "\n");
  end_time = clock();
  time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
  fprintf(stderr, "Time usage = %17.13f\n", time_used);

  fclose(ifp);
  fclose(ofp);

  return 0;
}

