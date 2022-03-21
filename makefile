CC = gcc
CFLAGS = -I.
DEPS = libImage.h
OBJ = libImage.o main.o 
LIBS = -lm
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

treat_image: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

