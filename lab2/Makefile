CSRC = cstring.c cfileutils.c cpersoana.c
COBJ = $(CSRC:.c=.o)

CPPSRC = agenda.cpp
CPPOBJ = $(CPPSRC:.cpp=.o)

CFLAGS = -pedantic -Wall -g
CPPFLAGS = ${CFLAGS}

.c.o:
	cc -c ${CFLAGS} $<

.cpp.o:
	c++ -c ${CPPFLAGS} $<

ctest: ${COBJ} ctesting.c
	cc -o $@ ${COBJ} ctesting.c

cpptest: ${CPPOBJ} ${COBJ} cpptesting.cpp
	c++ -o $@ ${CPPOBJ} ${COBJ} cpptesting.cpp

clean:
	rm -f ${COBJ} ${CPPOBJ}

.PHONY: clean ctest cpptest
