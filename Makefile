CFLAGS =
CC = gcc
objects = $(patsubst src/%.c, obj/release/%.o, $(wildcard src/*.c))
debug_objects = $(patsubst src/%.c, obj/debug/%.o, $(wildcard src/*.c))

all: $(objects)
	echo $(objects)
	$(CC) $(CFLAGS) -O3 -o Szpital $(objects)

debug: $(debug_objects)
	echo $(debug_objects)
	$(CC) $(CFLAGS) -g -o Szpital.dbg $(debug_objects)

clean:
	rm -rf obj
	rm -f Szpital
	rm -f Szpital.dbg

obj/release/%.o:
	mkdir -p obj/release/
	$(CC) $(CFLAGS) -c $(@:obj/release/%.o=src/%.c) -o $@

obj/debug/%.o:
	mkdir -p obj/debug/
	$(CC) $(CFLAGS) -g -c $(@:obj/debug/%.o=src/%.c) -o $@
