RAYLIB_LIB ?= ./deps/raylib/build/raylib/libraylib.a
RAYLIB_INC ?= ./deps/raylib/src
RM ?= rm -f

CFLAGS := -I$(RAYLIB_INC)
LDFLAGS := $(RAYLIB_LIB) -framework Cocoa -framework OpenGL -framework IOKit

main: main.o

main.o: main.c

clean:
	$(RM) main main.o
