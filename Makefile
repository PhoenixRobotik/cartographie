PROJECT=cartographie
default: all
# Default Options
export ARCH  ?= PC
export ROBOT ?= gros
export SDL   ?= yes
export DEBUG ?= _WARNING_

export PARENT_DIR = ../
include $(PARENT_DIR)/hardware/common.mk

################################################################################
# Fichiers du projet

EXEC    = carto_robot

FICHIERS_C = \
	geometrie.c \
	obstacles.c \
	point.c \
	pointList.c \
	bestInFirstOut.c \
	cartographie.c \
	astar.c \
	debug.c

FICHIERS_H = $(FICHIERS_C:.c=.h)
FICHIERS_O  += $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )

################################################################################

.PHONY: all view

all: $(EXEC)

view: $(EXEC)
	./$^

libCartographie: $(BUILD_DIR)/libCartographie.a

$(BUILD_DIR)/libCartographie.a: $(FICHIERS_O)

$(EXEC): $(FICHIERS_O) $(BUILD_DIR)/exemple.o $(COMMON_DIR)/$(BUILD_DIR)/libCommon.a
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	$(CC) -o $@ $^ $(LDFLAGS)


$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(COMMON_DIR)/$(BUILD_DIR)/libCommon.a:
	@$(MAKE) ARCH=$(ARCH) ROBOT=$(ROBOT) SDL=$(SDL) DEBUG=$(DEBUG) -C $(COMMON_DIR) libCommon
