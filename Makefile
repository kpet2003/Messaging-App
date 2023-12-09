CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS = -lm -lpthread -ldl -lrt
OBJS_A = process_a.o shared_memory.o ipc_functions.o
OBJS_B = process_b.o shared_memory.o ipc_functions.o 

EXEC_A = process_a
EXEC_B = process_b

all: $(EXEC_A) $(EXEC_B)

$(EXEC_A): $(OBJS_A)
	$(CC) $(OBJS_A) -o $(EXEC_A) $(LDFLAGS)

$(EXEC_B): $(OBJS_B)
	$(CC) $(OBJS_B) -o $(EXEC_B) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS_A) $(OBJS_B) $(EXEC_A) $(EXEC_B)

