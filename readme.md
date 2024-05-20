# GLib Practice
## Goals
1. Create example projects and structure for GDbus application development.
2. Create example projects aimed towards BlueZ

## Tools Needed
1. dbus-monitor
2. d-feet
3. gdbus

## Usage
1. Generate updated GDBus files: `make gen`
2. Run `make all`
3. Run `./out`
4. In a new terminal tab run `make call`

## Adding new method calls
TODO...


## TODO
1. The way scan returns objects is disgusting.
	- Find a more robust way to do this without exposing the user to GLIB.

