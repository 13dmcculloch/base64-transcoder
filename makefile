CC = gcc

CFLAGS = 

b64: b64.o b64_enc.o b64_dec.o b64_table.o
	$(CC) $(CFLAGS) -o b64 b64.o b64_enc.o b64_dec.o b64_table.o

b64.o: b64.c b64_enc.h b64_dec.h
	$(CC) $(CFLAGS) -c b64.c

b64_enc.o: b64_enc.c b64.h b64_enc.h
	$(CC) $(CFLAGS) -c b64_enc.c

b64_dec.o: b64_dec.c b64.h b64_dec.h
	$(CC) $(CFLAGS) -c b64_dec.c

b64_table.o: b64_table.c b64.h
	$(CC) $(CFLAGS) -c b64_table.c

clean:
	$(RM) b64 *.o *~
