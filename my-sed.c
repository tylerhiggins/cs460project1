/*
find and replace
TODO - check valgrind
TODO - error checking
*/

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


int main(int argc, char *argv[]){
	FILE *fp = NULL;									// file pointer
	int buf_size = 1024;								// size of buffer
	char* stringToPrint;
	char* find = (char *) malloc(buf_size);				// buffer to store find string
	char* replace = (char *) malloc(buf_size);			// buffer to store replace string
	char* line = NULL;
	size_t linecap = 512;
	ssize_t linelen;
<<<<<<< HEAD
	strncpy(find, argv[1], sizeof(&argv[1]));			// save the find and replace arguments
	strncpy(replace, argv[2], sizeof(&argv[2]));
	char* substring = (char *) malloc(sizeof(find));	// buffer to store lines

	empty = isempty(find);

	// iterate through each file
=======
	strncpy(find, argv[1], sizeof(&argv[1]));
	strncpy(replace, argv[2], sizeof(&argv[2]));
	char* substring = (char *) malloc(sizeof(find));	// buffer to store lines
	// iterate through each file from the cmd line
>>>>>>> Resolved memory leak
	for (int i = 3; i < argc; i++) {
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			perror("my_sed could not open file ");
			return 1;
		}
<<<<<<< HEAD
		// get one line of the file at a time
=======
		// get the lines of the file
>>>>>>> Resolved memory leak
		while ((linelen = getline(&line, &linecap, fp)) > 0) {
			if (linelen < 0) {
				perror("Error: ");
				return 1;
				continue;
			}
			stringToPrint = (char *) malloc(linelen * sizeof(char));			// string that will be printed
			// naiive string matching
			for (int i = 0; i < strlen(line); i++) {
				// copy substring https://stackoverflow.com/questions/4214314/get-a-substring-of-a-char
				strncpy(substring, line + i, strlen(find));
				// use strncmp to see if it is a match, if a match is found, concatenate the replacement string instead
				if (strncmp(find, substring, strlen(substring)) ==0 ) {
					strncat(stringToPrint, replace, strlen(replace));
				}
				else {
					strncat(stringToPrint, substring, strlen(substring)-1);	
				}
			}
			printf("%s\n", stringToPrint);	
<<<<<<< HEAD
			free(stringToPrint);
=======
			strncpy(stringToPrint, "\0", 1);
			free(stringToPrint);		
>>>>>>> Resolved memory leak
		}
		fclose(fp);
	}
	free(find);
	free(replace);
	free(line);
	free(substring);
	return 0;
}
