CC = gcc
CFLAGS = -Wall -Wextra -Wwrite-strings

STARGET = toasty_server
CTARGET = toasty_client

all: $(STARGET) $(CTARGET)

$(STARGET) : $(STARGET).c
	$(CC) $(CFLAGS) -o $(STARGET) $(STARGET).c

$(CTARGET) : $(CTARGET).c
	$(CC) $(CFLAGS) -o $(CTARGET) $(CTARGET).c

clean:
	rm $(STARGET) $(CTARGET)
