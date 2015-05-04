CC=gcc
CFLAGS=-Wall
LD=$(CC)
LDFLAGS=-lpthread
TARGET=toasty_client
OBJECTS=$(patsubst %.c, %.o, $(wildcard *.c))

%.o : $.c
	$(CC) $(CFLAGS) $^ -o $@

all: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(LD) $(LDFLAGS) $^ -o $@

clean:
	$(RM) $(TARGET) $(OBJECTS)