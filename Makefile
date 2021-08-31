CC = gcc

SOURCE = source
SOURCE_EXT = c

BINARIES = bin
BINARIES_EXT = o

INCLUDE = include
INCLUDE_EXT = h

FLAGS = -Wall -Werror -Wpedantic -O2
PACKAGES = 


############################## SETTINGS ##############################


FLAGS += $(shell pkg-config --cflags --libs $(PACKAGES) 2> /dev/null)

BINDEPS = $(shell ls $(BINARIES)/* 2> /dev/null)
INCDEPS = $(shell ls $(INCLUDE)/* 2> /dev/null)
SRCDEPS = $(shell ls $(SOURCE)/* 2> /dev/null)
FULLDEPS = $(BINDEPS) $(INCDEPS)

main: main.$(SOURCE_EXT) $(FULLDEPS)
	$(CC) $(FLAGS)-I$(INCLUDE) -o $@ $< $(BINDEPS)

%: $(SOURCE)/%.$(SOURCE_EXT)
	$(CC) $(FLAGS)-I$(INCLUDE) -o $@ $< $(BINDEPS)

$(BINARIES)/%.$(BINARIES_EXT): $(SOURCE)/%.$(SOURCE_EXT) $(INCLUDE)/%.$(INCLUDE_EXT)
	$(CC) $(FLAGS)-I$(INCLUDE) -o $@ -c $<


init:
	- mkdir $(SOURCE)
	- mkdir $(BINARIES)
	- mkdir $(INCLUDE)
	touch main.c

var:
	@echo $(BINDEPS)
	@echo $(INCDEPS)
	@echo $(FULLDEPS)