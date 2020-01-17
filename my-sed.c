/*
find and replace
TODO - check valgrind
TODO - error checking
TODO - test case sensitive find/replace
- test file that can't be opened, make it have a newline and exit if this happens
- get input from stdin using fgets from fd 1

*/
#define _GNU_SOURCE
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

void findReplace(char* find, char* replace, char* line, char* stringToPrint);

// int mystringlen(char* string) {
// 	int i = 0;
// 	while(string[i] != '\0') {
// 		i++;
// 	}
// 	return i;
// }

/*
line - a string which will have variables substituted
*/
void findReplace(char* find, char* replace, char* line, char* stringToPrint) {
	// printf("find: %s\nreplace: %s\nline: %s\nstringToPrint: %s\n", find, replace, line, stringToPrint);
	char* substring = (char*) calloc(strlen(find) + 1, sizeof(char)); //store lines
	substring[0] = '\0';
	// char substring[strlen]
	if (substring == NULL) {
		exit(1);
	}
	// naiive string matching
	for (int i = 0; i < strlen(line); i++) {
		// copy substring
		strncpy(substring, line + i, strlen(find));			// https://stackoverflow.com/questions/4214314/get-a-substring-of-a-char
		// use strncmp to see if it is a match, if a match is found, concatenate the replacement string instead
		if (strncmp(find, substring, strlen(substring)) == 0) {
			// printf("match found at %d\n", i);
			strncat(stringToPrint, replace, strlen(replace));
			i++;
		}
		else {
			strncat(stringToPrint, substring, strlen(substring)-1);	
		}
	}
	free(substring);
}


int main(int argc, char*argv[]){
	FILE *fp = NULL;									// file pointer
	int buf_size = 1024;								// size of buffer
	char* stringToPrint;
	char* find = (char*) calloc(buf_size, sizeof(char));				// buffer to store find string
	char* replace = (char*) calloc(buf_size, sizeof(char));			// buffer to store replace string
	find[0] = '\0';
	replace[0] = '\0';
	char* line = NULL;
	size_t linecap = 512;
	ssize_t linelen = 0;

	// save the find and replace arguments
	if (argc > 2) {
		strncpy(find, argv[1], sizeof(&argv[1]));			
		strncpy(replace, argv[2], sizeof(&argv[2]));
	}

	// show user usage of my-sed if less than 3 args
	if (argc < 3) {
		printf("find term replace term [file ...]\n");
	}

	// get input from stdin
	// TODO use realloc if string gets too large
	else if (argc == 3) {
		// printf("Getting stdin:\n");
		line = (char*) calloc(buf_size, sizeof(char));			// buffer to store replace string
		line[0] = '\0';
		if (fgets(line, buf_size, stdin) != NULL) {
			stringToPrint = (char*) calloc(strlen(line), sizeof(char));			// string that will be printed
			stringToPrint[0] = '\0';
			findReplace(find, replace, line, stringToPrint);
			printf("%s\n", stringToPrint);	
			free(stringToPrint);	
		}
	}

	// user specified a find, replace, and at least one file
	else if (argc > 3) {
		// iterate through each file from the cmd line
		// stringToPrint = (char*) malloc(linelen * sizeof(char));			// string that will be printed
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
				stringToPrint = (char*) calloc(linelen, sizeof(char));			// string that will be printed
				stringToPrint[0] = '\0';
				findReplace(find, replace, line, stringToPrint);
				printf("%s\n", stringToPrint);	
				strncpy(stringToPrint, "\0", 1);
				free(stringToPrint);		
			}
			fclose(fp);
		}
		free(line);	// line memory is allocated by getline
	}

	free(find);
	free(replace);
	// free(stringToPrint);
	return 0;
}
