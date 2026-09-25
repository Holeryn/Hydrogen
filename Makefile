CC = gcc

CFLAGS = -Wall -Wextra -g

LIBS = -lGL -lGLU -lglut -lm

TARGET = HF

SRC = HF.c \
      numerics/numerics.c \
      numerics/schrodinger.c \
      graphics/graphics.c

OBJ = $(SRC:.c=.o)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: clean
