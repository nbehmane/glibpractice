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
	@gdbus-codegen --generate-c-code application --interface-prefix ti.example. ./xml/ti.example.Application.xml
	@gdbus-codegen --generate-c-code leadvertisement --interface-prefix org.bluez. ./xml/org.bluez.LEAdvertisement.xml
	@mv application* ./gen
	@mv leadvertisement.* ./gen

# Commands to call over the bus
scanon:
	gdbus call -e -d ti.example -o /ti/example/Application -m ti.example.App.Scan 1 

scanoff:
	gdbus call -e -d ti.example -o /ti/example/Application -m ti.example.App.Scan 0 

getresults:
	gdbus call -e -d ti.example -o /ti/example/Application -m ti.example.App.GetScanResults 

advertise:
	gdbus call -e -d ti.example -o /ti/example/Application -m ti.example.App.advertise 

all: $(BIN)

clean:
	@echo "Cleaning..."
	@rm -r ./gen
	@rm *.o *.h.gch out
	
$(BIN): $(SRC) gen
	$(CC) $(CPPFLAGS) -c $(HDR) $(GENHDR) $(GENSRC) $(SRC)
	$(CC) $(OBJ) $(LDFLAGS) -o $(BIN)
