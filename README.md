buffy.h
====
Simple string buffer implementation in C

## Installation
Download the `buffy.h` file, in one of your project files add `#define BUFFY_IMPL` BEFORE including the actual header and include the header simply by `#include "buffy.h"` wherever you desire.

## Usage Example
```c
#define BUFFY_IMPL
#include "buffy.h"
#include <stdio.h>

// for printing and testing purposes
void out(buffy_t *buf) {
  printf("%s\n", buf->data);
  printf("Capacity : %ld\tLength : %ld\n\n", buf->cap, buf->len);
}

int main(void) {
  // Create a buffer object and initialize it
  buffy_t buf;
  buffy_init(&buf, BUFFY_SMALL);

  // Add data to the buffer
  buffy_add(&buf, "lorem ipsum dolor sit amet");
  buffy_addl(&buf, "\ntest", 5);

  out(&buf);

  // Remove bytes from the buffer
  buffy_del(&buf, 5);

  out(&buf);

  // Zero initialize the buffer
  buffy_clear(&buf);

  out(&buf);

  // Free the memory
  buffy_free(&buf);
  return 0;
}
```

## Documentation

### `int buffy_init(buffy_t *buf, size_t sz)`
Initializes the buffer object. Allocates `sz` bytes for it

### `int buffy_add(buffy_t *buf, const char *str)`
Inserts bytes to the buffer. This function stops at string terminator `\0`.

### `int buffy_addl(buffy_t *buf, const char *str, size_t len)`
Inserts bytes to the buffer but length is decided by `len` parameter.

### `void buffy_sub(buffy_t *buf, size_t start, size_t end)`
Takes two position indexes and clears everything but between this positions.

### `void buffy_del(buffy_t *buf, size_t sz)`
Removes bytes from the right side (end) of the buffer.

### `void buffy_fill(buffy_t *buf, char c)`
Fills the buffer with the desired character `c`.

### `void buffy_clear(buffy_t *buf)`
Unfills (Zero initializing) the buffer.

### `void buffy_free(buffy_t *buf)`
Free the memory that's allocated by the buffer object.

## License
```
MIT License

Copyright (c) 2022 nikneym

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```