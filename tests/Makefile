# Set this to 0 if you do not have METIS
CC = g++
CFLAGS=-O3 -D__LOG_ENABLE__

# source files.
OBJ = $(SRC:.cpp=.o)

# directories
OUTLIB=libdlb.a

# Unit tests
GTEST_DIR=../gtest-1.6.0

# include directories
INCLUDES = -I../inc/ -I $(GTEST_DIR)/include -I $(GTEST_DIR)
# library paths
LIBDIR=-L../lib 
LIBS = $(LIBDIR) -lm -lgtest -ldlb4vc -lpthread
# source
SRC = NodeTests.cpp

#.SUFFIXES: .cpp

EXE=NodeTests
all: $(EXE)

.cpp.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< $(LIBS)

NodeTests:NodeTests.o
	$(CC) $(INCLUDES) -o $@ $^ $(LIBS)

clean:
	@- $(RM) $(OBJ) $(EXE)

