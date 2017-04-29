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


char * append(char * string1, char * string2)
{
  char * result = NULL;
  asprintf(&result, "%s%s", string1, string2);
  return result;
}

//Print Encoding


/* W O C K Y */
void wocky(FILE * inputFile, FILE * outputFile){
  char bit;
  bit = fgetc(inputFile);
  printf("bit1 %i: %c\n", bit_counter, bit);
  ++bit_counter;
  //first case
  if(index_count == 0){
    Table_Entry *temp_entry = New_Entry(index_count, NULL);
    ++index_count;
    head = temp_entry;
    
    if(bit == '1'){
      fprintf(outputFile, "First Case: %c\n", bit);
      Table_Entry * new_entry = New_Entry(index_count, &bit/*append(bit, '\0')*/);
      new_entry->previous = head;
      head->next = new_entry;
      ++index_count;

    }else if(bit == '0'){
      fprintf(outputFile, "First Case: %c\n", bit);
      Table_Entry * new_entry = New_Entry(index_count, &bit/*append(bit, '\0')*/);
      new_entry->previous = head;
      head->next = new_entry;
      ++index_count;

    }
  }
  
  Print_Table();

  while(!feof(inputFile)){
    bit = fgetc(inputFile);
    if(bit == '\n' || bit == EOF) break;
    printf("bit2 %i: %c\n", bit_counter, bit);
    ++bit_counter;
    //Other Cases

  }
  //printf("bit_len  = %i\n", bit_len);

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
	wocky(ifp, ofp);
	end_time = clock();
	time_used = (double)(end_time - begin_time)/CLOCKS_PER_SEC;
	fprintf(stderr, "Time usage = %17.13f\n", time_used);

  	fclose(ifp);
	fclose(ofp);
	
	return 0;
}
