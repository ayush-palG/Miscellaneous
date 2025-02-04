#include <stdio.h>
#include <stdlib.h>

#define CHAR_SIZE 256

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
  Frequency* freq = (Frequency*) malloc(CHAR_SIZE * sizeof(Frequency));

  for (size_t i = 0; i < CHAR_SIZE; ++i) {
    freq[i].ch = (char) i;
    freq[i].count = 0;
  }

  return freq;
}

int get_frequency_length(const Frequency* freq)
{
  int counter = 0;

  for (size_t i = 0; i < CHAR_SIZE; ++i) {
    if (freq[i].count > 0) counter++;
  }

  return counter;
}

void print_frequency(const Frequency* freq)
{
  int freq_size = get_frequency_length(freq);
  
  for (size_t i = 0; i < freq_size; ++i) {
    if (freq[i].count >= 0) {
      printf("%d (%c) -> %d\n", freq[i].ch, freq[i].ch, freq[i].count);
    }
  }
  printf("\n");
}

void ssort_frequency(Frequency* freq)
{
  int freq_size = get_frequency_length(freq);
  
  for (size_t i = 0; i < freq_size; ++i) {
    int min_index = i;
    
    for (size_t j = i+1; j < freq_size; ++j) {
      if (freq[j].count < freq[min_index].count) min_index = j;
    }
    
    Frequency temp_freq = freq[i];
    freq[i] = freq[min_index];
    freq[min_index] = temp_freq;
  }
}

Frequency* get_eff_frequency(Frequency* frequency)
{
  int freq_size = get_frequency_length(frequency);
  Frequency* freq = (Frequency*) malloc(freq_size * sizeof(Frequency));

  for (size_t i = 0, j = 0; i < CHAR_SIZE && j < freq_size; ++i) {
    if (frequency[i].count > 0) freq[j++] = frequency[i];
  }

  free(frequency);
  ssort_frequency(freq);

  return freq;
}

Frequency* get_frequency(const char* text)
{
  Frequency* freq = init_frequency();
  int text_length = get_text_length(text);
  
  for (size_t i = 0; i < text_length; ++i) {
    freq[(int) text[i]].count += 1;
  }

  freq = get_eff_frequency(freq);

  return freq;
}

{
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
  get_huffman_tree("saaaaaaaaaasdasdssss");
}
