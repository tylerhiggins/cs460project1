#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int uniq( FILE* fp ){
	char* line1 = NULL;
	char* line2 = NULL;
	size_t n = 0;
	ssize_t read;

	//fill the first line buffer
	getline(&line1, &n, fp);

	//for each subsequent line, fill the second buffer and compare it to the first
	//there may be more than one adjacent repeat of each line, so don't print them until an
	//  unequal line is encountered. set the repeated flag when an adjacent repetition is detected
	//after the comparison, copy the second buffer into the first

	int repeated = 0;
	while( (read = getline(&line2, &n, fp)) != -1){
		
		int cmp = strncmp(line1, line2, strlen(line1));

		if( cmp == 0 ){
			repeated = 1;
		}else if( repeated ){
			printf("%s\n", line1);
			repeated = 0;
		}

		//the number of characters to copy should be
		//  the size of the longest line
		size_t toCopy = 0;
		if( strlen(line1) >= strlen(line2) ){
			toCopy = strlen(line1);
		}else{
			toCopy = strlen(line2);
		}
		strncpy(line1, line2, toCopy);
	}
	free(line1);
	free(line2);
	return 0;
}

int main(int argc, char* argv[]){
	if( argc == 1 ){
		//no args given, use stdin
		uniq(stdin);
	}else{
		for( int i = 1; i < argc; i++ ){
			FILE* fp = fopen(argv[i], "r");
			if( !fp ){
				printf("my-uniq: cannot open file\n");
				exit(1);
			}
			uniq(fp);

			fclose(fp);
		}
	}

	return 0;
}
