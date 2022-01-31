/*
 * File:   ring.h
 */

#ifndef RING_H
#define RING_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define RINGSIZE 256
#define FAIL false
#define SUCCESS true

typedef struct
{
    uint8_t *buffer;
    uint8_t *wptr;
    uint8_t *rptr;
    uint8_t *endptr;
    uint16_t len;
    uint16_t size;
} ring_t;

bool RING_init(ring_t *ring, uint8_t *buffer, uint16_t size);
bool RING_isInit(ring_t *ring);
bool RING_isEmpty(ring_t *ring);
bool RING_hasData(ring_t *ring);
bool RING_isFull(ring_t *ring);
uint16_t RING_getLen(ring_t *ring);
uint16_t RING_getSize(ring_t *ring);
uint16_t RING_getAvail(ring_t *ring);
bool RING_push(ring_t *ring, uint8_t val);
bool RING_write(ring_t *ring, uint8_t *data, uint16_t length);
bool RING_pop(ring_t *ring, uint8_t *valptr);
uint8_t RING_readOne(ring_t *ring);
uint16_t RING_read(ring_t *ring, uint8_t *data, uint16_t maxReadLen);
bool RING_peek(ring_t *ring, uint16_t offset, uint8_t *valptr);
ring_t *RING_new(uint16_t ringSize);
void RING_free(ring_t *ring);

#endif  /* RING_H */

