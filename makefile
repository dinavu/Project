CC = g++
CFLAGS = -lSDL -lSDL_image -g3
OBJECTS = main.o graphics.o timer.o mario.o
HEADERS = graphics.h timer.h mario.h

all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ 

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean
clean:
	-rm *.o
