#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char **combs;
  size_t combs_qt;
} Combs;

size_t nCk(size_t n, size_t k)
{
  assert(n >= k);
  size_t numerator = 1;
  for (size_t i = k+1; i <= n; ++i) numerator *= i;

  size_t denominator = 1;
  for (size_t i = 1; i <= (n-k); ++i) denominator *= i;

  return numerator / denominator;
}

void combs_malloc(Combs *combs, size_t size)
{
  combs->combs = (char **) malloc(sizeof(char *) * (size+1));
  for (size_t i = 0; i <= size; ++i) combs->combs[i] = NULL;
}

void combinations(Combs *combs, char *cstr, size_t r)
{
  size_t len = strlen(cstr);
  if (r > len) return;
  size_t indices[r];
  for (size_t i = 0; i < r; ++i) indices[i] = i;

  char *ch = (char *) malloc(sizeof(char) * (r+1));
  for (size_t i = 0; i < r; ++i) ch[i] = cstr[indices[i]];
  ch[r] = 0;
  combs->combs[combs->combs_qt++] = ch;

  while (1) {
    size_t i = 0;
    size_t is_if_block_in_for_loop_visited = 0;
    for (i = r-1; i < r; --i) {
      if (indices[i] != i + len - r) {
	is_if_block_in_for_loop_visited = 1;
	break;
      }
    }
    if (!is_if_block_in_for_loop_visited) break;

    indices[i] += 1;
    for (size_t j = i+1; j < r; ++j) indices[j] = indices[j-1] + 1;
    
    ch = (char *) malloc(sizeof(char) * (r+1));
    for (size_t i = 0; i < r; ++i) ch[i] = cstr[indices[i]];
    ch[r] = 0;
    combs->combs[combs->combs_qt++] = ch;
  }
}

void print_combinations(Combs *combs)
{
  for (size_t i = 0; i < combs->combs_qt; ++i) {
    printf("%s\n", combs->combs[i]);
  }
}

Combs combs = {0};

int main(void)
{
  char *cstr = "ABCDEF";
  size_t choose_num = 3;
  
  size_t size = nCk(strlen(cstr), choose_num);
  combs_malloc(&combs, size);
  combinations(&combs, cstr, choose_num);
  print_combinations(&combs);

  return 0;
}
