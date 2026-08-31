CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude -lm

SRCS = src/ode.c src/system.c main.c
OBJS = $(SRCS:.c=.o)
TARGET = ode_solver

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o *.o $(TARGET) simulation.csv

.PHONY: all clean