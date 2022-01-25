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
	$(CXX) -o $@ $(SOURCES) $(CXXFLAGS) $(LDFLAGS)

clean:
	-$(RM) -rf main
