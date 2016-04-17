PROJECT=cartographie
default: all
# Default Options
export ARCH  ?= PC
export DEBUG ?= 0

PARENT_DIR = ../

# Constantes de compilation
EXEC    = carto_robot

include $(PARENT_DIR)/hardware/common.rules
################################################################################
# Fichiers du projet

FICHIERS_C = \
	geometrie.c \
	obstacles.c \
	point.c \
	pointList.c \
	bestInFirstOut.c \
	cartographie.c \
	astar.c \
	debug.c

FICHIERS_O  += $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )

################################################################################
# Compilation

# Règles de compilation de la "librairie cartographie"
_libCarto: $(BUILD_DIR)/libCarto.a

$(BUILD_DIR)/libCarto.a: $(FICHIERS_O)

# Règles de compilation de l'exécutable carto (des tests quoi)
all: $(BUILD_DIR)/$(EXEC)


$(BUILD_DIR)/$(EXEC): $(FICHIERS_O) $(BUILD_DIR)/exemple.o libHardware
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	$(CC) $(CFLAGS) -o $@ $(FICHIERS_O) $(BUILD_DIR)/exemple.o -lHardware $(LDFLAGS)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
