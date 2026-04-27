#include "circular_buffer.h"
#include <stddef.h>

void CircularBuffer_Init(CircularBuffer *cb){
    if (cb == NULL){
        return;
    }

    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

int CircularBuffer_Enqueue(CircularBuffer *cb, uint8_t data){
    if (cb == NULL){
        return CB_ERROR_NULL;
    }
    
    // reject data overwrite
    if (CircularBuffer_IsFull(cb)){
        return CB_ERROR_FULL;
    }

    cb->buffer[cb->head] = data;
    cb->head = (cb->head + 1) % BUFFER_SIZE;
    cb->count++;

    return CB_SUCCESS;
}

int CircularBuffer_Dequeue(CircularBuffer *cb, uint8_t *data){
    if (cb == NULL){
        return CB_ERROR_NULL;
    }

    if (CircularBuffer_IsEmpty(cb)){
        return CB_ERROR_EMPTY;
    }

    *data = cb->buffer[cb->tail];
    cb->tail = (cb->tail + 1) % BUFFER_SIZE;
    cb->count--;

    return CB_SUCCESS;
}

int CircularBuffer_Peek(CircularBuffer *cb, uint8_t *data){
    if (cb == NULL){
        return CB_ERROR_NULL;
    }

    if (CircularBuffer_IsEmpty(cb)){
        return CB_ERROR_EMPTY;
    }
    
    *data = cb->buffer[cb->tail];

    return CB_SUCCESS;
}

bool CircularBuffer_IsFull(const CircularBuffer *cb){
    if (cb == NULL){
        return false;
    }

    return cb->count == BUFFER_SIZE;
}

bool CircularBuffer_IsEmpty(const CircularBuffer *cb){
    if (cb == NULL){
        return true;
    }

    return cb->count == 0;
}

uint16_t CircularBuffer_Count(const CircularBuffer *cb){
     if (cb == NULL){
        return 0;
    }

    return cb->count;
}

void CircularBuffer_Reset(CircularBuffer *cb){
     if (cb == NULL){
        return;
    }

    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}



