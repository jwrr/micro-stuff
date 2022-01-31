
#include "ring.h"

bool RING_init(ring_t *ring, uint8_t *buffer, uint16_t size)
{
    if (ring == NULL) return false;
    if (buffer == NULL) return false;
    ring->buffer = buffer;
    ring->wptr = buffer;
    ring->rptr = buffer;
    ring->len  = 0;
    ring->size = size;
    return true;
}

bool RING_isInit(ring_t *ring)
{
    if (ring == NULL) return false;
    return (ring->size > 0);
}

bool RING_isEmpty(ring_t *ring)
{
    if (ring == NULL) return true;
    return (ring->len == 0);
}

bool RING_hasData(ring_t *ring)
{
    if (ring == NULL) return false;
    return (ring->len != 0);
}

bool RING_isFull(ring_t *ring)
{
    if (ring == NULL) return true;
    return (ring->len >= ring->size);
}

uint16_t RING_getLen(ring_t *ring)
{
    return ring->len;
}

uint16_t RING_getSize(ring_t *ring)
{
    return ring->size;
}

uint16_t RING_getAvail(ring_t *ring)
{
    uint16_t spaceRemaining = RING_getSize(ring) - RING_getLen(ring);
    return spaceRemaining;
}

bool RING_push(ring_t *ring, uint8_t val)
{
    if (ring == NULL) return FAIL;
    if (RING_isFull(ring))
    {
        return FAIL;
    }

    *(ring->wptr) = val;
    ring->wptr++;
    ring->len++;
    if (ring->wptr == (ring->buffer + ring->size))
    {
        ring->wptr = ring->buffer;
    }
    return SUCCESS;
}

bool RING_write(ring_t *ring, uint8_t *data, uint16_t len)
{
    if (!RING_isInit(ring)) return false;
    if (len > RING_getAvail(ring)) return false;
    uint16_t i = 0;
    for (; i < len; i++)
    {
        RING_push(ring, data[i]);
    }
    return true;
}

bool RING_pop(ring_t *ring, uint8_t *valptr)
{
    if (ring == NULL) return FAIL;
    if (RING_isEmpty(ring))
    {
        return FAIL;
    }

    *valptr = *(ring->rptr);
    ring->rptr++;
    ring->len--;
    if (ring->rptr == ring->buffer + ring->size)
    {
        ring->rptr = ring->buffer;
    }
    return SUCCESS;
}

uint8_t RING_readOne(ring_t *ring)
{
    uint8_t val = 0;
    RING_pop(ring, &val);
    return val;
}

static uint16_t min(uint16_t a, uint16_t b)
{
    return (a < b) ? a : b;
}

uint16_t RING_read(ring_t *ring, uint8_t *data, uint16_t maxReadLen)
{
    if (ring == NULL) return 0;
    if (data == NULL) return 0;
    uint16_t ringLen = RING_getLen(ring);
    if (ringLen == 0) return 0;
    uint16_t readLen = min(ringLen, maxReadLen);
    uint16_t i = 0;
    for (; i < readLen; i++)
    {
        RING_pop(ring, &(data[i]));
    }
    return readLen;
}

bool RING_peek(ring_t *ring, uint16_t offset, uint8_t *valptr)
{
    if (ring == NULL) return FAIL;
    if (offset >= ring->len) return FAIL;

    uint8_t *peekPtr = ring->rptr + offset;
    uint16_t rptrOffsetCurr = (uint16_t)(ring->rptr - ring->buffer);
    uint16_t rptrOffsetNext = rptrOffsetCurr + offset;
    bool wrap = (rptrOffsetNext >= ring->size);
    if (wrap)
    {
        uint16_t rptrOffsetWrapped = rptrOffsetNext - ring->size;
        peekPtr = ring->buffer + rptrOffsetWrapped;
    }
    
    *valptr = *peekPtr;
    return SUCCESS;
}

ring_t *RING_new(uint16_t ringSize)
{
    ring_t *ring = (ring_t*)malloc(sizeof(ring_t));
    if (ring == NULL) {
        return NULL;
    }
    uint8_t *buffer = (uint8_t*)malloc(ringSize);
    if (buffer == NULL)
    {
        free(ring);
        return NULL;
    }

    RING_init(ring, buffer, ringSize);
    return ring;
}

void RING_free(ring_t *ring)
{
    if (ring == NULL) return;
    if (ring->buffer != NULL)
    {
        free(ring->buffer);
    }
    free(ring);
}

