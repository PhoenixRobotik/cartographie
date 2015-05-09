# Cibles :
#    run: lance l'executable
#    all: créer l'executable
#    demo: lance un ensemble de commande au robot
################################################################################

# Options
# PC ou STM32
export ARCH  = STM32
# yes ou no
export SDL   = yes
# Niveaux de débug
export DEBUG = _WARNING_

################################################################################
# Variables de compilation

ifeq ($(ARCH), STM32)
	include ../stm32f407/stm32f407.mk
else
	CC = gcc
	AR = ar
	CFLAGS  = -W -Wall -fdiagnostics-color=auto -std=c99
	LDFLAGS = -lm
	ifeq ($(SDL),yes)
		LDFLAGS += -lSDL -lSDL_image -lGL -lGLU -lSOIL
		SOURCES += ../common_code/simulation/affichage.c
		CFLAGS  += -DUSE_SDL=1
		OBJECTS  = $(OBJECTS_SDL)
		EXEC     = $(EXEC_SDL)
	endif
endif

ifeq ($(DEBUG),yes)
	DEBUGFLAG = -DDEBUG=1 -g
else
	DEBUGFLAG = -DDEBUG=0
endif


# Chemin du dépôt stm32f407
# /!\ Doit être le chemin absolu. Pas relatif.
PathSTM32 = ../stm32f407/

EXEC      = carto_robot
EXEC_SDL  = carto_robot_sdl

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

.PHONY:view

view: all
	./$(EXEC)

all: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ exemple.c $^ $(LDFLAGS) $(DEBUGFLAG) $(SDLFLAGS)

libCartographie.a: $(OBJECTS)
	@echo "	AR	$@"
	@$(AR) -r $@ $(OBJECTS)
	@echo "	RANLIB	$@"
	@ranlib $@

%.o: %.c
	@echo "	CC	$@"
	@$(CC) $(CFLAGS) $(DEBUGFLAG) -o $@ -c $<
%_sdl.o: %.c
	$(CC) $(CFLAGS) $(DEBUGFLAG) -o $@ -c $<


##### Nettoyage
.PHONY: clean cleanDist cleanLib bclean mrproper

clean:
	rm -f $(OBJECTS) $(OBJECTS_SDL)
	rm -f libCartographie.a

cleanDist: clean
	$(MAKE) -C $(STM32_Dir) clean

bclean:
	$(MAKE) -C $(STM32_Dir) $@
	rm -f $(EXEC) $(EXEC_SDL)

mrproper: clean bclean
