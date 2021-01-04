# SIC-ASSEMBLER Pass One

[![Run on Repl.it](https://repl.it/badge/github/jeremiahbaclig/SIC-ASSEMBLER)](https://repl.it/github/jeremiahbaclig/SIC-ASSEMBLER)

Pass 1 of a two-pass assembler.

PASS 1: 	Based on the file input, the program
will first check if there is a program call and a file via the command
line. If not, it will throw an error and exit. Via !inputFile being true,
there will also be an error. Otherwise, the file will be read through line
by line and checks will be made for the symbol rules in the SIC Assembly 
Language Specification (symbols != directives, [A-Z], len(Symbol) < 7 characters, 
no special chars). Afterwards, the symbols will be inserted into a
hash table along with the address. 

The hash table is an array of size 26 which utilizes the data types 
within the Symbol struct. Based on the hash/insert function, the symbols
are sorted out by its first letter alphabetically and collisions are dealt 
with by separate chaining (linked lists). The output will yield the symbol
table, which is the symbol 
```name <tab>hex address <CrLf>``` 
Besides the necessary 
symbol checks stated earlier, other checks that state the error and exit 
include duplicate symbols. The address should be incremented accordingly, and 
special cases such as ```BYTE, WORD, RESB, RESW``` should function correctly.
