PROJECT=cartographie
default: all
# Default Options
export ARCH  ?= PC
export ROBOT ?= gros
export SDL   ?= yes
export DEBUG ?= 0

PARENT_DIR = ../

# Constantes de compilation
EXEC    = carto_robot

include $(PARENT_DIR)/hardware/common.mk
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
.PHONY: all view

all: $(EXEC)

view: $(EXEC)
	./$^

_libCarto: $(CARTO_LIB)

$(CARTO_LIB): $(FICHIERS_O)

$(EXEC): $(FICHIERS_O) $(BUILD_DIR)/exemple.o libHardware
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(HARDW_LIB) $(LDFLAGS) -o $@ $(FICHIERS_O) $(BUILD_DIR)/exemple.o

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)


################################################################################
# Cibles génériques

mrproper: clean
	@echo "Hard-cleaning  $(PROJECT) directory…"
	@rm -rf $(EXEC) $(LIBCARTO)
