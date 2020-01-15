/*
find and replace
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int strmatch() {
	return 0;
}


int main(int argc, char *argv[]){
	FILE *fp = NULL;	// file pointer
	int buf_size = 1024;		// size of buffer
	char* find = (char *) malloc(buf_size);	// buffer to store lines
	char* replace = (char *) malloc(buf_size);	// buffer to store lines
	char* stringToPrint;
	char* line = NULL;
	size_t linecap = 512;
	ssize_t linelen;

	strncpy(find, argv[1], sizeof(&argv[1]));
	strncpy(replace, argv[2], sizeof(&argv[2]));

	// printf("find:%s, replace:%s\n", find, replace);

	char* substring = (char *) malloc(sizeof(find));	// buffer to store lines

	// iterate through each file from the cmd line
	for (int i = 3; i < argc; i++) {
		// get the current line and the next line
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			perror("my_sed could not open file ");
			return 1;
		}
		// read two lines of the file at the same time
		// get the lines of the file
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
					i++;
				}
				else {
					strncat(stringToPrint, substring, strlen(substring)-1);	
				}
			}
			printf("%s\n", stringToPrint);
			
			
		}


		fclose(fp);
	}


	free(find);
	free(replace);
	free(line);
	free(substring);
	free(stringToPrint);

	// compare the lines char by char

	// if the line doesn't match, print it

	return 0;
}
