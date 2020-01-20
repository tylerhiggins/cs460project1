/*
find and replace
TODO - error checking
TODO - test case sensitive find/replace
TODO - handle files we can't open
- test file that can't be opened, make it have a newline and exit if this happens
*/

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void findReplace(char* find, char* replace, char* line, char* stringToPrint);

/*
Finds a string and replaces it with another string
find - string to find
replace - string to replace
line - a string which will have variables substituted
stringToPrint - string that will be printed after find/replace
*/
void findReplace(char* find, char* replace, char* line, char* stringToPrint) {
	// if (DEBUG == 1) printf("\nfind: %s\nreplace: %s\nline: %s\n", find, replace, line);
	char* substring = (char*) calloc(1, strlen(find) * sizeof(char) + 1); //store lines
	substring[0] = '\0';
	if (substring == NULL) {exit(1);}
	// naiive string matching
	for (int i = 0; i < strlen(line)-1; i++) {
		// copy substring
		strncpy(substring, line + i, strlen(find));			// https://stackoverflow.com/questions/4214314/get-a-substring-of-a-char
		if (strlen(substring) > 0) {
		       substring[strlen(find)]= '\0';
		}	
		// use strncmp to see if it is a match, if a match is found, concatenate the replacement string instead
		if (strncmp(find, substring, strlen(substring)) == 0) {
			strncat(stringToPrint, replace, strlen(replace));
			i+=strlen(find)-1;
		}
		else {
			strncat(stringToPrint, &line[i], 1);
		}
		substring[0] = '\0';
	}
	free(substring);
}


int main(int argc, char*argv[]){
	FILE *fp = NULL;									// file pointer
	int buf_size = 1024;								// size of buffer
	char* stringToPrint;
	char* find = (char*) calloc(1, buf_size * sizeof(char) + 1);				// buffer to store find string
	if (find == NULL) {exit(1);}
	char* replace = (char*) calloc(1, buf_size * sizeof(char) + 1);			// buffer to store replace string
	if (replace == NULL) {exit(1);}
	find[0] = '\0';
	replace[0] = '\0';
	char* line = NULL;
	size_t linecap = 512;
	ssize_t linelen = 0;

	// save the find and replace arguments
	if (argc > 2) {
		strncpy(find, argv[1], strlen(argv[1]) + 2);			
		strncpy(replace, argv[2], strlen(argv[2]) + 2);
		if (strlen(find) > 0) {
		       find[strlen(find)]= '\0';
		}	
		if (strlen(replace) > 0) {
		       replace[strlen(replace)]= '\0';
		}	
	}

	// show user usage of my-sed if less than 3 args
	if (argc < 3) {
		printf("find term replace term [file ...]\n");
	}

	// get input from stdin
	else if (argc == 3) {
		// printf("Getting stdin:\n");
		line = (char*) calloc(1, buf_size * sizeof(char));			// buffer to store replace string
		if (line == NULL) {exit(1);}
		line[0] = '\0';
		if (fgets(line, buf_size, stdin) != NULL) {
			stringToPrint = (char*) calloc(1, buf_size + strlen(line) * sizeof(char) + 1);			// string that will be printed
			if (stringToPrint == NULL) {exit(1);}
			stringToPrint[0] = '\0';
			findReplace(find, replace, line, stringToPrint);
			printf("%s\n", stringToPrint);	
			free(stringToPrint);	
		}
	}

	// user specified a find, replace, and at least one file
	else if (argc > 3) {
		// iterate through each file from the cmd line
		for (int i = 3; i < argc; i++) {
			fp = fopen(argv[i], "r");
			if (fp == NULL) {
				perror("my_sed could not open file ");
				return 1;
			}
			// get one line of the file at a time
			while ((linelen = getline(&line, &linecap, fp)) > 0) {
				if (linelen < 0) {
					perror("Error: ");
					return 1;
					continue;
				}
				stringToPrint = (char*) calloc(1, buf_size + sizeof(char) * (linelen) + 1);			// string that will be printed
				if (stringToPrint == NULL) {exit(1);}
				stringToPrint[0] = '\0';
				findReplace(find, replace, line, stringToPrint);
				printf("%s\n", stringToPrint);
				stringToPrint[0] = '\0';
				free(stringToPrint);		
			}
			fclose(fp);
		}
	}
	free(line);	// line memory is allocated by getline
	free(find);
	free(replace);
	return 0;
}
