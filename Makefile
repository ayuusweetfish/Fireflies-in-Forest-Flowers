# For web:
# make CXX=emcc LDFLAGS=deps/raylib/build_web/raylib/libraylib.a EXTRAFLAGS="-O2 -o game.html -s USE_GLFW=3 --preload-file res --shell-file deps/raylib/src/minshell.html -s ASYNCIFY -DPLATFORM_WEB"
RAYLIB_LIB ?= ./deps/raylib/build/raylib/libraylib.a
RAYLIB_INC ?= ./deps/raylib/src
RM ?= rm
MD ?= mkdir
DENO ?= deno

CXXFLAGS := -I$(RAYLIB_INC) -I. -std=c++11
LDFLAGS := $(RAYLIB_LIB) -framework Cocoa -framework OpenGL -framework IOKit

SOURCES := $(wildcard *.cc)
HEADERS := $(wildcard *.hh)

main: $(SOURCES) $(HEADERS)
	$(CXX) -o $@ $(SOURCES) $(CXXFLAGS) $(LDFLAGS) $(EXTRAFLAGS)

clean:
	-$(RM) -rf main
