NAME=tree
CC=gcc
DEBUG_FLAG=-ansi -pedantic-errors -Wall -Wextra -g -D_DEFAULT_SOURCE -lm
RELEASE_FLAGS=-ansi -pedantic-errors -Wall -Wextra -DNDEBUG -O3 -lm -D_DEFAULT_SOURCE
VLG_FLAGS=--leak-check=yes --track-origins=yes
INCLUDE=-I include/

all: debug release object 

debug: src/$(NAME)/$(NAME).c test/$(NAME)_test.c 
	$(CC) $(DEBUG_FLAG) -o obj/$(NAME)_debug.out $^ $(INCLUDE)

release: src/$(NAME)/$(NAME).c test/$(NAME)_test.c 
	$(CC) $(RELEASE_FLAGS) -o obj/$(NAME)_release.out $^ $(INCLUDE)

object: src/$(NAME)/$(NAME).c
	$(CC) $(RELEASE_FLAGS) -c $^ -o obj/$(NAME)_release.o $(INCLUDE)
	$(CC) $(DEBUG_FLAG) -c $^ -o obj/$(NAME)_debug.o $(INCLUDE)

lib: obj/$(NAME)_release.o obj/$(NAME)_debug.o
	ar -q lib/lib$(NAME).a obj/$(NAME)_release.o obj/$(NAME)_debug.o 

.PHONY: clean
clean:
	rm -rf obj/*.o lib/*.a
	
.PHONY2: clean2
clean2:
	rm -f obj/*.out

	

	


