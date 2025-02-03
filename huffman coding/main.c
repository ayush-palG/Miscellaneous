#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char ch;
  int count;
} Frequency;

int get_text_length(const char* text)
{
  int counter = 0;
  while (text[counter] != 0) counter++;
  return counter;
}

Frequency* init_frequency(void)
{
  Frequency* freq = (Frequency*) malloc(256 * sizeof(Frequency));

  for (size_t i = 0; i < 256; ++i) {
    freq[i].ch = (char) i;
    freq[i].count = 0;
  }

  return freq;
}

Frequency* get_frequency(const char* text)
{
  Frequency* freq = init_frequency();
  int text_length = get_text_length(text);
  
  for (size_t i = 0; i < text_length; ++i) {
    freq[(int) text[i]].count += 1;
  }

  return freq;
}

void print_frequency(Frequency* freq)
{
  for (size_t i = 0; i < 256; ++i) {
    if (freq[i].count > 0) {
      printf("%zu (%c) -> %d\n", i, (char)i, freq[i].count);
    }
  }
}

void get_huffman_tree(const char* text)
{
  if (get_text_length(text) == 0) return;
  Frequency* freq = get_frequency(text);
  print_frequency(freq);
}

int main(void)
{
  get_huffman_tree("asdasdssss");
}
