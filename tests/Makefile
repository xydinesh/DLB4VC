# Set this to 0 if you do not have METIS
CC = g++
CFLAGS=-O3 -D__LOG_ENABLE__

# source files.
OBJ = $(SRC:.cpp=.o)

# Unit tests
GTEST_DIR=../gtest-1.6.0

# include directories
INCLUDES = -I../inc/ -I $(GTEST_DIR)/include -I $(GTEST_DIR)
# library paths
LIBDIR=-L../lib 
LIBS = $(LIBDIR) -lm -lgtest -ldlb4vc -lpthread
# source
SRC = NodeTests.cpp GraphTests.cpp DimacsBuilderTests.cpp VertexCoverTests.cpp

.SUFFIXES: .cpp

EXE= NodeTests GraphTests DimacsBuilderTests VertexCoverTests

all:$(EXE)

.cpp.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< $(LIBS)

NodeTests:NodeTests.o
	$(CC) $(INCLUDES) -o $@ $^ $(LIBS)

GraphTests:GraphTests.o
	$(CC) $(INCLUDES) -o $@ $^ $(LIBS)

DimacsBuilderTests:DimacsBuilderTests.o
	$(CC) $(INCLUDES) -o $@ $^ $(LIBS)

VertexCoverTests:VertexCoverTests.o
	$(CC) $(INCLUDES) -o $@ $^ $(LIBS)

clean:
	@- $(RM) $(OBJ) $(EXE) *.log *~

test:$(EXE)
	for i in $^; do \
	./$$i;\
	done


