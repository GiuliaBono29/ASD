#=============================================================
simulation: compile
	clear

compile:	Order

clean:
	ipcrm -a
	rm Order_Array
	clear

run:
	clear
	./Order_Array records.txt

#=============================================================

CC = gcc 

#=============================================================
Order: Order_Array_Main.c
	${CC}	Order_Array_Main.c Order_Array.c -o Order_Array

