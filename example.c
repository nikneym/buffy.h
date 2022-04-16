#include <stdio.h>
#include "buffy.h"

void out(buffy_t *buf) {
  printf("%s\n", buf->data);
  printf("Capacity : %ld\tLength : %ld\n\n", buf->cap, buf->len);
}

int main(void) {
  buffy_t buf;
  buffy_init(&buf, BUFFY_SMALL);
  buffy_add(&buf, "lorem ipsum dolor sit amet");
  buffy_addl(&buf, "\ntest", 5);
  out(&buf);

  buffy_del(&buf, 5);
  out(&buf);

  buffy_clear(&buf);
  out(&buf);

  buffy_free(&buf);
  return 0;
}