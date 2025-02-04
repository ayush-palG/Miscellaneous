#include <stdio.h>
#include <stdlib.h>

#define FREQUENCY_IMPLEMENTATION
#include "frequency.h"

#define NODE_IMPLEMENTATION
#include "node.h"

Node* get_huffman_tree(const char* text)
{
  if (get_text_length(text) == 0) {
    printf("Problem in getting huffman tree!");
    exit(0);
  }
  
  Frequency* freq = get_frequency(text);
  print_frequency(freq);

  Node* nodes = init_nodes(freq);
  int nodes_size = get_nodes_length(nodes);

  printf("Node size Before: %d\n", nodes_size);

  while (get_nodes_length(nodes) > 1) {
    Node* left = get_last_node(nodes);
    Node* right = get_last_node(nodes);
    
    Frequency new_freq = (Frequency) {
      .ch = 0,
      .count = left->freq.count + right->freq.count,
    };
    Node new_node = (Node) {
      .freq = new_freq,
      .left = left,
      .right = right,
    };
    
    add_new_node(nodes, new_node);
    ssort_nodes(nodes);
  }

  printf("Node Size After: %d\n", get_nodes_length(nodes));

  return nodes;
}

int main(void)
{
  get_huffman_tree("sasdasdssss");
}
