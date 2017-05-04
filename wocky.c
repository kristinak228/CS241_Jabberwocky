#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>


#include <stdio.h>
#include <stdlib.h>



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


int search(int x)
{
  Table_Entry* current = head;  // Initialize current
  while (current != NULL)
    {
      if (current->index == x){
	return x;
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


int fpeek(FILE *stream){
  int c;

  c = fgetc(stream);
  ungetc(c, stream);

  return c;
}


int printToBinary( char * a){
  return 0;
}
//Print Encoding



/* W O C K Y */
void wocky(FILE * inputFile, FILE * outputFile){
  char bit[2] = "\0";
  bit[0] = fgetc(inputFile);
  printf("bit1 %i: %c\n", bit_counter, bit[0]);
  ++bit_counter;
  //first case
  if(index_count == 0){
    Table_Entry *temp_entry = New_Entry(index_count, NULL);
    ++index_count;
    head = temp_entry;
    
    if(bit[0] == '1'){
      fprintf(outputFile, "First Case: %c\n", bit[0]);
      Table_Entry * new_entry = New_Entry(index_count, bit/*append(bit, '\0')*/);
      new_entry->previous = head;
      head->next = new_entry;
      ++index_count;

    }else if(bit[0] == '0'){
      fprintf(outputFile, "First Case: %c\n", bit[0]);
      Table_Entry * new_entry = New_Entry(index_count, bit/*append(bit, '\0')*/);
      new_entry->previous = head;
      head->next = new_entry;
      ++index_count;

    }
  }  

  Print_Table();

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
    while(search(binaryToDecimal(newBits))){
      oldBits = newBits;
      if(fpeek(inputFile)){
	char newBit[2] = "\0";
	newBit[0] = fgetc(inputFile);
	printf("bit2 %i: %c\n", bit_counter, newBit[0]);
	++bit_counter;
	newBits = concat(oldBits, newBit);
      }else{
	break;
      }
    }
    //print pattern at binary to decimal of oldBits plus last character in newBits
    //Make new node with new_bits
    // increment index_count
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
	end_time = clock();
	time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
	fprintf(stderr, "Time usage = %17.13f\n", time_used);

  	fclose(ifp);
	fclose(ofp);
	
	return 0;
}
