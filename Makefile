PROJECT=cartographie

# Default Options
export ARCH  = PC
export ROBOT = gros
export SDL   = yes
export DEBUG = _WARNING_

export PARENT_DIR = ../
include $(PARENT_DIR)/common_code/common.mk

# Constantes de compilation
EXEC    = carto_robot
LIBCARTO= libCartographie


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

FICHIERS_H = $(FICHIERS_C:.c=.h)
FICHIERS_O  += $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )

################################################################################

.PHONY:view

all: $(EXEC)

view: $(EXEC)
	./$^

$(EXEC): $(FICHIERS_O) $(BUILD_DIR)/exemple.o $(COMMON_DIR)/$(BUILD_DIR)/libCommon.a
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) -o $@ $^ $(LDFLAGS)

libCartographie.a: $(FICHIERS_O)
	@echo "	AR	$@"
	@$(AR) -q $@ $(FICHIERS_O)
	@echo "	RANLIB	$@"
	@$(RANLIB) $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	@mkdir $(BUILD_DIR) $ -p

$(COMMON_DIR)/$(BUILD_DIR)/libCommon.a:
	@$(MAKE) ARCH=$(ARCH) ROBOT=$(ROBOT) SDL=$(SDL) DEBUG=$(DEBUG) -C $(COMMON_DIR) libCommon


################################################################################
# Cibles génériques

.PHONY: clean mrproper

clean:
	@echo "Cleaning $(PROJECT) directory…"
	@find $(BUILD_DIR) -name '*.o' -delete
	@rmdir -p --ignore-fail-on-non-empty $(BUILD_DIR)/*/* 2>/dev/null || true

mrproper: clean
	@echo "Hard-cleaning  $(PROJECT) directory…"
	@rm -rf $(EXEC) $(PIC_ELF) $(PIC_HEX)
