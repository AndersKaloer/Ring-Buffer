#include <assert.h>
#include <stdio.h>
#include "../ringbuffer.h"

int main(void) {
  int i, cnt;
  char tmp;
  char tmp_arr[50];
  
  /* Create and initialize ring buffer */
  ring_buffer_t ring_buffer;
  char buf_arr[128];
  ring_buffer_init(&ring_buffer, buf_arr, sizeof(buf_arr));
  
  /* Add elements to buffer; one at a time */
  for(i = 0; i < 100; i++) {
    ring_buffer_queue(&ring_buffer, i);
  }

  /* Verify size */
  assert(ring_buffer_num_items(&ring_buffer) == 100);

  /* Peek third element */
  cnt = ring_buffer_peek(&ring_buffer, &tmp, 3);
  /* Assert byte returned */
  assert(cnt == 1);
  /* Assert contents */
  assert(tmp == 3);

  /* Dequeue all elements */
  for(cnt = 0; ring_buffer_dequeue(&ring_buffer, &tmp) > 0; cnt++) {
    /* Do something with buf... */
    assert(tmp == cnt);
    printf("Read: %d\n", tmp);
  }
  printf("\n===============\n");

  /* Add array */
  ring_buffer_queue_arr(&ring_buffer, "Hello, Ring Buffer!", 20);

  /* Is buffer empty? */
  assert(!ring_buffer_is_empty(&ring_buffer));

  /* Dequeue all elements */
  while(ring_buffer_dequeue(&ring_buffer, &tmp) > 0) {
    /* Print contents */
    printf("Read: %c\n", tmp);
  }
  
  /* Add new array */
  ring_buffer_queue_arr(&ring_buffer, "Hello again, Ring Buffer!", 26);
  
  /* Dequeue array in two parts */
  printf("Read:\n");
  cnt = ring_buffer_dequeue_arr(&ring_buffer, tmp_arr, 13);
  printf("%d\n", cnt);
  assert(cnt == 13);
  /* Add \0 termination before printing */
  tmp_arr[13] = '\0';
  printf("%s\n", tmp_arr);
  /* Dequeue remaining */
  cnt = ring_buffer_dequeue_arr(&ring_buffer, tmp_arr, 13);
  assert(cnt == 13);
  printf("%s", tmp_arr);
  

  printf("\n===============\n");

  /* Overfill buffer */
  for(i = 0; i < 1000; i++) {
    ring_buffer_queue(&ring_buffer, (i % 127));
  }
  
  /* Is buffer full? */
  if(ring_buffer_is_full(&ring_buffer)) {
    cnt = ring_buffer_num_items(&ring_buffer);
    printf("Buffer is full and contains %d bytes\n", cnt);
  }
  
  /* Dequeue all elements */
  while(ring_buffer_dequeue(&ring_buffer, &tmp) > 0) {
    /* Print contents */
    printf("Read: 0x%02x\n", tmp);
  }
  
  return 0;
}
