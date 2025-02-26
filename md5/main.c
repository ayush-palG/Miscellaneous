#define MD5_IMPLEMENTATION
#include "stb_md5.h"

int main(void)
{
  const char *digest = md5("input");
  printf("%s\n", digest);
  
  return 0;
}
