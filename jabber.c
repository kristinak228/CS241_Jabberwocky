#include <stdio.h>
#include <stdlib.h>



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

void Print(){
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


int main( int argc, char *argv[] ){

  head = NULL;
  char a = '0';
  char a2 = '1';
  char a3[2] = {'1', '0'};
  char *p1 = &a;
  char *p2 = &a2;
  char *p3 = a3;

  Insert_Entry(0, p1); Print();
  Insert_Entry(1, p2); Print();
  Insert_Entry(2, p3); Print();


  return 0;
}
