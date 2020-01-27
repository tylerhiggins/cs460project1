# Unix Utilities cat, sed, and uniq in C #

## my-cat ##
Usage: `./my-cat [file ...]`  
Description: This program takes file names as agruments and outputs the contents of each file in order to stdout. If no file specified, the program runs and terminates with no output to stdout.

## my-sed ##
Usage: `./my-sed find_term replace_term [file ...]`  
Description: This program takes a find term and replace term, and replaces the first occurence of the find term with the replace term on each file specified. If the user specifies an empty string, the first occurence of the term in each file will be removed. If there is no files specifed, it will read from stdin for finding and replacing the term.

## my-uniq ##
Usage: `./my-uniq [file ...]`  
Description: This program finds adjacent duplicate lines from multiple files, removes them, and prints them to stdout. If there is no input file specifed, this program will read from stdin. 

## Compile and run instructions ##
To compile: `make all`  
  
You can run tests on each progam:  
my-cat test: `make cat-test`  
my-sed test: `make sed-test`  
my-uniq test: `make uniq-test`

You can customize the test files in the Makefile


## Authors
- Tyler Higgins
- Jacob Pugsley
- Julian Keller
