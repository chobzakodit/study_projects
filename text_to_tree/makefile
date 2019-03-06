objects = main.o binarytree.o orderedset.o

main : $(objects)
	gcc -Wall -Wextra -Werror -o main $(objects)

main.o : binarytree.h orderedset.h
	gcc -c main.c
binarytree.o: binarytree.h orderedset.h
	gcc -c binarytree.c
orderedset.o: orderedset.h
	gcc -c orderedset.c
.PHONY : clean

clean :
	rm main $(objects)