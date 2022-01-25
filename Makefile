RAYLIB_LIB ?= ./deps/raylib/build/raylib/libraylib.a
RAYLIB_INC ?= ./deps/raylib/src
RM ?= rm -f

CFLAGS := -I$(RAYLIB_INC)
LDFLAGS := $(RAYLIB_LIB) -framework Cocoa -framework OpenGL -framework IOKit

SOURCES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

main: $(SOURCES) $(HEADERS)
	$(CC) -o $@ $(SOURCES) $(CFLAGS) $(LDFLAGS)

clean:
	$(RM) main
