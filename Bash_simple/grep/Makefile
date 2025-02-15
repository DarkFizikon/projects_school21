CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
SRCS = s21_grep.c
OBJS = $(SRCS:.c=.o)
TARGET = s21_grep

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
