/*
 * @file circular_buffer.h
 * @brief Fixed-size circular buffer for uint8_t elements.
 *
 * This library provides a simple, safe circular buffer implementation
 * suitable for embedded applications.
 *
 * NULL pointer policy:
 *  - Operational functions (Enqueue, Dequeue, Peek, Reset) return an error
 *    code (CB_ERROR_NULL) if cb == NULL.
 *  - Query functions (IsFull, IsEmpty, Count) return safe neutral defaults:
 *      - IsEmpty(NULL) -> true
 *      - IsFull(NULL)  -> false
 *      - Count(NULL)   -> 0
 *
 * Error codes:
 *  - CB_SUCCESS       : Operation successful
 *  - CB_ERROR_FULL    : Buffer full, cannot enqueue
 *  - CB_ERROR_EMPTY   : Buffer empty, cannot dequeue/peek
 *  - CB_ERROR_NULL    : Invalid buffer pointer
 *
 * Usage example:
 *   CircularBuffer cb;
 *   CircularBuffer_Init(&cb);
 *   CircularBuffer_Enqueue(&cb, 42);
 *   uint8_t val;
 *   if (CircularBuffer_Dequeue(&cb, &val) == CB_SUCCESS) {
 *        use val
 *   }
*/

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 128

// Return codes
#define CB_SUCCESS 0
#define CB_ERROR_FULL -1
#define CB_ERROR_NULL -2
#define CB_ERROR_EMPTY -3

typedef struct{
    uint8_t buffer[BUFFER_SIZE];
    uint16_t head;
    uint16_t tail;
    uint16_t count;
}CircularBuffer;

void CircularBuffer_Init(CircularBuffer *cb);
int CircularBuffer_Enqueue(CircularBuffer *cb, uint8_t data);
int CircularBuffer_Dequeue(CircularBuffer *cb, uint8_t *data);
int CircularBuffer_Peek(CircularBuffer *cb, uint8_t *data);

bool CircularBuffer_IsFull(const CircularBuffer *cb);
bool CircularBuffer_IsEmpty(const CircularBuffer *cb);
uint16_t CircularBuffer_Count(const CircularBuffer *cb);
void CircularBuffer_Reset(CircularBuffer *cb);


#endif