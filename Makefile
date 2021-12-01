CC = gcc
TARGET = bin/sandgame
SOURCES = src/main.c src/particle.c
OBJECTS = obj/main.o obj/particle.o

all: bin obj $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $^ /usr/lib/libraylib.so -I src/ -o $@

$(OBJECTS): obj/%.o: src/%.c
	$(CC) -c $< -o $@

bin:
	mkdir -p $@

obj:
	mkdir -p $@

.PHONY: clean
clean:
	rm -rf bin obj