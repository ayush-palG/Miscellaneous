#ifndef BITMAP
#define BITMAP

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} color_t;

typedef struct {
  int width;
  int height;
  color_t *pixels;
} Bitmap;

// Creating and destroying bitmaps
Bitmap init_bitmap(int width, int height);
void free_bitmap(Bitmap bitmap);

// Drawing on the Bitmap
void set_pixel(Bitmap bitmap, int x, int y, color_t color);
void fill(Bitmap bitmap, int x1, int y1, int x2, int y2, color_t color);

// MISCELLANEOUS
int calc_row_size(int width);
int calc_image_size(int width, int height);
color_t hex_to_color(unsigned int hex_color);

// Writing the file
void write_bitmap(Bitmap bitmap, const char* filename);
void write_fileheader(int width, int height, FILE *file);
void write_infoheader(int width, int height, FILE *file);
void write_pixeldata(Bitmap bitmap, FILE *file);

#endif // BITMAP

#ifdef BITMAP_IMPLEMENTATION

Bitmap init_bitmap(int width, int height)
{
  color_t *pixels = malloc(width * height * sizeof(color_t));
  Bitmap bitmap = {
    .width = width,
    .height = height,
    .pixels = pixels,
  };
  
  return bitmap;
}

void free_bitmap(Bitmap bitmap)
{
  free(bitmap.pixels);
  // Or else I would be left with the pointer to freed memory in the struct
  bitmap.pixels = NULL;
}

void set_pixel(Bitmap bitmap, int x, int y, color_t color)
{
  if (x < 0 || x >= bitmap.width || y < 0 || y >= bitmap.height) return;
  bitmap.pixels[y*bitmap.width + x] = color;
}

void fill(Bitmap bitmap, int x1, int y1, int x2, int y2, color_t color)
{
  if (x1 > x2 || y1 > y2) return;

  for (size_t j = y1; j <= y2; ++j) {
    for (size_t i = x1; i <= x2; ++i) {
      set_pixel(bitmap, i, j, color);
    }
  }
}

int calc_row_size(int width) {
  int row_length = width * 3;
  row_length += 4 - (row_length % 4);
  assert(row_length % 4 == 0);
  return row_length;
}

int calc_image_size(int width, int height)
{
  return calc_row_size(width) * height;
}

color_t hex_to_color(unsigned int hex_color)
{
  color_t color = {
    .red = (hex_color & 0xFF0000) >> 16,
    .green = (hex_color & 0x00FF00) >> 8,
    .blue = (hex_color & 0x0000FF) >> 0,
  };
  return color;
}

void write_bitmap(Bitmap bitmap, const char* filename)
{
  FILE *file = fopen(filename, "wb");
  if (file == NULL) return;

  write_fileheader(bitmap.width, bitmap.height, file);
  write_infoheader(bitmap.width, bitmap.height, file);

  write_pixeldata(bitmap, file);
  
  fclose(file);
}

void write_fileheader(int width, int height, FILE* file)
{
  fputs("BM", file);

  int file_size = 14 + 40 + calc_image_size(width, height);
  fwrite(&file_size, sizeof(file_size), 1, file);

  int reserved = 0;
  fwrite(&reserved, sizeof(reserved), 1, file);
  
  int offset = 14 + 40;
  fwrite(&offset, sizeof(offset), 1, file);
}

void write_infoheader(int width, int height, FILE *file)
{
  int header_size = 40;
  int planes = 1;
  int bits_per_pixel = 24;
  int compression = 0;
  int image_size = calc_image_size(width, height);
  int x_pixels_per_meter = 0;
  int y_pixels_per_meter = 0;
  int colors_used = 0;
  int important_colors_used = 0;

  fwrite(&header_size , 4, 1, file);
  fwrite(&width , 4, 1, file);
  fwrite(&height , 4, 1, file);
  fwrite(&planes , 2, 1, file);
  fwrite(&bits_per_pixel , 2, 1, file);
  fwrite(&compression , 4, 1, file);
  fwrite(&image_size , 4, 1, file);
  fwrite(&x_pixels_per_meter , 4, 1, file);
  fwrite(&y_pixels_per_meter , 4, 1, file);
  fwrite(&colors_used , 4, 1, file);
  fwrite(&important_colors_used , 4, 1, file);
}

void write_pixeldata(Bitmap bitmap, FILE *file)
{
  int row_size = calc_row_size(bitmap.width);

  for (int y = bitmap.height-1; y >= 0; --y) {
    for (int x = 0; x < bitmap.width; ++x) {
      color_t color = bitmap.pixels[y*bitmap.width + x];
      fwrite(&color.blue, 1, 1, file);
      fwrite(&color.green, 1, 1, file);
      fwrite(&color.red, 1, 1, file);
    }

    for (int i = bitmap.width * 3; i < row_size; ++i) {
      fputc(0, file);
    }
  }
}

#endif // BITMAP_IMPLEMENTATION
