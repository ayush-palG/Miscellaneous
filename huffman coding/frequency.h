#ifndef FREQUENCY
#define FREQUENCY

#define CHAR_SIZE 256

typedef struct {
  char ch;
  int count;
} Frequency;

int get_text_length(const char* text);

int get_frequency_length(const Frequency* freq);
void print_frequency(const Frequency* freq);

void ssort_frequency(Frequency* freq);

Frequency* init_frequency(void);
Frequency* get_eff_frequency(Frequency* frequency);
Frequency* get_frequency(const char* text);

#endif // FREQUENCY

#ifdef FREQUENCY_IMPLEMENTATION

int get_text_length(const char* text)
{
  int counter = 0;
  while (text[counter] != 0) counter++;
  return counter;
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
    int max_index = i;
    
    for (size_t j = i+1; j < freq_size; ++j) {
      if (freq[j].count > freq[max_index].count) max_index = j;
    }
    
    Frequency temp_freq = freq[i];
    freq[i] = freq[max_index];
    freq[max_index] = temp_freq;
  }
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

Frequency* get_eff_frequency(Frequency* frequency)
{
  int freq_size = get_frequency_length(frequency);
  Frequency* freq = (Frequency*) malloc(freq_size * sizeof(Frequency));

  for (size_t i = 0, j = 0; i < CHAR_SIZE && j < freq_size; ++i) {
    if (frequency[i].count > 0) freq[j++] = frequency[i];
  }

  free(frequency);

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

#endif // FREQUENCY_IMPLEMENTATION
