#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define TABLE_LEN 26

typedef struct Symbol {
	int Address; 
	int SourceLineNumber; 
	struct Symbol * next; 
	char name[7];
} Symbol;

Symbol *Hashes[TABLE_LEN];

void hash_table(){
	for(int i=0; i<TABLE_LEN; i++) {
		Hashes[i] = NULL;
	}
}

int hash(char* name){
	int hash_value = 0;

  hash_value = name[0]-65;

	return hash_value;
}

void insert(Symbol* symb, int address){
  if (symb==NULL) {
  }

  int index = hash(symb->name);
	symb->next = Hashes[index];
	Hashes[index] = symb;
}

int duplicates(char *name) {
  int counter = 0;
  int index = hash(name);
  Symbol *Current = Hashes[index];

  while(Current!=NULL) {
    if(strcmp(Current->name, name) == 0){
      counter++;
    }
	  Current = Current->next;
  }
  return counter;
}

int strlength(char *input){
  int length = strlen(input);
  int counter = 0;

  for(int i=0; i<length; i++){
    if(input[i] <= 'Z' && input[i] >= 'A')
      counter++;
  }
  return counter;
}

int lowcheck(char *input){
  int length = strlen(input);
  int counter = 0;

  for(int i=0; i<length; i++){
    if(input[i] <= 'z' && input[i] >= 'a')
      counter++;
  }
  return counter;
}

int constcheck(char* constant){
  int len = strlen(constant);
  int size = 0;

  if(constant[0] == 'C'){
    for(int i=1; i<len; i++){
      if(constant[i] <= 'Z' && constant[i] >= 'A')
        size++;
    }
  }
  if(constant[0] == 'X'){
    for(int i=1; i<len; i++){
      if(constant[i] <= 'Z' && constant[i] >= 'A')
        size++;
      else if(constant[i] <= '9' && constant[i] >= '0')
        size++;
    }         
    size /= 2; 
  }
  
  return size;
}

int main(int argc, char *argv[]) {

    FILE* inputFile;

    inputFile = fopen("test.txt", "r");

    if (!inputFile) {
        printf("\nnASSEMBLY ERROR: file could not be opened for reading.\nexiting...\n1");
        return 1;
    }

    hash_table();

    char line[1024];
    char hexval[5];
    int linectr = 0;
    int symctr = 0;
    int address = 0;
    Symbol *Temp;
    while (fgets(line, 1024, inputFile)) {
      int length = strlen(line);
      
      char * temp[3];
        if (length > 0) {
          if (line[0] == 35){}
          else if (line[0] == '\n'){}
          else {  
            char *token = strtok(line, " \t");
            int strctr = 0;
            while (token) {  
                  temp[strctr] = token;
                  token = strtok(NULL, " \t");
                  strctr++;
            }
            
            linectr++;
            Temp = malloc(sizeof(token+1));
            if(strctr >= 3) {
              if (strstr(temp[0], "$") != NULL || strstr(temp[0], "!") != NULL || strstr(temp[0], "=") != NULL || \
                      strstr(temp[0], "+") != NULL || strstr(temp[0], "-") != NULL || strstr(temp[0], "(") != NULL || \
                          strstr(temp[0], ")") != NULL || strstr(temp[0], "@") != NULL) {
                    printf("\nASSEMBLY ERROR \nline %d: symbols cannot contain: spaces, $, !, =, +, - , (,  ), or @ \nexiting...\n", symctr+1);
                    return 1;
              }
              
              if (strstr(temp[0], "START") != NULL ||strstr(temp[0], "END") != NULL ||strstr(temp[0], "BYTE") != NULL || \
                    strstr(temp[0], "WORD") != NULL ||strstr(temp[0], "RESB") != NULL ||strstr(temp[0], "RESW") != NULL || \
                        strstr(temp[0], "EXPORTS") != NULL) {
                if (strcmp(temp[0], temp[1]) == 0) {
                  printf("\nASSEMBLY ERROR \nline %d: Symbol defined with name that matches an assembler directive:\n%s and %s\nexiting...\n", symctr+1, \
                  temp[0], temp[1]);
                  return 1;   	      
                }
              }

              if (strlength(temp[0]) > 6) {
                printf("\nASSEMBLY ERROR \nline %d: Symbol must be less than 7 characters:\n%s\nexiting...\n", symctr+1, temp[0]);
                return 1;   	  
              }

              if (lowcheck(temp[0]) > 0) {
                printf("\nASSEMBLY ERROR \nline %d: Symbol cannot have [a-z]:\n%s\nexiting...", symctr+1, temp[0]);
                return 1;  
              }
              
              if(strstr(temp[1], "START") && linectr == 1) {
                symctr++;
                char *rest;
                address = (int)strtol(temp[2], &rest, 16);

                char Name[7];
                strcpy(Name, temp[0]);
                Temp->Address = address;
                Temp->SourceLineNumber = linectr;
                strcpy(Temp->name, Name);

                insert(Temp, address);

                if(duplicates(Name) > 1){
                  printf("\nASSEMBLY ERROR \nline %d: Duplicate Symbol:\n%s\nexiting...\n", symctr+1, Name);
                  return 1;  
                }

                printf("%s\t%x\n", temp[0], Temp->Address);
              }
              
              else if (linectr == 1) {
                symctr++;
                char Name[7];
                strcpy(Name, temp[0]);
                Temp->Address = address;
                Temp->SourceLineNumber = linectr;
                strcpy(Temp->name, Name);
                insert(Temp, address);

                if(duplicates(Name) > 1){
                  printf("\nASSEMBLY ERROR \nline %d: Duplicate Symbol:\n%s\nexiting...\n", symctr+1, Name);
                  return 1;  
                }

                printf("%s\t%x\n", temp[0], Temp->Address);
                address += 3;
              }
              else {               
                symctr++;

                char Name[7];
                strcpy(Name, temp[0]);
                Temp->Address = address;
                Temp->SourceLineNumber = linectr;
                strcpy(Temp->name, Name);
                insert(Temp, address);
                
                if(duplicates(Name) > 1){
                  printf("\nASSEMBLY ERROR \nline %d: Duplicate Symbol:\n%s\n\n", symctr+1, Name); 
                  return 1;
                }

                printf("%s\t%x\n", temp[0], Temp->Address);

                char *other;
                int amount = (int)strtol(temp[2], &other, 10);
                if(strstr(temp[1], "WORD") != NULL){
                  address += 3;
                }
                else if(strstr(temp[1], "RESW")!= NULL){
                  address += 3*amount;
                }
                else if(strstr(temp[1], "RESB")!= NULL){
                  address += amount;
                }
                else if(strstr(temp[1], "BYTE")!= NULL){
                  amount = constcheck(temp[2]);
                  address += amount;
                }
                else {
                  address += 3;
                }           
              }

            }
            else if(strctr == 2){
              char *other;
              int amount = (int)strtol(temp[1], &other, 16);
              if(strstr(temp[0], "WORD")!= NULL){
                address += 3;
              }
              else if(strstr(temp[0], "RESW")!= NULL){
                address += 3*amount;
              }
              else if(strstr(temp[0], "RESB")!= NULL){
                address += amount;
              }
              else if(strstr(temp[0], "BYTE")!= NULL){
                amount = constcheck(temp[1]);
                address += amount;
              }
              else {
                address += 3;
              }      

              Temp = malloc(sizeof(token+1));
              Temp->SourceLineNumber = linectr;
            }
            else {
              address += 3;
              Temp = malloc(sizeof(token+1));
              Temp->SourceLineNumber = linectr;
            }

          for (int i=0; i<2; i++)
            temp[i] = 0;
        }
      }  
    }
    fclose(inputFile);

    return 0;
}
