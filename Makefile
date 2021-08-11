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


FLAGS = $(shell pkg-config --cflags --libs $(PACKAGES) 2> /dev/null)

main: main.$(SOURCE_EXT) $(shell ls $(BINARIES)/* 2> /dev/null) $(shell ls $(INCLUDE)/* 2> /dev/null)
	$(CC) $(FLAGS) -I$(INCLUDE) -o $@ $< $(shell ls $(BINARIES)/* 2> /dev/null)

%: %.$(SOURCE_EXT) $(shell ls $(BINARIES)/* 2> /dev/null) $(shell ls $(INCLUDE)/* 2> /dev/null)
	$(CC) $(FLAGS) -I$(INCLUDE) -o $@ $< $(shell ls $(BINARIES)/* 2> /dev/null)

$(BINARIES)/%.$(BINARIES_EXT): $(SOURCE)/%.$(SOURCE_EXT) $(INCLUDE)/%.$(INCLUDE_EXT)
	$(CC) $(FLAGS) -I$(INCLUDE) -o $@ -c $<

init:
	- mkdir $(SOURCE)
	- mkdir $(BINARIES)
	- mkdir $(INCLUDE)
