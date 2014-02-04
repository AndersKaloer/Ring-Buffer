#include <assert.h>
#include "../../ringbuffer.h"

int main(void) {
  uint8_t i, cnt;
  char buf;
  
  /* Create and initialize ring buffer */
  ring_buffer_t ring_buffer;
  ring_buffer_init(&ring_buffer);
  
  /* Add elements to buffer; one at a time */
  for(i = 0; i < 100; i++) {
    ring_buffer_queue(&ring_buffer, i);
  }

  /* Verify size */
  assert(ring_buffer_num_items(&ring_buffer) == 100);

  /* Peek third element */
  cnt = ring_buffer_peek(&ring_buffer, &buf, 3);
  /* Assert byte returned */
  assert(cnt == 1);
  /* Assert contents */
  assert(buf == 3);

  /* Dequeue all elements */
  for(cnt = 0; ring_buffer_dequeue(&ring_buffer, &buf) > 0; cnt++) {
    /* Do something with buf... */
    assert(buf == cnt);
  }

  /* Add array */
  ring_buffer_queue_arr(&ring_buffer, "Hello, Ring Buffer!", 20);

  /* Is buffer empty? */
  assert(!ring_buffer_is_empty(&ring_buffer));
  
  /* Is buffer full? */
  if(ring_buffer_is_full(&ring_buffer)) {
    /* What to do? */
  }
  
  return 0;
}
