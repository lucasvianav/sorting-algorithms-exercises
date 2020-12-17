all:
	gcc -Wall -Werror -std=c99 -o InsertionMerge InsertionMerge.c

mem:
	gcc -g3 -fsanitize=address -fno-omit-frame-pointer -fsanitize=undefined -Wall -Werror -std=c99 InsertionMerge.c -o InsertionMerge

run:
	./InsertionMerge
