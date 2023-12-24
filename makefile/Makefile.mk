//makefile 

CC = gcc
CFLAGS = -fsanitize=address
LDFLAGS = -lm

SRC = main.c boat.c game.c
SRH = main.h boat.h game.h
OBJ = $(SRC:.c=.o)
EXEC = my_code

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
    $(CC) $(CFLAGS) $(OBJ) -o $(EXEC) $(LDFLAGS)

$(OBJ): $(SRC) $(SRH)
    $(CC) $(CFLAGS) -c $< -o $@

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(EXEC)

