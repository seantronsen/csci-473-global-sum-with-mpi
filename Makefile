CFLAGS = -g  -Wall -Wstrict-prototypes
PROGS = driver
OBJECTS = gsum.o functions.o
LDFLAGS = -lm -ldl
CC = gcc
MCC = mpicc

all: $(PROGS)


driver: $(OBJECTS)
	$(MCC)  -o driver $(OBJECTS) $(LDFLAGS)

gsum.o: gsum.c
	$(MCC) $(CFLAGS) -c gsum.c

functions.o: functions.c functions.h
	$(MCC) $(CFLAGS) -c functions.c


clean:
	rm -f $(PROGS) *.o core* *.out