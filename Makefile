PACKAGES= gio-2.0 gio-unix-2.0 glib-2.0
HDR=*.h
SRC=*.c
OBJ=*.o
OPTIMFLAGS=-g
PKG_CFLAGS= $(shell pkg-config --cflags $(PACKAGES))
CPPFLAGS=-Wall -pedantic $(OPTIMFLAGS) $(PKG_CFLAGS)
LDFLAGS= $(shell pkg-config --libs $(PACKAGES))
BIN=out

gen:
	@gdbus-codegen --generate-c-code objecttest --interface-prefix ti.example. ti.example.ObjectTest.xml

call:
	gdbus call -e -d ti.example -o /ti/example/ObjectTest -m ti.example.ObjectTest.HelloWorld nima
	gdbus call -e -d ti.example -o /ti/example/ObjectTest -m ti.example.ObjectTest.setNumbers [1,2]
	gdbus call -e -d ti.example -o /ti/example/ObjectTest -m ti.example.ObjectTest.Add

all: $(BIN)

clean:
	@echo "Cleaning..."
	@rm *.o *.h.gch out
	
$(BIN): $(SRC)
	$(CC) $(CPPFLAGS) -c $(HDR) $(SRC)
	$(CC) $(OBJ) $(LDFLAGS) -o $(BIN)
