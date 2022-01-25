RAYLIB_LIB ?= ./deps/raylib/build/raylib/libraylib.a
RAYLIB_INC ?= ./deps/raylib/src
RMRF ?= rm -rf
MD ?= mkdir
DENO ?= deno

CFLAGS := -I$(RAYLIB_INC) -I.
LDFLAGS := $(RAYLIB_LIB) -framework Cocoa -framework OpenGL -framework IOKit

SOURCES := $(wildcard *.c)
HEADERS := $(wildcard *.h)
SOURCES := $(subst scene_,gen/scene_,$(SOURCES))

main: $(SOURCES) $(HEADERS)
	$(CC) -o $@ $(SOURCES) $(CFLAGS) $(LDFLAGS)

gen/scene_%.c: scene_%.c
	-$(MD) gen 2>/dev/null
	$(DENO) run process.js $(basename $<) < $< > $@

clean:
	-$(RMRF) main gen
