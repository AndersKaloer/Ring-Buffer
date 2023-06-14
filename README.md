Ring-Buffer
===========

A simple ring buffer (circular buffer) designed for embedded systems.

An example is given in [examples/simple.c](examples/simple.c).

The size of the memory buffer must be a power-of-two, and the ring buffer can contain at most `buf_size-1` bytes.

A new ring buffer is created using the ` ring_buffer_init(&ring_buffer, buff, sizeof(buff))` function:
```c
char buff[64];
ring_buffer_t ring_buffer;
ring_buffer_init(&ring_buffer, buff, sizeof(buff));
```
In this case, the buffer size is 64 bytes and the ring buffer can contain 63 bytes.

The module provides the following functions for accessing the ring buffer (documentation can be found in [ringbuffer.h](ringbuffer.h)):
```c
void ring_buffer_queue(ring_buffer_t *buffer, char data);
void ring_buffer_queue_arr(ring_buffer_t *buffer, const char *data, ring_buffer_size_t size);
uint8_t ring_buffer_dequeue(ring_buffer_t *buffer, char *data);
ring_buffer_size_t ring_buffer_dequeue_arr(ring_buffer_t *buffer, char *data, ring_buffer_size_t len);
uint8_t ring_buffer_peek(ring_buffer_t *buffer, char *data, ring_buffer_size_t index);
uint8_t ring_buffer_is_empty(ring_buffer_t *buffer);
uint8_t ring_buffer_is_full(ring_buffer_t *buffer);
ring_buffer_size_t ring_buffer_num_items(ring_buffer_t *buffer);
```
