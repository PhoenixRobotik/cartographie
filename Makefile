PROJECT=cartographie

# Default Options
export ARCH  = dsPIC
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

libCartographie: $(BUILD_DIR)/libCartographie.a

view: $(EXEC)
	./$^

$(EXEC): $(FICHIERS_O) $(BUILD_DIR)/exemple.o $(COMMON_DIR)/$(BUILD_DIR)/libCommon.a
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	$(CC) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/libCartographie.a: $(FICHIERS_O)
	@echo "	AR	$(PROJECT)|$(notdir $@)"
	@rm -f $@
	@$(AR) -r $@ $^
	@echo "	RANLIB	$(PROJECT)|$(notdir $@)"
	@$(RANLIB) $@

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	@echo "	CC	$(PROJECT)|$(notdir $@)"
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(COMMON_DIR)/$(BUILD_DIR)/libCommon.a:
	@$(MAKE) ARCH=$(ARCH) ROBOT=$(ROBOT) SDL=$(SDL) DEBUG=$(DEBUG) -C $(COMMON_DIR) libCommon


################################################################################
# Cibles génériques

.PHONY: clean mrproper

clean:
	@echo "Cleaning $(PROJECT) directory…"
	@rm -rf build/

mrproper: clean
	@echo "Hard-cleaning  $(PROJECT) directory…"
	@rm -rf $(EXEC) $(PIC_ELF) $(PIC_HEX)
