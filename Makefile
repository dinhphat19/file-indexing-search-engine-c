
CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99

TARGET = search_index

build:
	$(CC) $(CFLAGS) *.c -o $(TARGET)

clean:
	rm -f $(TARGET) *.o