CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -pedantic

TARGET = birigui

SRC = main.c menu.c cidade.c problema.c
OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
