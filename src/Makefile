# Set this to 0 if you do not have METIS
CC = g++
CFLAGS=-O0 -g2 -D__LOG_ENABLE__

# source files.
OBJ = $(SRC:.cpp=.o)

# directories
OUTLIB=../lib/libdlb4vc.a
OUT=../bin/testgraph

# Unit tests
GTEST_DIR=../gtest-1.6.0
LIBGTEST=../lib/libgtest.a

# include directories
INCLUDES = -I../inc/
GTEST_INCLUDES= -I $(GTEST_DIR)/include -I $(GTEST_DIR)
# library paths
LIBDIR=-L../lib 
LIBS = $(LIBDIR) -lm
# source
SRC = Node.cpp Graph.cpp DimacsBuilder.cpp BuiderFactory.cpp main.cpp log.cpp

.SUFFIXES: .cpp

all: $(OUTLIB) $(OUT) $(LIBGTEST)

.cpp.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< $(LIBS)

$(OUTLIB): $(OBJ)
	ar -rv $(OUTLIB) $^

$(OUT): $(OBJ)
	$(CC) -I../inc $(CFLAGS) $^ -o $@ $(INCLUDES) $(LIBS) -L../lib

clean:
	rm -f *.o \#* PI* core* *~ $(OBJ) $(OUT) $(OUTLIB) $(LIBGTEST) *.log

#---- no change below this line--------------------------------------------------
gtest-all.o: ${GTEST_DIR}/src/gtest-all.cc
	$(CC) -c $< $(GTEST_INCLUDES)

gtest_main.o: ${GTEST_DIR}/src/gtest_main.cc
	$(CC) -c $< $(GTEST_INCLUDES)

$(LIBGTEST): gtest-all.o gtest_main.o
	ar -rv $(LIBGTEST) $^


# makefile tutorial: http://www.cs.duke.edu/~ola/courses/programming/Makefiles/node1.html
