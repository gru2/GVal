OPT_FLAGS = -g

CPPFLAGS = $(OPT_FLAGS) -I. -std=c++11

TARGETS = GValTest 

all: $(TARGETS)

GValTest: GValTest.o GVal.o GValProgressReporter.o Sutf.o
	g++ -o GValTest GValTest.o GVal.o GValProgressReporter.o Sutf.o

%.o: %.cpp
	g++ -c $(CPPFLAGS) $< -o $@

clean::
	-rm -vf $(TARGETS) *.o

