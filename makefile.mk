#target:dependencies
#<tab>commands
a:menu.o fun.o
	gcc menu.o fun.o
menu.o:menu.c
	gcc -c menu.c
fun.o:fun.c fun.h
	gcc -c fun.c