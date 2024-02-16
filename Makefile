PACKAGES= gtk+-3.0
SRC=*.c
OBJ=*.o
OPTIMFLAGS=-g
PKG_CFLAGS= $(shell pkg-config --cflags $(PACKAGES))
CPPFLAGS=-Wall -W -ansi -pedantic $(OPTIMFLAGS) $(PKG_CFLAGS)
LDFLAGS= $(shell pkg-config --libs $(PACKAGES))
BIN=out

all: $(BIN)

clean:
	@echo "Cleaning..."
	@rm *.o out
	
$(BIN): $(SRC)
	$(CC) $(CPPFLAGS) -c $(SRC)
	$(CC) $(OBJ) $(LDFLAGS) -o $(BIN)
