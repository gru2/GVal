OPT_FLAGS = -g

CPPFLAGS = $(OPT_FLAGS) -I. -std=c++11

TARGETS = GValTest 

GVAL_TEST_OBJS=GValTest.o GVal.o ProgressReporter.o GValUtils.o Sutf.o \
GValParser.o toString.o MultiArrayIterator.o MultiArraySlice.o \
GValFormatter.o FileStream.o BinaryStream.o MemoryStream.o GValSerializer.o

all: $(TARGETS)

GValTest: $(GVAL_TEST_OBJS)
	g++ -o GValTest $(GVAL_TEST_OBJS)

%.o: %.cpp
	g++ -c $(CPPFLAGS) $< -o $@

clean::
	-rm -vf $(TARGETS) *.o

