#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

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
      else if(constant[i] != 39) {
	size = -1;
	break;
      }
    }
  }
  if(constant[0] == 'X'){
    for(int i=1; i<len; i++){
      if(constant[i] <= 'F' && constant[i] >= 'A')
        size++;
      else if(constant[i] <= '9' && constant[i] >= '0')
        size++;
      else if(constant[i] != 39) {
	size = -1;
	break;
      }
    }   
    if(size != -1){      
    	size /= 2; 
    }
  }
  return size;
}

char* removespace(char *input){
    char *output;
    output = malloc(sizeof(input));
    int i = 0, j = 0, len;

    len = strlen(input);
    while(input[i] != '\0'){
        if(input[i] != ' ') {
            output[j++] = input[i];
        }
        i++;
    }
    return output;
}

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("USAGE: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* inputFile;

    inputFile = fopen(argv[1], "r");

    if (!inputFile) {
        printf("\nASSEMBLY ERROR: file could not be opened for reading.\nexiting...\n1");
        return 1;
    }

    hash_table();

    char line[1024];
    char hexval[5];
    int linectr = 0;
    int symctr = 0;
    int address = 0;
    int startctr = 0;
    int endctr = 0;
    Symbol *Temp;
    while (fgets(line, 1024, inputFile)) {
      int length = strlen(line);
      
      char * temp[3];
        if (length > 0) {
          if (strstr(line, "#") != NULL) {}
          else if (line[0] == 10 || line[0] == 13){
            printf("\nASSEMBLY ERROR\nSIC file contains a blank line \nexiting...\n");
            return 1;
          }
          else {  
            char *token = strtok(line, " \t\n");
            int strctr = 0;
            while (token) {                    
                  temp[strctr] = removespace(token);
                  token = strtok(NULL, " \t\n");

                  if(strctr < 3 && *temp[strctr] <= 90 && *temp[strctr] >= 32){ 
                    strctr++;  
                  } 
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
	            if(*temp[0] <= '/' && *temp[0] >= '!'){
                    printf("\nASSEMBLY ERROR \nline %d: symbols must start with [A-Z]:\n%s\nexiting...\n", symctr+1, temp[0]);
                    return 1;
              }

              if (strstr(temp[0], "START") != NULL ||strstr(temp[0], "END") != NULL ||strstr(temp[0], "BYTE") != NULL || \
                    strstr(temp[0], "WORD") != NULL ||strstr(temp[0], "RESB") != NULL ||strstr(temp[0], "RESW") != NULL || \
                        strstr(temp[0], "EXPORTS") != NULL) {
                if (strcmp(temp[0], temp[1]) == 0) {
                  printf("\nASSEMBLY ERROR \nline %d: Symbol defined with name that matches an assembler directive:\n%s and %s\nexiting...\n", symctr+1, temp[0], temp[1]);
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

              if(strstr(temp[1], "START")){
                if(startctr==1){
                  printf("\nASSEMBLY ERROR \nline %d: Multiple start decl.\nexiting...", symctr+1);
                return 1;  
                }
              }

              if(strcmp(temp[1], "END") == 0){
                endctr++;
                if(endctr==2){
                  printf("\nASSEMBLY ERROR \nline %d: Multiple end decl.\nexiting...", symctr+1);
                return 1;  
                }
              }
              
              if(strstr(temp[1], "START") && linectr == 1) {
                startctr++;
                symctr++;
                char *rest;
                address = (int)strtol(temp[2], &rest, 16);

                if(address == 0 && *temp[2] != 48){
                  printf("\nASSEMBLY ERROR \nline %d: Invalid address:\n%s\nexiting...\n", symctr+1, temp[2]);
                  return 1;
                }

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

                if(Temp->Address > pow(2, 15)){
                  printf("\nASSEMBLY ERROR \nline %d: Memory Exceeded (> 8000):\n%X\nexiting...\n", symctr+1, Temp->Address);
                  return 1; 
                }
                else {
                  printf("%s\t%X\n", temp[0], Temp->Address);
                }
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

                if(Temp->Address > pow(2, 15)){
                  printf("\nASSEMBLY ERROR \nline %d: Memory Exceeded (> 8000):\n%X\nexiting...\n", symctr+1, Temp->Address);
                  return 1; 
                }
                else {
                  printf("%s\t%X\n", temp[0], Temp->Address);
                }
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

                if(Temp->Address > pow(2, 15)){
                  printf("\nASSEMBLY ERROR \nline %d: Memory Exceeded (> 8000):\n%X\nexiting...\n", symctr+1, Temp->Address);
                  return 1; 
                }
                else {
                  printf("%s\t%X\n", temp[0], Temp->Address);
                }
               
                char *other;
                int amount = (int)strtol(temp[2], &other, 10);
                if(strstr(temp[1], "WORD") != NULL){
                  int word = atoi(temp[2]);
                  if(word > pow(2, 23) || word < (-1 * pow(2, 23))){
                    printf("\nASSEMBLY ERROR \nline %d: Constant exceeds WORD size:\n%s\n\n", symctr+1, temp[2]); 
                  return 1;
                  }
                  else {
                    address += 3;
                  }
                }
                else if(strstr(temp[1], "RESW")!= NULL){
                  address += 3*amount;
                }
                else if(strstr(temp[1], "RESB")!= NULL){
                  address += amount;
                }
                else if(strstr(temp[1], "BYTE")!= NULL){
                  amount = constcheck(temp[2]);
                if(amount == -1) {
		              printf("\nASSEMBLY ERROR \nline %d: Invalid BYTE constant:\n%s\n\n", symctr+1, temp[2]); 
		              return 1;
		            } 
		            address += amount;
                }
                else {
                  address += 3;
                }           
              }

            }
            else if(strctr == 2){
              if(strstr(temp[0], "START")){
                if(startctr==1){
                  printf("\nASSEMBLY ERROR \nline %d: Multiple start decl.\nexiting...", symctr+1);
                return 1;  
                }
              }

              if(strcmp(temp[0], "END") == 0){
                endctr++;
                if(endctr==2){
                  printf("\nASSEMBLY ERROR \nline %d: Multiple end decl.\nexiting...", symctr+1);
                return 1;  
                }
              }
              char *other;
              int amount = (int)strtol(temp[1], &other, 16);
              if(strstr(temp[0], "WORD")!= NULL){
                int word = atoi(temp[1]);
                  if(word > pow(2, 23) || word < (-1 * pow(2, 23))){
                    printf("\nASSEMBLY ERROR \nline %d: Constant exceeds WORD size:\n%s\n\n", symctr+1, temp[1]); 
                  return 1;
                  }
                  else {
                    address += 3;
                  }
              }
              else if(strstr(temp[0], "RESW")!= NULL){
                address += 3*amount;
              }
              else if(strstr(temp[0], "RESB")!= NULL){
                address += amount;
              }
              else if(strstr(temp[0], "BYTE")!= NULL){
                amount = constcheck(temp[1]);
                if(amount == -1) {
                  printf("\nASSEMBLY ERROR \nline %d: Invalid BYTE constant:\n%s\n\n", symctr+1, temp[1]); 
                  return 1;
                }
                address += amount;
              }
              else {
                address += 3;
              }      

              Temp = malloc(sizeof(token+1));
              Temp->SourceLineNumber = linectr;
            }
            else if (strctr != 0){
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
