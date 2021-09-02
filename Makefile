CC = gcc

BASENAME = main

SRC_DIR = source
SRC_EXT = c

BIN_DIR = bin
BIN_EXT = o

INC_DIR = include
INC_EXT = h

FLAGS = -Wall -Werror -Wpedantic -O2
DEPS = 
PACKAGES = 

############################## SETTINGS ##############################

# get add packages dependencies to flags
FLAG += $(DEPS)
FLAGS += $(shell pkg-config --cflags --libs $(PACKAGES) 2> /dev/null)

SRC_FIL = $(shell ls $(SRC_DIR)/* 2> /dev/null)
BIN_FIL = $(shell ls $(BIN_DIR)/* 2> /dev/null)
INC_FIL = $(shell ls $(INC_DIR)/* 2> /dev/null)
BIN_INC_FIL = $(BIN_FIL) $(INC_FIL)

MAIN_RUL = $(shell $(CC) -MM $(BASENAME).$(SRC_EXT) 2>/dev/null | cut -d':' -f2-)
MAIN_SRC_DEP = $(shell ./dep_gen.sh none $(INC_EXT) $(SRC_DIR) $(SRC_EXT) $(MAIN_RUL))
MAIN_BIN_DEP = $(shell ./dep_gen.sh force $(SRC_EXT) $(BIN_DIR) $(BIN_EXT) $(MAIN_SRC_DEP))

OBJ_BAS = $(shell basename "$@" | cut -d'.' -f1)
OBJ_RUL = $(shell $(CC) -MM $(SRC_DIR)/$(OBJ_BAS).$(SRC_EXT) 2>/dev/null | cut -d' ' -f3-)
OBJ_SRC_DEP = $(shell ./dep_gen.sh none $(INC_EXT) $(SRC_DIR) $(SRC_EXT) $(OBJ_RUL))

$(BASENAME): $(MAIN_RUL) $(MAIN_SRC_DEP) $(MAIN_BIN_DEP)
	$(CC) $(FLAGS)-I$(INC_DIR) -o $(BASENAME) $(BASENAME).$(SRC_EXT) $(MAIN_BIN_DEP)

$(BIN_DIR)/%.$(BIN_EXT): $(OBJ_RUL) $(OBJ_SRC_DEP) $(OBJ_BIN_DEP)
	$(CC) $(FLAGS)-I$(INC_DIR) -o $@ -c $(SRC_DIR)/$(OBJ_BAS).$(SRC_EXT) $(OBJ_BIN_DEP)


init:
	-@mkdir $(INC_DIR) 				2> /dev/null	|| true
	-@mkdir $(SRC_DIR) 				2> /dev/null	|| true
	-@mkdir $(BIN_DIR) 				2> /dev/null	|| true
	@touch $(BASENAME).$(SRC_EXT) 	2> /dev/null
