CC = g++
CFLAGS = -lSDL -lSDL_image -lSDL_ttf -g3
OBJECTS = main.o graphics.o timer.o mario.o fireball.o enemy.o goomba.o koopa.o plant.o
HEADERS = graphics.h timer.h mario.h fireball.h enemy.h goomba.h koopa.h plant.h

all: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ 

%.o: %.cpp $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY: clean
clean:
	-rm *.o main *~
