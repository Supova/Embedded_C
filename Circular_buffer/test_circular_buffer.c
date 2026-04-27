/*
 * @file test_circular_buffer.c
 * @brief Unit tests for the circular buffer library.
 *
 * Tests cover: initialisation, enqueue/dequeue, FIFO ordering, peek,
 * full/empty boundary conditions, NULL pointer handling, wrap-around
 * behaviour, reset, and interleaved operations.
 *
 * Build and run via the Makefile:
 *   make test
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "circular_buffer.h"

static int tests_run    = 0;
static int tests_passed = 0;

#define CHECK(desc, expr)                                          \
    do {                                                           \
        tests_run++;                                               \
        if (expr) {                                                \
            printf("  PASS  %s\n", desc);                         \
            tests_passed++;                                        \
        } else {                                                   \
            printf("  FAIL  %s  (line %d)\n", desc, __LINE__);    \
        }                                                          \
    } while (0)


static void test_init(void)
{
    printf("\n[Init]\n");
    CircularBuffer cb;
    CircularBuffer_Init(&cb);

    CHECK("fresh buffer is empty",       CircularBuffer_IsEmpty(&cb));
    CHECK("fresh buffer is not full",    !CircularBuffer_IsFull(&cb));
    CHECK("fresh buffer count is 0",     CircularBuffer_Count(&cb) == 0);
}

static void test_enqueue_dequeue(void)
{
    printf("\n[Enqueue / Dequeue]\n");
    CircularBuffer cb;
    CircularBuffer_Init(&cb);

    CHECK("enqueue returns CB_SUCCESS",  CircularBuffer_Enqueue(&cb, 42) == CB_SUCCESS);
    CHECK("count is 1 after enqueue",    CircularBuffer_Count(&cb) == 1);
    CHECK("not empty after enqueue",     !CircularBuffer_IsEmpty(&cb));

    uint8_t val = 0;
    CHECK("dequeue returns CB_SUCCESS",  CircularBuffer_Dequeue(&cb, &val) == CB_SUCCESS);
    CHECK("dequeued correct value",      val == 42);
    CHECK("empty after dequeue",         CircularBuffer_IsEmpty(&cb));
    CHECK("count is 0 after dequeue",    CircularBuffer_Count(&cb) == 0);
}

static void test_fifo_order(void)
{
    printf("\n[FIFO order]\n");
    CircularBuffer cb;
    CircularBuffer_Init(&cb);

    CircularBuffer_Enqueue(&cb, 1);
    CircularBuffer_Enqueue(&cb, 2);
    CircularBuffer_Enqueue(&cb, 3);

    uint8_t a, b, c;
    CircularBuffer_Dequeue(&cb, &a);
    CircularBuffer_Dequeue(&cb, &b);
    CircularBuffer_Dequeue(&cb, &c);

    CHECK("first in, first out (a==1)",  a == 1);
    CHECK("first in, first out (b==2)",  b == 2);
    CHECK("first in, first out (c==3)",  c == 3);
}

static void test_peek(void)
{
    printf("\n[Peek]\n");
    CircularBuffer cb;
    CircularBuffer_Init(&cb);

    CircularBuffer_Enqueue(&cb, 99);

    uint8_t val = 0;
    CHECK("peek returns CB_SUCCESS",     CircularBuffer_Peek(&cb, &val) == CB_SUCCESS);
    CHECK("peek reads correct value",    val == 99);
    CHECK("peek does not remove item",   CircularBuffer_Count(&cb) == 1);

    // Peek on empty buffer
    CircularBuffer_Dequeue(&cb, &val);
    CHECK("peek on empty returns CB_ERROR_EMPTY",
          CircularBuffer_Peek(&cb, &val) == CB_ERROR_EMPTY);
}

static void test_full_buffer(void)
{
    printf("\n[Full buffer]\n");
    CircularBuffer cb;
    CircularBuffer_Init(&cb);

    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
        CircularBuffer_Enqueue(&cb, (uint8_t)i);
    }

    CHECK("buffer is full after BUFFER_SIZE enqueues", CircularBuffer_IsFull(&cb));
    CHECK("count equals BUFFER_SIZE",                  CircularBuffer_Count(&cb) == BUFFER_SIZE);
    CHECK("enqueue on full returns CB_ERROR_FULL",
          CircularBuffer_Enqueue(&cb, 0) == CB_ERROR_FULL);
}

static void test_empty_buffer(void)
{
    printf("\n[Empty buffer]\n");
    CircularBuffer cb;
    CircularBuffer_Init(&cb);

    uint8_t val;
    CHECK("dequeue on empty returns CB_ERROR_EMPTY",
          CircularBuffer_Dequeue(&cb, &val) == CB_ERROR_EMPTY);
    CHECK("peek on empty returns CB_ERROR_EMPTY",
          CircularBuffer_Peek(&cb, &val) == CB_ERROR_EMPTY);
}

static void test_null_pointer(void)
{
    printf("\n[NULL pointer handling]\n");
    uint8_t val;

    CHECK("Enqueue(NULL) returns CB_ERROR_NULL",  CircularBuffer_Enqueue(NULL, 1)   == CB_ERROR_NULL);
    CHECK("Dequeue(NULL) returns CB_ERROR_NULL",  CircularBuffer_Dequeue(NULL, &val) == CB_ERROR_NULL);
    CHECK("Peek(NULL) returns CB_ERROR_NULL",     CircularBuffer_Peek(NULL, &val)    == CB_ERROR_NULL);
    CHECK("IsFull(NULL) returns false",           CircularBuffer_IsFull(NULL)  == false);
    CHECK("IsEmpty(NULL) returns true",           CircularBuffer_IsEmpty(NULL) == true);
    CHECK("Count(NULL) returns 0",                CircularBuffer_Count(NULL)   == 0);
}

static void test_wrap_around(void)
{
    printf("\n[Wrap-around]\n");
    CircularBuffer cb;
    CircularBuffer_Init(&cb);

    // Fill halfway, drain halfway to shift the tail pointer mid-buffer
    for (uint16_t i = 0; i < BUFFER_SIZE / 2; i++) {
        CircularBuffer_Enqueue(&cb, (uint8_t)i);
    }
    uint8_t discard;
    for (uint16_t i = 0; i < BUFFER_SIZE / 2; i++) {
        CircularBuffer_Dequeue(&cb, &discard);
    }

    // Now fill completely — head must wrap around the array boundary
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
        CircularBuffer_Enqueue(&cb, (uint8_t)(i & 0xFF));
    }

    CHECK("full after wrap-around fill",  CircularBuffer_IsFull(&cb));

    // Verify FIFO order across the wrap boundary
    bool order_ok = true;
    for (uint16_t i = 0; i < BUFFER_SIZE; i++) {
        uint8_t val;
        CircularBuffer_Dequeue(&cb, &val);
        if (val != (uint8_t)(i & 0xFF)) {
            order_ok = false;
            break;
        }
    }
    CHECK("FIFO order preserved across wrap boundary", order_ok);
    CHECK("empty after draining wrapped buffer",       CircularBuffer_IsEmpty(&cb));
}

static void test_reset(void)
{
    printf("\n[Reset]\n");
    CircularBuffer cb;
    CircularBuffer_Init(&cb);

    CircularBuffer_Enqueue(&cb, 10);
    CircularBuffer_Enqueue(&cb, 20);
    CircularBuffer_Reset(&cb);

    CHECK("empty after reset",       CircularBuffer_IsEmpty(&cb));
    CHECK("count is 0 after reset",  CircularBuffer_Count(&cb) == 0);

    // Should be usable again after reset
    CHECK("enqueue after reset succeeds",
          CircularBuffer_Enqueue(&cb, 55) == CB_SUCCESS);
    uint8_t val;
    CircularBuffer_Dequeue(&cb, &val);
    CHECK("correct value after reset + enqueue", val == 55);
}

static void test_interleaved(void)
{
    printf("\n[Interleaved enqueue/dequeue]\n");
    CircularBuffer cb;
    CircularBuffer_Init(&cb);

    // Alternately enqueue and dequeue many times
    bool ok = true;
    for (uint8_t i = 0; i < 200; i++) {
        if (CircularBuffer_Enqueue(&cb, i) != CB_SUCCESS) { ok = false; break; }
        uint8_t val;
        if (CircularBuffer_Dequeue(&cb, &val) != CB_SUCCESS || val != i) { ok = false; break; }
    }
    CHECK("200 interleaved enqueue/dequeue cycles correct", ok);
    CHECK("empty after all interleaved ops", CircularBuffer_IsEmpty(&cb));
}

int main(void)
{
    printf("=== Circular Buffer Tests ===");

    test_init();
    test_enqueue_dequeue();
    test_fifo_order();
    test_peek();
    test_full_buffer();
    test_empty_buffer();
    test_null_pointer();
    test_wrap_around();
    test_reset();
    test_interleaved();

    printf("\n=============================\n");
    printf("Results: %d / %d passed\n", tests_passed, tests_run);
    printf("=============================\n");

    return (tests_passed == tests_run) ? 0 : 1;
}
