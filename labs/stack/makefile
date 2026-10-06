CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = stack

SRCS = stack.c
OBJS = $(SRCS:.c=.o)

run: clean $(TARGET)
	./$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
