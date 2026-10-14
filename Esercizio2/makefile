simulation: compile
	clear

compile:	SkipList

clean:
	ipcrm -a
	rm Skiplist
	clear

run:
	clear
	./Skiplist dictionary.txt correctme.txt

#=============================================================

CC = gcc 

#=============================================================
SkipList: SkiplistMain.c
	${CC}	SkiplistMain.c Skiplist.c -o Skiplist