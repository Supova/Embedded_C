#include <stdio.h>

#include "circular_buffer.h"

int main() {
  CircularBuffer cb;
  CircularBuffer_Init(&cb);
  CircularBuffer_Enqueue(&cb, 25);
  CircularBuffer_Enqueue(&cb, 30);

  uint8_t value;
  int ret = CircularBuffer_Peek(&cb, &value);
    if (ret == CB_SUCCESS) {
        printf("Peeked value: %d\n", value);
    } else {
        printf("Peek failed, error code: %d\n", ret);
    }

    ret = CircularBuffer_Dequeue(&cb, &value);
    if (ret == CB_SUCCESS) {
        printf("Dequeued value: %d\n", value);
    }

    return 0;
}