#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>


int bit_counter = 0;
int index_count = 0;
int bit_len = 0;

typedef struct Table_Entry{
  
  int index;
  char *pattern;
  struct Table_Entry *next;
  struct Table_Entry *previous;
  

}Table_Entry;

Table_Entry *head;

Table_Entry *New_Entry( int index, char *pattern){
  
  Table_Entry *new_Entry = (Table_Entry *)malloc(sizeof(Table_Entry));
  new_Entry->index = index;
  new_Entry->pattern = pattern;
  new_Entry->previous = NULL;
  new_Entry->next = NULL;
  return new_Entry;

}

void Insert_Entry( int index, char *pattern){
  Table_Entry *temp = head;
  Table_Entry *new_Entry = New_Entry( index, pattern );
  if(head == NULL){
    head = new_Entry;
    return;
  }
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = new_Entry;
  new_Entry->previous = temp;

}

int Pow(int base, int exp){

  int number = 1;

  for(int i = 0; i < exp; ++i){
    number *= base;
  }
  return number;
}


void Print_Table(){
  Table_Entry *temp = head;
  printf("Top of Table: \n");
  while(temp != NULL){
    printf("%d", temp->index);
    printf(" | ");
    printf("%s\n" , temp->pattern);
    temp = temp->next;
  }
  printf("\n");
}

int binaryToDecimal(char *str){ 
  //char *binstring = "10000001"; //binary for 129
  int decimal = 0;
  int stringpos;

  for (stringpos=strlen(str)-1; stringpos>=0; stringpos--) {
    decimal = decimal<<1;    
    if (str[stringpos]=='1'){
      decimal += 1;
    }
  }

  //printf("The binary string %s is equal to %u in decimal.\n", str, decimal);
  return decimal;
}

//#define SRCH_PRE "\x1b[34m"
//#define SRCH_FAIL "\x1b[31m"
//#define SRCH_GOOD "\x1b[32m"
//#define RST "\x1b[m"
int search(int x)
{
  Table_Entry* current = head;  // Initialize current
  int iter = 0;
  //printf(SRCH_PRE);
  //printf("SEARCH(%d):\n", x);
  while (current != NULL)
    {
      //printf("SEARCH: current %p, iter %d, current->index %d:", current, iter, current->index);
      if (current->index == x){
	//printf(SRCH_GOOD "SUCCESS\n" RST);
	return 1;
      }
      //printf(SRCH_FAIL "FAILED\n" SRCH_PRE);
      iter++;
      current = current->next;
    }
  //printf("SEARCH END (current == %p), " SRCH_FAIL "FAILED\n" RST, current);
  return 0;
}

char* returnPattern(int x){
  Table_Entry* current = head;  // Initialize current
  while (current != NULL){
    if (current->index == x){
      return current->pattern;
    }
      current = current->next;
    }
  return 0;
}
  

char* concat(const char *s1, const char *s2)
{
  char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}


bool fpeek(FILE *stream){
  int c;
  c = fgetc(stream);
  if((c != '\n') || (c != EOF)){
    ungetc(c, stream);
    return true;
  }
  ungetc(c, stream);
  return false;
}


int printToBinary( char * a){
  return 0;
}
//Print Encoding


//#define OUT_PRE "\x1b[1;33m"
/* W O C K Y */
void wocky(FILE * inputFile, FILE * outputFile){
  char bit[2] = "\0";
  bit[0] = fgetc(inputFile);
  printf("bit1 %i: %c\n", bit_counter, bit[0]);
  ++bit_counter;
  //first case
  if(index_count == 0){
    Table_Entry *temp_entry = New_Entry(index_count, "");
    ++index_count;
    head = temp_entry;
    
    if(bit[0] == '1'){
      fprintf(outputFile, /*"First Case:*/ "%c", bit[0]);
      Table_Entry * new_entry = New_Entry(index_count, bit/*append(bit, '\0')*/);
      new_entry->previous = head;
      head->next = new_entry;
      ++index_count;

    }else if(bit[0] == '0'){
      fprintf(outputFile, /*"First Case:*/ "%c", bit[0]);
      Table_Entry * new_entry = New_Entry(index_count, bit/*append(bit, '\0')*/);
      new_entry->previous = head;
      head->next = new_entry;
      ++index_count;

    }
  }  

  //Print_Table();

  int numBits = 0;
  int searchResult;
  int hitEnd;
  while(!feof(inputFile)){
    char bits[2] = "\0";
    bits[0] = fgetc(inputFile);
    if(bits[0] == '\n' || bits[0] == EOF) break;
    printf("bit2 %i: %c\n", bit_counter, bits[0]);
    ++bit_counter;
    //Other Cases
    if(index_count > Pow(2, bit_len)){
      ++bit_len;
    }
    char *oldBits;
    char *newBits = bits;
    while(searchResult = search(binaryToDecimal(newBits)) && numBits <= bit_len ){
      oldBits = newBits;
      if(fpeek(inputFile)){
	printf("\t\tWOCKY: if\n");
	char newBit[2] = "\0";
	newBit[0] = fgetc(inputFile);
	numBits ++;
	if(newBit[0] == '\n' || newBit[0] == EOF) {
	  hitEnd = 1;
	  break;
	}
	printf("\t\tWOCKY: bit3 %i: %c\n", bit_counter, newBit[0]);
	++bit_counter;
	newBits = concat(newBit, oldBits);
      }else{
	printf("\t\tWOCKY: else\n");
	break;
      }
    }
    if(!searchResult) {
      printf("\tWOCKY: endwhile(search failed)\n");
    }
    //print pattern at binary to decimal of oldBits plus last character in newBits
    fprintf( outputFile, /*"Pattern:*/ "%s", returnPattern(binaryToDecimal(oldBits)));
    //printf(OUT_PRE "PATTERN (at %d): %s\n" RST, binaryToDecimal(oldBits), returnPattern(binaryToDecimal(oldBits)));
    if(!hitEnd) {
      fprintf( outputFile, /*"Bit: */ "%c", newBits[strlen(newBits)-1]);
      //printf(OUT_PRE "BIT: %c\n" RST, newBits[strlen(newBits) - 1]);
    }
    //Make new node with new_bits
    Insert_Entry( index_count, newBits );
    // increment index_count
    index_count++;
  }
  //printf("bit_len  = %i\n", bit_len);

}



int main( int argc, char * argv[] ) {

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
	
	//char *str = "111";
	//printf( "%i\n", binaryToDecimal(str));

	begin_time = clock();
	wocky(ifp, ofp);
	fprintf(ofp, "\n");
	end_time = clock();
	time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
	fprintf(stderr, "Time usage = %17.13f\n", time_used);

  	fclose(ifp);
	fclose(ofp);
	
	return 0;
}
