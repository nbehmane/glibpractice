PACKAGES= gtk+-3.0
HDR=*.h
SRC=*.c
OBJ=*.o
OPTIMFLAGS=-g
PKG_CFLAGS= $(shell pkg-config --cflags $(PACKAGES))
CPPFLAGS=-Wall -pedantic $(OPTIMFLAGS) $(PKG_CFLAGS)
LDFLAGS= $(shell pkg-config --libs $(PACKAGES))
BIN=out

all: $(BIN)

clean:
	@echo "Cleaning..."
	@rm *.o *.h.gch out
	
$(BIN): $(SRC)
	$(CC) $(CPPFLAGS) -c $(HDR) $(SRC)
	$(CC) $(OBJ) $(LDFLAGS) -o $(BIN)
