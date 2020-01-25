# my-cat
[1] - "If the program tries to fopen() a file and fails, it should print the exact message “my-cat: cannot open file”"
		You are printing 2 error messages, but neither are the exact one from the project document

# my-uniq
[2] - when entering input from stdin, the program only prints one character after the second set of adjacent lines.
		To reproduce:
		type "./my-uniq" and hit enter
		type "one", hit enter
		type "one", hit enter twice

		type "two", hit enter
		type "two", hit enter twice

		At this point the console will print out just the first letter "t"

[3] - test the program on mobydick-paragraph.txt and mobydick.txt, it is not finding the duplicated lines I added.

"The original Unix uniq utility detects adjacent duplicate lines from the input file and removes them and writes out to an output file. my-uniq will do exactly this, it finds out adjacent duplicate lines in files, and prints them."
This is a little confusing, one one hand it sounds like we should find the duplicate lines and only print those. On the other hand it sounds like it is supposed to function just like 'uniq' where it prints out the entire contents of the file, but deletes duplicated adjacent lines. 

# my-sed