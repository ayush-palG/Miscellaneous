#define BITMAP_IMPLEMENTATION
#include "bitmap.h"

int main()
{
  Bitmap bitmap = init_bitmap(5, 5);
  fill(bitmap, 0, 0, 5, 5, hex_to_color(0x00FFFF));
  write_bitmap(bitmap, "out.bmp");
  free_bitmap(bitmap);
  
  return 0;
}

