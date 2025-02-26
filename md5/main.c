#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <math.h>

#define MD5_IMPLEMENTATION
#include "stb_md5.h"

int main(void)
{
  const char *file_path = get_padded_output_file();
  FILE *file = fopen(file_path, "rb");
  if (file == NULL) {
    fprintf(stderr, "ERROR: could not open output file %s: %s\n", file_path, strerror(errno));
    exit(1);
  }

  uint64_t file_size = get_file_size(file);
  int32_t data[16];

  uint32_t a0 = 0x67452301;
  uint32_t b0 = 0xefcdab89;
  uint32_t c0 = 0x98badcfe;
  uint32_t d0 = 0x10325476;
 
  while ((uint64_t) ftell(file) != file_size) {
    fseek(file, 0, SEEK_CUR);
    fread(&data, sizeof(data), 1, file);
    // for (size_t i = 0; i < 16; ++i) printf("%x\n", data[i]);

    uint32_t a = a0;
    uint32_t b = b0;
    uint32_t c = c0;
    uint32_t d = d0;

    for (size_t i = 0; i < 64; ++i) {
      // printf("%x\t%x\t%x\t%x\n", a, b, c, d);
      uint32_t func = get_non_linear_func(b, c, d, i);
      size_t index = get_current_index(i);

      func = func + a + key_constant[i] + data[index];
      
      a = d;
      d = c;
      c = b;
      uint32_t lr = left_rotate(func, shift_amount[i]);
      // printf("lr: %x, shift: %d\n", lr, shift_amount[i]);
      b = b + lr;
    }

    a0 += a;
    b0 += b;
    c0 += c;
    d0 += d;
    // printf("%x\t%x\t%x\t%x\n", a0, b0, c0, d0);
  }

  change_endian(&a0);
  change_endian(&b0);
  change_endian(&c0);
  change_endian(&d0);
  printf("%x%x%x%x\n", a0, b0, c0, d0);
  
  return 0;
}
