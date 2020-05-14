DEBUG = 0

CC = gcc
EXEC = ms2ampmax
#COMMON = -I./libmseed/ -I.
COMMON = -I/usr/local/ -I.
CFLAGS =  -Wall
#LDFLAGS = -L./libmseed -Wl,-rpath,./libmseed
LDFLAGS = -L/usr/local
#LDLIBS = -Wl,-Bstatic -lmseed -Wl,-Bdynamic -lm
LDLIBS = -lmseed -lm

OBJS = temp.o standard_deviation.o min_max.o

ifeq ($(DEBUG), 1)
CFLAGS += -O0 -g -DDEBUG=1
endif

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libmseed/ clean
	rm -rf $(OBJS) $(EXEC)
