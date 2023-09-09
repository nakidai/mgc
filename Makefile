CC     = tcc
CFLAGS =
OUT    = mgc

$(OUT) : mgc.c
	$(CC) $(CFLAGS) -o $@ $<

buildrun: $(OUT)
	./$(OUT) 10 9
