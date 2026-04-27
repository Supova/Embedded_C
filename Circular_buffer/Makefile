CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -g

SRC     = circular_buffer.c
DEMO    = main.c
TEST    = test_circular_buffer.c

DEMO_BIN = demo_app
TEST_BIN = test_runner

.PHONY: all test demo clean

all: $(TEST_BIN) $(DEMO_BIN)

# Build and run the tests
test: $(TEST_BIN)
	./$(TEST_BIN)

$(TEST_BIN): $(SRC) $(TEST)
	$(CC) $(CFLAGS) $^ -o $@

# Build and run the demo (original main.c)
demo: $(DEMO_BIN)
	./$(DEMO_BIN)

$(DEMO_BIN): $(SRC) $(DEMO)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f $(TEST_BIN) $(DEMO_BIN)
