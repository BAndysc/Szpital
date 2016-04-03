CFLAGS = -std=c99
CC = gcc
objects = $(patsubst src/%.c, obj/release/%.o, $(wildcard src/*.c))
debug_objects = $(patsubst src/%.c, obj/debug/%.o, $(wildcard src/*.c))
DEPS := $(objects:.o=.d)
DEPS_DEBUG := $(debug_objects:.o=.d)
BINARY_NAME = hospital

NO_COLOR=\x1b[0m
OK_COLOR=\x1b[32;01m
INFO_COLOR=\x1b[36m
COMPILE_COLOR=\x1b[32;21m
ERROR_COLOR=\x1b[31;01m
WARN_COLOR=\x1b[33;01m

all: $(objects)
	@echo "$(INFO_COLOR)Building Hospital (release)$(NO_COLOR)"
	@$(CC) $(CFLAGS) -O3 -o $(BINARY_NAME) $(objects)
	@echo "Compiled to: $(BINARY_NAME)"

debug: $(debug_objects)
	@echo "$(INFO_COLOR)Building Hospital (debug)$(NO_COLOR)"
	@$(CC) $(CFLAGS) -g -o $(BINARY_NAME).dbg $(debug_objects)
	@echo "Compiled to: $(BINARY_NAME).dbg"

clean:
	@echo "$(INFO_COLOR)Clean up solution$(NO_COLOR)"
	@rm -rf obj
	@rm -f hos
	@rm -f Szpital.dbg

obj/release/%.o: src/%.c
	@mkdir -p obj/release/
	@echo "$(COMPILE_COLOR)Building $@$(NO_COLOR)"
	@$(CC) $(CFLAGS) -MMD -MP -c $(@:obj/release/%.o=src/%.c) -o $@

obj/debug/%.o: src/%.c
	@mkdir -p obj/debug/
	@echo "$(COMPILE_COLOR)Building $@$(NO_COLOR)"
	@$(CC) $(CFLAGS) -MMD -MP -g -c $(@:obj/debug/%.o=src/%.c) -o $@

-include $(DEPS)
-include $(DEPS_DEBUG)
