#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFY_SMALL  (size_t) 64
#define BUFFY_MEDIUM (size_t) 512
#define BUFFY_LARGE  (size_t) 1024
#define BUFFY_XL     (size_t) 2048
#define BUFFY_XXL    (size_t) 4096

typedef struct buffy_t {
  char *data;
  size_t cap;
  size_t len;
} buffy_t;

// buffer initializer, must be called once
int buffy_init(buffy_t *buf, size_t sz) {
  buf->data = (char *)malloc(sizeof(char) * sz);
  if (buf->data == NULL)
    return 1;

  memset(buf->data, 0, sz);

  buf->cap = sz;
  buf->len = 0;

  return 0;
}

// insert bytes to the buffer
void buffy_add(buffy_t *buf, const char *str) {
  size_t sz = strlen(str);
  if ((buf->cap - buf->len) - 1 < sz) {
    buf->cap += sz - (buf->cap - buf->len) + 1;
    buf->data = realloc(buf->data, buf->cap);
  }

  //memmove(&buf->data[buf->len], str, sz);
  while (*str) {
    memset(&buf->data[buf->len], *str, 1);
    buf->len++;
    str++;
  }

  // terminate, just in case
  buf->data[buf->len] = '\0';
}

// insert bytes to the buffer but instead of string terminator,
// length parameter decides the size.
// this function is not as safe as buffy_add
void buffy_addl(buffy_t *buf, const char *str, size_t len) {
  if ((buf->cap - buf->len) - 1 < len) {
    buf->cap += len - (buf->cap - buf->len) + 1;
    buf->data = realloc(buf->data, buf->cap);
  }

  for (int i = 0; i < len; i++) {
    memset(&buf->data[buf->len], *str, 1);
    buf->len++;
    str++;
  }

  buf->data[buf->len] = '\0';
}

// sub the buffer
void buffy_sub(buffy_t *buf, size_t start, size_t end) {
  size_t len = end - start;
  if (len < 1)
    len = 1;

  memmove(&buf->data[0], &buf->data[start], len);
  memset(&buf->data[len], 0, buf->len - len);
  buf->len = len;
}

// remove bytes from the right side of the buffer
void buffy_del(buffy_t *buf, size_t sz) {
  if (sz <= 0 || sz > buf->len)
    return;

  memset(&buf->data[buf->len - sz], 0, sz);
  buf->len -= sz + 1;
}

// fill the buffer with the desired character
void buffy_fill(buffy_t *buf, char c) {
  buf->len = buf->cap - 1;
  memset(&buf->data[0], c, buf->len);
}

// unfill the buffer but do not realloc
void buffy_clear(buffy_t *buf) {
  memset(&buf->data[0], 0, buf->len);
  buf->len = 0;
}

// remove the buffer from the memory
void buffy_free(buffy_t *buf) {
  return free((void *)buf->data);
}