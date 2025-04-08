Author: Mihir Gupta
Student ID: 101172281

List of sourcefile: 

deque.c         fight.c         fighter.c       main.c
run.c           stats.c         defs.h          makefile


Instructions on how to use:

Just type "make" it will link everything.

After linking type "./fp" this will run the program.

To remove all the .o files at the end: please run the command "make clean"

To check leaks: please run below command after compilling

"make && valgrind --leak-check=full --show-leak-kinds=all -s ./fp"


Thanks

-----------------------------------------------------------------------------------------------------------------