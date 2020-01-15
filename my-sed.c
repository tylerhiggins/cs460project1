/*
*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>


int main(int argc, char *argv[]){
	FILE *fp = NULL;	// file pointer
	int buf_size = 512;		// size of buffer
	char* line1 = (char *) malloc(buf_size);	// buffer to store lines
	char* line2 = (char *) malloc(buf_size);	// buffer to store lines

	// iterate through each file from the cmd line
	for (int i = 1; i < argc; i++) {
		// get the current line and the next line
		fp = fopen(argv[i], "r");
		if (fp == NULL) {
			perror("my_uniq could not open file ");
			return 1;
		}
		// read two lines of the file at the same time
		// get the lines of the file
		while (fgets(line1, buf_size, fp) != NULL) {
			if (line2 == NULL) {
				if (strncpy(line2, line1, sizeof(line1)) == NULL) {
					perror("Error: ");
					return 1;
				}
				continue;
			}

			// compare lines 1 and 2
			// if diff print line 1
			printf("%s", line2);
			// else strncpy
			
		}


		fclose(fp);
	}


	free(line1);
	free(line2);

	// compare the lines char by char

	// if the line doesn't match, print it

	return 0;
}
