/*
 * my_cat.c: Written by Tyler Higgins
 * This program performs a similar task to the 'cat'
 * program in Unix Systems. This program takes files
 * as arguments from the command line and prints them to 
 * std out.
*/
#include<stdio.h>
int main(int argc, char *argv[]){
	int buf = 256;			// Buffer size. 
	char buffer[buf];       // Buffer in which to store characters.
	FILE *file = NULL;       // Pointer to the file.
	/* Iterates through each filename given in the arguments
	   ignoring index 0 since argv[0] is the name of the program
	   itself. */
	for(int i = 1; i < argc; i++){
		/* Open the file. */
		file = fopen(argv[i], "r");
		if(file == NULL){
			printf("my_cat: Could not open file %s\n", argv[i]);
			return 1;
		}
		/* Read the contents of the file. So long as fgets does not
		   read EOF. */
		while(fgets(buffer,buf,file) != NULL){
			printf("%s",buffer);
		}

		fclose(file);
	}
	return 0;
}