BASE_DIR = /usr/local




CXXFLAGS = -std=gnu++11 -I. -Werror -Wno-unused-result


ifeq ($(opt),1)
  CXXFLAGS += -Os -march=i686 -fomit-frame-pointer
  LDFLAGS  += -s
else
  CXXFLAGS += -g
endif


COMMON_LDFLAGS = -lstdc++


ifeq ($(mingw),1)
  EXE_EXT = .exe
  DIR_PREFIX = i686-w64-mingw32
  CMD_PREFIX = $(DIR_PREFIX)-
  LDFLAGS = $(COMMON_LDFLAGS) -lmingw32 -static
else
  LDFLAGS = $(COMMON_LDFLAGS)
endif




ifeq ($(ccache),1)
  CXX = CCACHE_DIR=/tmp/ccachedir ccache $(CMD_PREFIX)g++
else
  CXX = $(CMD_PREFIX)g++
endif



STRIP = $(CMD_PREFIX)strip
AR    = $(CMD_PREFIX)ar

CXXFLAGS += -I$(BASE_DIR)/$(DIR_PREFIX)/include
LDFLAGS  += -L$(BASE_DIR)/$(DIR_PREFIX)/lib


ifeq ($(delay),1)
%.o : %.cpp
	$(CXX) -c $(CXXFLAGS)  $< -o $@
	sleep 1
endif


OBJ +=                        \
  minpp_position.o            \
  minpp_folder.o              \
  minpp_stream.o              \
  minpp_character.o           \
  minpp_string.o              \
  minpp_unicode.o             \
  minpp_utf8chunk.o           \


all: $(OBJ) test_minpp


clean:
	rm -f $(OBJ) test_minpp test.o


objects: $(OBJ)


test_minpp: $(OBJ) test.o
	g++ $(OBJ) test.o -o $@ $(CXXFLAGS)




