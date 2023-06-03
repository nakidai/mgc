CC     = gcc
CFLAGS =
OUT    = mgc

$(OUT) : mgc.c
	$(CC) $(CFLAGS) -o $@ $<
