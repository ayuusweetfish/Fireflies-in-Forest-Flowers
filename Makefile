# mkdir build; cd build; cmake .. -DCMAKE_BUILD_TYPE=Release
# emcmake cmake -S . -B build_wasm -DCMAKE_BUILD_TYPE=Release -DPLATFORM=Web

TARGET = main

ifeq ($(WEB),1)
  CXX = emcc
  RAYLIB_LIB ?= ./deps/raylib/build_wasm/raylib/libraylib.a
  TARGET = web/index.html
  EXTRAFLAGS ?= -O3 -o $(TARGET) -s USE_GLFW=3 --preload-file res --shell-file shell.html -DPLATFORM_WEB -s ASYNCIFY -s TOTAL_MEMORY=67108864
  EXTRASTEP = $(MD) web 2>/dev/null
endif

ifeq ($(shell uname),Darwin)
  EXTRAFLAGS ?= -framework Cocoa -framework OpenGL -framework IOKit
endif

RAYLIB_LIB ?= ./deps/raylib/build/raylib/libraylib.a
RAYLIB_INC ?= ./deps/raylib/src
RM ?= rm
MD ?= mkdir

CXXFLAGS := -I$(RAYLIB_INC) -I. -std=c++11
LDFLAGS := $(RAYLIB_LIB)

SOURCES := $(wildcard *.cc)
HEADERS := $(wildcard *.hh)

$(TARGET): $(SOURCES) $(HEADERS)
	-$(EXTRASTEP)
	$(CXX) -o $@ $(SOURCES) $(CXXFLAGS) $(LDFLAGS) $(EXTRAFLAGS)

clean:
	-$(RM) -rf main
