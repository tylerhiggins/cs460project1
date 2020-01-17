# Makefile for Mini Unix Utilities
# cs460-project1

PROJ = cs460-project1-Team1
CAT = my-cat
SED = my-sed
UNIQ = my-uniq

.SUFFIXES: .c .o
CC = gcc
CCFLAGS = -std=c99 -pedantic -Wall -g -Werror
OBJS = ${CAT}.o ${SED}.o ${UNIQ}.o

# the info for compiling, runs when 'make' is called
all: ${OBJS}
	${CC} ${CCFLAGS} -o ${CAT} ${CAT}.o
	${CC} ${CCFLAGS} -o ${SED} ${SED}.o
	${CC} ${CCFLAGS} -o ${UNIQ} ${UNIQ}.o

.c.o:
	${CC} ${CCFLAGS} -c $<

# program tests
cat-test: ${CAT}
	@echo --- RUNNING TEST my-cat ---
	./my-cat mobydick.txt oneline.txt test1.txt test2.txt

sed-test: all ${SED}
	@echo --- RUNNING TEST my-sed ---
	./my-sed "is" "isn't" test1.txt

uniq-test: ${UNIQ}
	@echo --- RUNNING TEST my-uniq ---
	./my-uniq test1.txt test2.txt

# val: all
# 	valgrind --leak-check=full --show-leak-kinds=all ./${EXEC}

# deletes unneccessary files
clean:
	rm -f ${CAT} ${CAT}.o  *.o *.tgz *.zip
	rm -f ${SED} ${SED}.o  *.o *.tgz *.zip
	rm -f ${UNIQ} ${UNIQ}.o *.o *.tgz *.zip

# make a tarball
tarball: clean
	rm -f ${PROJ}.zip ${PROJ}.tgz
	tar -czf ${PROJ}.tgz *

# make a zip file
zip: clean
	rm -f ${PROJ}.zip ${PROJ}.tgz
	zip -r ${PROJ}.zip *

# can add more *.o declarations here if necessary
${CAT}.o: ${CAT}.c
${SED}.o: ${SED}.c
${UNIQ}.o: ${UNIQ}.c