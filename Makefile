
# Options prises en compte :
#    SDL=yes       pour utiliser le simulateur
#    DEBUG=yes     pour activer le debug

# Cibles :
#    run: lance l'executable
#    all: créer l'executable
#    demo: lance un ensemble de commande au robot

################################################################################

# Valeur par défaut

CC = gcc

CFLAGS  = -W -Wall -fdiagnostics-color=auto -std=c99
LDFLAGS = -lm
# -lpthread
EXEC  = carto_robot

# options
SDL   = yes
DEBUG = yes

################################################################################

SOURCES=main.c \
		geometrie.c \
		obstacles.c \
		point.c \
		pointList.c \
		bestInFirstOut.c \
		pathfinding.c \

HEADERS=$(SOURCES:.c=.h)
OBJECTS=$(SOURCES:.c=.o)

SOURCEFILES=main.c $(SOURCES) $(HEADERS) plateau.png

################################################################################

# Gestion des options

ifeq ($(SDL),yes)
	LDFLAGS    += -lSDL -lSDL_image -lGL -lGLU -lSOIL
	SOURCES += simulation/affichage.c
	CFLAGS += -DUSE_SDL=1
endif

ifeq ($(DEBUG),yes)
	CFLAGS += -DDEBUG=1 -g
endif

################################################################################

.PHONY:view

view: all
	./$(EXEC)

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) $(SDLFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

clean:
	rm -f $(OBJECTS)

mrproper: clean
	rm -rf $(EXEC) $(EXEC).tar.bz2
