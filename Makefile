PACKAGES= gio-2.0 gio-unix-2.0 glib-2.0
HDR=*.h
SRC=*.c
GENSRC=./gen/*.c
GENHDR=./gen/*.h
OBJ=*.o
OPTIMFLAGS=-g
PKG_CFLAGS= $(shell pkg-config --cflags $(PACKAGES))
CPPFLAGS=-Wall -pedantic $(OPTIMFLAGS) $(PKG_CFLAGS)
LDFLAGS= $(shell pkg-config --libs $(PACKAGES))
BIN=out

gen:
	@mkdir gen
	@gdbus-codegen --generate-c-code appinfo --interface-prefix ti.example. ./xml/ti.example.AppInfo.xml
	@gdbus-codegen --generate-c-code adapter --interface-prefix ti.example. ./xml/ti.example.Adapter.xml
	@mv appinfo* adapter* ./gen


appinfo:
	gdbus call -e -d ti.example -o /ti/example/AppInfo -m ti.example.AppInfo.Version 

adapter:
	gdbus call -e -d ti.example -o /ti/example/Adapter -m ti.example.Adapter.SetPower 0 
	gdbus call -e -d ti.example -o /ti/example/Adapter -m ti.example.Adapter.SetPower 1 

all: $(BIN)

clean:
	@echo "Cleaning..."
	@rm -r ./gen
	@rm *.o *.h.gch out
	
$(BIN): $(SRC) gen
	$(CC) $(CPPFLAGS) -c $(HDR) $(GENHDR) $(GENSRC) $(SRC)
	$(CC) $(OBJ) $(LDFLAGS) -o $(BIN)
