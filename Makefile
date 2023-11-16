CC = gcc
CFLAGS = -Wall -Werror -g
LDFLAGS = -lm -lpthread -ldl -lrt
OBJS_A = process_a.o shared_memory.o
OBJS_B = process_b.o shared_memory.o  # Use the same shared_memory.o for both processes

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

run_a: $(EXEC_A)
	./$(EXEC_A) $(ARGS)

run_b: $(EXEC_B)
	./$(EXEC_B) $(ARGS)

valgrind_a: $(EXEC_A)
	valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all ./$(EXEC_A) $(ARGS)

valgrind_b: $(EXEC_B)
	valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all ./$(EXEC_B) $(ARGS)
