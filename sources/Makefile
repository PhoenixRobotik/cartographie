CC=gcc
CFLAGS=-W -Wall

LDFLAGS=-lm
SDLFLAGS=-lSDL -lSDL_image -lGL -lGLU -lSOIL
GDBFLAGS=-g
EXEC=carto_robot

SOURCES=main.c geometrie.c obstacles.c point.c pointList.c bestInFirstOut.c pathfinding.c
HEADERS=$(SOURCES:.c=.h)
OBJECTS=$(SOURCES:.c=.o)

SOURCEFILES=main.c $(SOURCES) $(HEADERS) plateau.png

.PHONY:view

view: all
	./$(EXEC)

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS) $(GDBFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS) $(GDBFLAGS)

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -rf $(EXEC) $(EXEC).tar.bz2
