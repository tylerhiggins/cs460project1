# my-cat
[1] - "If the program tries to fopen() a file and fails, it should print the exact message “my-cat: cannot open file”"
		You are printing 2 error messages, but neither are the exact one from the project document

# my-uniq
[2] - when entering input from stdin, the program only prints one character after the second set of adjacent lines.
To reproduce:
```
type "./my-uniq" and hit enter
type "one", hit enter
type "one", hit enter twice

type "two", hit enter
type "two", hit enter twice

At this point the console will print out just the first letter "t"
```

[3] - test the program on mobydick-paragraph.txt and mobydick.txt, it is not finding the duplicated lines I added.

# my-sed
