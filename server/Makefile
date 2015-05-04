CC=gcc
CFLAGS=-Wall
LD=$(CC)
LDFLAGS=-lpthread
TARGET=toasty_server
OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))

%.o : $.c
	$(CC) $(CFLAGS) $^ -c $@

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)