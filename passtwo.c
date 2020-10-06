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
  int index = hash(symb->name);
	symb->next = Hashes[index];
	Hashes[index] = symb;
}

bool in_table(char *symb){
  for(int i=0; i<TABLE_LEN; i++){
    if(Hashes[i] != NULL){
      Symbol *temp = Hashes[i];
      while(temp != NULL){
        if(strstr(symb, temp->name)){
          return true;
          break;
        }

        temp = temp -> next;
      }
    }
  }
  return false;
}

int opcodes(char* directive){
  if(strcmp(directive, "ADD") == 0){
    return (int)0x18;
  }
  else if(strcmp(directive, "ADDF") == 0){
    return (int)0x58;
  }
  else if(strcmp(directive, "ADDR") == 0){
    return (int)0x90;
  }
  else if(strcmp(directive, "AND") == 0){
    return (int)0x40;
  }
  else if(strcmp(directive, "CLEAR") == 0){
    return (int)0xB4;
  }
  else if(strcmp(directive, "COMP") == 0){
    return (int)0x28;
  }
  else if(strcmp(directive, "COMPF") == 0){
    return (int)0x88;
  }
  else if(strcmp(directive, "COMPR") == 0){
    return (int)0xA0;
  }
  else if(strcmp(directive, "DIV") == 0){
    return (int)0x24;
  }
  else if(strcmp(directive, "DIVF") == 0){
    return (int)0x64;
  }
  else if(strcmp(directive, "DIVR") == 0){
    return (int)0x9C;
  }
  else if(strcmp(directive, "FIX") == 0){
    return (int)0xC4;
  }
  else if(strcmp(directive, "FLOAT") == 0){
    return (int)0xC0;
  }
  else if(strcmp(directive, "HIO") == 0){
    return (int)0xF4;
  }
  else if(strcmp(directive, "J") == 0){
    return (int)0x3C;
  }
  else if(strcmp(directive, "JEQ") == 0){
    return (int)0x30;
  }
  else if(strcmp(directive, "JGT") == 0){
    return (int)0x34;
  }
  else if(strcmp(directive, "JLT") == 0){
    return (int)0x38;
  }
  else if(strcmp(directive, "JSUB") == 0){
    return (int)0x48;
  }
  else if(strcmp(directive, "LDA") == 0){
    return (int)0x00;
  }
  else if(strcmp(directive, "LDB") == 0){
    return (int)0x68;
  }
  else if(strcmp(directive, "LDCH") == 0){
    return (int)0x50;
  }
  else if(strcmp(directive, "LDF") == 0){
    return (int)0x70;
  }
  else if(strcmp(directive, "LDL") == 0){
    return (int)0x08;
  }
  else if(strcmp(directive, "LDS") == 0){
    return (int)0x6C;
  }
  else if(strcmp(directive, "LDT") == 0){
    return (int)0x74;
  }
  else if(strcmp(directive, "LDX") == 0){
    return (int)0x04;
  }
  else if(strcmp(directive, "LPS") == 0){
    return (int)0xD0;
  }
  else if(strcmp(directive, "MUL") == 0){
    return (int)0x20;
  }
  else if(strcmp(directive, "MULF") == 0){
    return (int)0x60;
  }
  else if(strcmp(directive, "MULR") == 0){
    return (int)0x98;
  }
  else if(strcmp(directive, "NORM") == 0){
    return (int)0xC8;
  }
  else if(strcmp(directive, "OR") == 0){
    return (int)0x44;
  }
  else if(strcmp(directive, "RD") == 0){
    return (int)0xD8;
  }
  else if(strcmp(directive, "RMO") == 0){
    return (int)0xAC;
  }
  else if(strcmp(directive, "RSUB") == 0){
    return (int)0x4C;
  }
  else if(strcmp(directive, "SHIFTL") == 0){
    return (int)0xA4;
  }
  else if(strcmp(directive, "SHIFTR") == 0){
    return (int)0xA8;
  }
  else if(strcmp(directive, "SIO") == 0){
    return (int)0xF0;
  }
  else if(strcmp(directive, "SSK") == 0){
    return (int)0xEC;
  }
  else if(strcmp(directive, "STA") == 0){
    return (int)0x0C;
  }
  else if(strcmp(directive, "STB") == 0){
    return (int)0x18;
  }
  else if(strcmp(directive, "STCH") == 0){
    return (int)0x54;
  }
  else if(strcmp(directive, "STF") == 0){
    return (int)0x80;
  }
  else if(strcmp(directive, "STI") == 0){
    return (int)0xD4;
  }
  else if(strcmp(directive, "STL") == 0){
    return (int)0x14;
  }
  else if(strcmp(directive, "STS") == 0){
    return (int)0x7C;
  }
  else if(strcmp(directive, "STSW") == 0){
    return (int)0xE8;
  }
  else if(strcmp(directive, "STT") == 0){
    return (int)0x84;
  }
  else if(strcmp(directive, "STX") == 0){
    return (int)0x10;
  }
  else if(strcmp(directive, "SUB") == 0){
    return (int)0x1C;
  }
  else if(strcmp(directive, "SUBF") == 0){
    return (int)0x5C;
  }
  else if(strcmp(directive, "SUBR") == 0){
    return (int)0x94;
  }
  else if(strcmp(directive, "TD") == 0){
    return (int)0xE0;
  }
  else if(strcmp(directive, "TIO") == 0){
    return (int)0xF8;
  }
  else if(strcmp(directive, "TIX") == 0){
    return (int)0x2C;
  }
  else if(strcmp(directive, "TIXR") == 0){
    return (int)0xB8;
  }
  else if(strcmp(directive, "WD") == 0){
    return (int)0xDC;
  }
  else{
    return 0;
  }
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

int symlength(char *input){
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
        if(constant[i+1] == 39){
	      break;
	}
      else if(constant[i] == 32) {
	size++;
        if(constant[i+1] == 39){
	      break;
	}
      }
      else if(constant[i] != 39 && &constant[i] == NULL) {
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

const char* bytecheck(char *byteword){
  int len = strlen(byteword);
  char temp[6];
  char hexval[6];
  char tempascii[6];
  char *toascii = malloc(len+1);

  if(byteword[0] == 'X'){
    for(int i=2; i<len; i++){
      if(byteword[i] == 39){
      }
      else if(byteword[i] <= 'F' && byteword[i] >= 'A' && &byteword[i] != NULL){
        sprintf(temp, "%c", byteword[i]);
        strcat(hexval, temp);
        strcpy(temp, "");
      }
      else if(byteword[i] <= '9' && byteword[i] >= '0' && &byteword[i] != NULL){
        sprintf(temp, "%c", byteword[i]);
        strcat(hexval, temp);
        strcpy(temp, "");

      }
    }
    strcpy(toascii, hexval);
    return toascii;
  }
  else if(byteword[0] == 'C'){
    for(int i=2; i<len; i++){
      if(byteword[i] != 39){
        int ascii = byteword[i];
        int length = snprintf(NULL, 0, "%d", ascii);
        char* src = malloc(length + 1);

        snprintf(src, length+1, "%d", ascii);
        strcat(tempascii, src);
        free(src);
      }
    }
    strcpy(toascii, tempascii);
    
    return toascii;
  }
  return NULL;
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

int linectr, symctr, address, startaddress, endaddress, startctr, endctr, opcode, symbnum;

int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("USAGE: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE* inputFile;
    inputFile = fopen(argv[1], "r");

    if (!inputFile) {
        printf("\nASSEMBLY ERROR: file could not be opened for reading.\nexiting...\n");
        return 1;
    }

    hash_table();

    FILE *objFile;
    char* objname = strcat(strtok(argv[1],"."),".obj");
    objFile = fopen(objname, "w+");

    FILE *tmp;
    tmp = fopen("tmp.txt", "w+"); 

    char line[1024];
    char hexval[5];
    char headerprint[19] = "H";
    char textprint[69] = "T";
    char symbols[50][7];
    Symbol *Temp;
    while (fgets(line, 1024, inputFile)) {
      int length = strlen(line);
      
      char * temp[3];
        if (length > 0) {
          if (strstr(line, "#") != NULL) {}
          else if (line[0] == 10 || line[0] == 13){
            printf("\nASSEMBLY ERROR\nSIC file contains a blank line \nexiting...\n");
            remove(objname);
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
                    remove(objname);
                    return 1;
              }
	            if(*temp[0] <= '/' && *temp[0] >= '!'){
                    printf("\nASSEMBLY ERROR \nline %d: symbols must start with [A-Z]:\n%s\nexiting...\n", symctr+1, temp[0]);
                    remove(objname);
                    return 1;
              }

              if (strstr(temp[0], "START") != NULL ||strstr(temp[0], "END") != NULL ||strstr(temp[0], "BYTE") != NULL || \
                    strstr(temp[0], "WORD") != NULL ||strstr(temp[0], "RESB") != NULL ||strstr(temp[0], "RESW") != NULL || \
                        strstr(temp[0], "EXPORTS") != NULL) {
                if (strcmp(temp[0], temp[1]) == 0) {
                  printf("\nASSEMBLY ERROR \nline %d: Symbol defined with name that matches an assembler directive:\n%s and %s\nexiting...\n", symctr+1, temp[0], temp[1]);
                  remove(objname);
                  return 1;   	      
                }
              }

              if (symlength(temp[0]) > 6) {
                printf("\nASSEMBLY ERROR \nline %d: Symbol must be less than 7 characters:\n%s\nexiting...\n", symctr+1, temp[0]);
                remove(objname);
                return 1;   	  
              }

              if (lowcheck(temp[0]) > 0) {
                printf("\nASSEMBLY ERROR \nline %d: Symbol cannot have [a-z]:\n%s\nexiting...", symctr+1, temp[0]);
                remove(objname);
                return 1;  
              }

              if(strstr(temp[1], "START")){
                if(startctr==1){
                  printf("\nASSEMBLY ERROR \nline %d: Multiple start decl.\nexiting...", symctr+1);
                  remove(objname);
                return 1;  
                }
              }

              if(strcmp(temp[1], "END") == 0){
                endctr++;
                char *rest;
                endaddress = address;
                if(endctr==2){
                  printf("\nASSEMBLY ERROR \nline %d: Multiple end decl.\nexiting...", symctr+1);
                  remove(objname);
                return 1;  
                }
              }
              
              if(strstr(temp[1], "START") && linectr == 1) {
                startctr++;
                symctr++;
                char *rest;
                address = (int)strtol(temp[2], &rest, 16);
                startaddress = (int)strtol(temp[2], &rest, 16);

                if(address == 0 && *temp[2] != 48){
                  printf("\nASSEMBLY ERROR \nline %d: Invalid address:\n%s\nexiting...\n", symctr+1, temp[2]);
                  remove(objname);
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
                    remove(objname);
                    return 1;  
                }

                if(Temp->Address > pow(2, 15)){
                  printf("\nASSEMBLY ERROR \nline %d: Memory Exceeded (> 8000):\n%x\nexiting...\n", symctr+1, Temp->Address);
                  remove(objname);
                  return 1; 
                }

                int checker = 6 - strlen(temp[0]);
                for(int i=0; i<checker; i++){
                  strcat(headerprint, "0");
                }
                strcat(headerprint, temp[0]);
                checker = 6 - strlen(temp[2]);
                for(int i=0; i<checker; i++){
                  strcat(headerprint, "0");
                }
                strcat(headerprint, temp[2]);
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
                    remove(objname);
                  return 1;  
                }

                if(Temp->Address > pow(2, 15)){
                  printf("\nASSEMBLY ERROR \nline %d: Memory Exceeded (> 8000):\n%x\nexiting...\n", symctr+1, Temp->Address);
                  remove(objname);
                  return 1; 
                }
                address += 3;

                int checker = 6 - strlen(temp[0]);
                for(int i=0; i<checker; i++){
                  strcat(headerprint, "0");
                }
                strcat(headerprint, temp[0]);
                checker = 6;
                for(int i=0; i<checker; i++){
                  strcat(headerprint, "0");
                }

                printf("WARNING:\nNo START directive -> starting address is 0\ncontinuing...\n\n");
              }
              else {               
                symctr++;

                char Name[7];
                strcpy(Name, temp[0]);
                Temp->Address = address;
                Temp->SourceLineNumber = linectr;
                strcpy(Temp->name, Name);
                insert(Temp, address);

                strcpy(textprint, "T");
                int length = snprintf(NULL, 0, "%x", address); 
                char* textaddr = malloc(length + 1);
                snprintf(textaddr, length + 1, "%x", address);
                int checker = 6 - strlen(textaddr);
                checker = 6 - strlen(textaddr);
                for(int i=0; i<checker; i++){
                  strcat(textprint, "0");
                }
                strcat(textprint, textaddr);
                free(textaddr);

                int someop = opcodes(temp[1]);
                
                if(someop != 0){
                  length = snprintf(NULL, 0, "%x", someop); 
                  char* textop = malloc(length + 1);
                  snprintf(textop, length + 1, "%x", someop);
                  strcat(textprint, "03");
                  strcat(textprint, textop);
                  free(textop);
                  fprintf(tmp, "%s\n", textprint);
                }

                if(duplicates(Name) > 1){
                  printf("\nASSEMBLY ERROR \nline %d: Duplicate Symbol:\n%s\n\n", symctr+1, Name); 
                  remove(objname);
                  return 1;
                }

                if(Temp->Address > pow(2, 15)){
                  printf("\nASSEMBLY ERROR \nline %d: Memory Exceeded (> 8000):\n%x\nexiting...\n", symctr+1, Temp->Address);
                  remove(objname);
                  return 1; 
                }
               
                char *other;
                int amount = (int)strtol(temp[2], &other, 10);
                if(strstr(temp[1], "WORD") != NULL){
                  int word = atoi(temp[2]);

                  if(word > pow(2, 23) || word < (-1 * pow(2, 23))){
                    printf("\nASSEMBLY ERROR \nline %d: Constant exceeds WORD size:\n%s\n\n", symctr+1, temp[2]); 
                    remove(objname);
                  return 1;
                  }
                  else {
                    char wordcount[12];
                    sprintf(wordcount, "%x", word);
                    strcat(textprint, "03");
                    strcat(textprint, wordcount);
                    fprintf(tmp, "%s\n", textprint);

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
                    remove(objname);
		                return 1;
		              } 

                  const char* bytecode = malloc(strlen(temp[2]));
                  bytecode = bytecheck(temp[2]);
                
                  if(bytecode != NULL){
                    strcat(textprint, "03");
                    strcat(textprint, bytecode);
                    fprintf(tmp, "%s\n", textprint);
                  }
		              address += amount;
                }
                else {
                  address += 3;
                }           
              }

            }
            else if(strctr == 2){
              strcpy(symbols[symbnum], temp[1]);
              symbnum++;

              if(strstr(temp[0], "START")){
                if(startctr==1){
                  printf("\nASSEMBLY ERROR \nline %d: Multiple start decl.\nexiting...", symctr+1);
                  remove(objname);
                return 1;  
                }
              }

              if(strcmp(temp[0], "END") == 0){
                endctr++;
                char *rest;
                endaddress = address;
                if(endctr==2){
                  printf("\nASSEMBLY ERROR \nline %d: Multiple end decl.\nexiting...", symctr+1);
                  remove(objname);
                return 1;  
                }
              }
              char *other;
              int amount = (int)strtol(temp[1], &other, 16);

              strcpy(textprint, "T");
              int length = snprintf(NULL, 0, "%x", address); 
              char* textaddr = malloc(length + 1);
              snprintf(textaddr, length + 1, "%x", address);
              int checker = 6 - strlen(textaddr);
              checker = 6 - strlen(textaddr);
              for(int i=0; i<checker; i++){
                strcat(textprint, "0");
              }
              strcat(textprint, textaddr);
              free(textaddr);

              int someop = opcodes(temp[0]);
                
              if(someop != 0){
                length = snprintf(NULL, 0, "%x", someop); 
                char* textop = malloc(length + 1);
                snprintf(textop, length + 1, "%x", someop);
                strcat(textprint, "03");
                strcat(textprint, textop);
                free(textop);
                fprintf(tmp, "%s\n", textprint);
              }

              if(strstr(temp[0], "WORD")!= NULL){
                int word = atoi(temp[1]);
                  if(word > pow(2, 23) || word < (-1 * pow(2, 23))){
                    printf("\nASSEMBLY ERROR \nline %d: Constant exceeds WORD size:\n%s\n\n", symctr+1, temp[1]); 
                    remove(objname);
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
                  remove(objname);
                  return 1;
                }
                const char* bytecode = malloc(strlen(temp[1]));
                  bytecode = bytecheck(temp[1]);
                
                  if(bytecode != NULL){
                    strcat(textprint, "03");
                    strcat(textprint, bytecode);
                    fprintf(tmp, "%s\n", textprint);
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

    for(int i=0; i<symbnum; i++){
      if(in_table(symbols[i]) == false){
          printf("\nPASS 2 ERROR\nOperand uses a symbol that is not defined: \n%s\nexiting...\n", symbols[i]);
          remove(objname);
          return 1;
      }
    }

    endaddress -= startaddress; 
    int length = snprintf(NULL, 0, "%x", endaddress); 
    char* sendaddr = malloc(length + 1);
    snprintf(sendaddr, length + 1, "%x", endaddress);
    int checker = 6 - strlen(sendaddr);
    for(int i=0; i<checker; i++){
      strcat(headerprint, "0");
    }
    strcat(headerprint, sendaddr);
    fprintf(objFile, "%s\n", headerprint);
    free(sendaddr);

    char command[50];
    strcpy(command, "cat tmp.txt >> ");
    strcat(command, objname);

    fclose(tmp);
    fclose(inputFile);  
    fclose(objFile);

    system(command);
    remove("tmp.txt");

    objFile = fopen(objname, "a");
    char endprint[7] = "E";
    length = snprintf(NULL, 0, "%x", startaddress); 
    char* sstartaddr = malloc(length + 1);
    snprintf(sstartaddr, length + 1, "%x", startaddress);
    checker = 6 - strlen(sstartaddr);
    for(int i=0; i<checker; i++){
      strcat(endprint, "0");
    }
    strcat(endprint, sstartaddr);
    fprintf(objFile, "%s\n", endprint);
    free(sstartaddr);
    fclose(objFile);

    return 0;
}
