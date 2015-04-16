
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
AR = ar
CFLAGS  = -W -Wall -fdiagnostics-color=auto -std=c99
LDFLAGS = -lm
# -lpthread
EXEC      = carto_robot
EXEC_SDL  = carto_robot_sdl

# options
SDL   = yes
DEBUG = yes

################################################################################

SOURCES=geometrie.c \
		obstacles.c \
		point.c \
		pointList.c \
		bestInFirstOut.c \
		cartographie.c \
		astar.c \
		debug.c

HEADERS=$(SOURCES:.c=.h)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_SDL=$(SOURCES:.c=_sdl.o)

SOURCEFILES=exemple.c $(SOURCES) $(HEADERS) plateau.png

################################################################################

# Gestion des options

ifeq ($(SDL),yes)
	LDFLAGS += -lSDL -lSDL_image -lGL -lGLU -lSOIL
	SOURCES += ../common_code/simulation/affichage.c
	CFLAGS  += -DUSE_SDL=1
	OBJECTS  = $(OBJECTS_SDL)
	EXEC     = $(EXEC_SDL)
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
	$(CC) $(CFLAGS) -o $@ exemple.c $^ $(LDFLAGS) $(SDLFLAGS)

libCARTOGRAPHIE.a: $(OBJECTS)
	$(AR) -r $@ $(OBJECTS)
	ranlib $@

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
%_sdl.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

tarall: $(SOURCEFILES)
	tar -jcvf $(EXEC).tar.bz2 $^

clean:
	rm -f $(EXEC) *.o libCARTOGRAPHIE.a

mrproper: clean
	rm -rf $(EXEC).tar.bz2
