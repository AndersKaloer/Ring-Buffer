/**
 * Equivalent to the Unix command 'tail -c 15'
 *
 *   $ printf JIHGFEDCBA9876543210 | ./tail ; echo
 *   EDCBA9876543210
 */
#include <stdio.h>
#include "../ringbuffer.h"

int main() {
  char c;
  char data[16];
  struct ring_buffer_t buffer;
  ring_buffer_init(&buffer, data, sizeof(data));

  while ((c = getchar()) != EOF)
    ring_buffer_queue(&buffer, c);

  while (ring_buffer_dequeue(&buffer, &c))
    putchar(c);

  return 0;
}
