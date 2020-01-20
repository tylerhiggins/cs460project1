/*
 * my_cat.c: Written by Tyler Higgins. This program performs a similar 
 * task to the program "cat" in Unix/Linux Systems. This program takes 
 * files as arguments from the command line and prints them 
 * to std out.
*/

// TODO use strerror to output error messages (mainly for fopen fd)
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
	long unsigned int buf = 0;			// Buffer size. 
	char *buffer = NULL;       // Buffer in which to store characters.
	FILE *file = NULL;       // Pointer to the file.
	/* Iterates through each filename given in the arguments
	   ignoring index 0 since argv[0] is the name of the program
	   itself. */
	for(int i = 1; i < argc; i++){
		/* Open the file. */
		file = fopen(argv[i], "r");
		if(file == NULL){
			printf("%s: Could not open file %s\n", argv[0], argv[i]);
			printf("%s: %s\n",argv[0], strerror(errno));
			return 1;
		}
		/* Read each line of the file, as long as there are 
		characters to be read. */
		while(getline(&buffer,&buf,file) > 0){
			printf("%s",buffer);
			free(buffer);		// free and reset buffers
			buffer = NULL;
			buf = 0;
		}
		/* free the buffer and reset buffer and character count
		   before moving on to the next file.*/
		free(buffer);
		buffer = NULL;
		buf = 0;
		fclose(file);
	}
	return 0;
}
