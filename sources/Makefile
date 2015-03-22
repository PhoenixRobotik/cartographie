CC=gcc
CFLAGS=-W -Wall

LDFLAGS=-lm
SDLFLAGS=-lSDL -lSDL_image -lGL -lGLU -lSOIL
EXEC=carto_robot

FICHIERS_C=main.c geometrie.c obstacles.c # pathfinding.c points.c
FICHIERS_H=$(FICHIERS_C:.c=.h)
FICHIERS_O=$(FICHIERS_C:.c=.o)

SOURCEFILES=main.c $(FICHIERS_C) $(FICHIERS_H) plateau.png

.PHONY:$(EXEC)

view: all
	./$(EXEC)

all: $(EXEC)

$(EXEC): $(FICHIERS_O)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

clean:
	rm -f $(FICHIERS_O)

mrproper: clean
	rm -rf $(EXEC) $(EXEC).tar.bz2
