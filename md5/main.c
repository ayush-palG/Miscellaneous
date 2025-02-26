#define MD5_IMPLEMENTATION
#include "stb_md5.h"

int main(void)
{
  const char *file_digest = md5("input", 'f');
  printf("Message digest from file: %s\n", file_digest);

  const char *memory_digest = md5("abcdefghijklmnopqrstuvwxyz", 'm');
  printf("Message digest from memory: %s\n", memory_digest);
  
  return 0;
}
