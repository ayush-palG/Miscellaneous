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

char* append_char_to_str(char* str, char ch)
{
  int str_length = get_text_length(str);

  char* str_result = (char*) malloc((str_length + 1) * sizeof(char));

  int index = 0;
  while (str[index] != 0) str_result[index++] = str[index];
  str_result[index++] = ch;
  str_result[index] = 0;

  free(str);
  return str_result;
}

int is_char_in_string(const char* str, const char ch)
{
  for (int i = 0; str[i] != 0; ++i) {
    if (str[i] == ch) {
      return 1;
    }
  }

  return 0;
}

char* get_unique_chars(const char* text)
{
  char* str = (char*) malloc(sizeof(char));
  int text_length = get_text_length(text);

  for (int i = 0; i < text_length; ++i) {
    if (!is_char_in_string(str, text[i])) {
      str = append_char_to_str(str, text[i]);
    }
  }

  printf("%s", str);
  return str;
}

int chars_in_str(const char* text, const char ch)
{
  int text_length = get_text_length(text);

  int counter = 0;
  for (int i = 0; i < text_length; ++i) {
    if (text[i] == ch) counter++;
  }

  return counter;
}

