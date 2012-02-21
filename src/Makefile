# Set this to 0 if you do not have METIS
CC = g++
CFLAGS=-O0 -g3 -D__LOG_ENABLE__
# source files.
OBJ = $(SRC:.cpp=.o)
#OUTLIB=../lib/libgraphdecomp.a
OUTLIB=../lib/libdlb4vc.a
OUT=../bin/testgraph
# include directories
INCLUDES = -I../inc/
# library paths
LIBDIR=-L../lib 
LIBS = $(LIBDIR) -lm
# source
SRC = Node.cpp Graph.cpp DimacsGraphBuilder.cpp BuiderFactory.cpp main.cpp log.cpp

.SUFFIXES: .cpp

all: $(OUTLIB) $(OUT)

.cpp.o:
	$(CC) $(INCLUDES) $(CFLAGS) -c $< $(LIBS)

$(OUTLIB): $(OBJ)
	ar -rv $(OUTLIB) $^

$(OUT): $(OBJ)
	$(CC) -I../inc $(CFLAGS) $^ -o $@ $(INCLUDES) $(LIBS) -L../lib 
clean:
	rm -f *.o \#* PI* ${EXECUTABLES} core *~ $(OBJ) $(OUT) $(OUTLIB) 

# makefile tutorial: http://www.cs.duke.edu/~ola/courses/programming/Makefiles/node1.html
