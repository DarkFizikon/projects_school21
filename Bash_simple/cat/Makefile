CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Werror -g
SRCS = s21_cat.c
OBJS = $(SRCS:.c=.o)
TARGET = s21_cat

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
