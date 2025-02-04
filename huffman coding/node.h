#ifndef NODE
#define NODE

typedef struct node {
  Frequency freq;
  struct node* left;
  struct node* right;
} Node;

int is_bottom_node(Node node);
int is_node_empty(Node node);
int get_nodes_length(Node* nodes);

void ssort_nodes(Node* nodes);

Node* create_node(const Frequency freq, Node* left, Node* right);
Node* init_nodes(const Frequency* freq);
Node* get_last_node(Node* nodes);
void add_new_node(Node* nodes, Node node);

#endif // NODE

#ifdef NODE_IMPLEMENTATION

int is_bottom_node(Node node)
{
  return (node.left == NULL && node.right == NULL);
}

int is_node_empty(Node node)
{
  return (is_bottom_node(node) &&
	  node.freq.ch == 0 &&
	  node.freq.count == 0);
}

int get_nodes_length(Node* nodes)
{
  size_t i = 0;
  while (!is_node_empty(nodes[i++]));
  return --i;
}

void ssort_nodes(Node* nodes)
{
  int node_size = get_nodes_length(nodes);
  
  for (size_t i = 0; i < node_size; ++i) {
    int max_index = i;
    
    for (size_t j = i+1; j < node_size; ++j) {
      if (nodes[j].freq.count > nodes[max_index].freq.count) max_index = j;
    }
    
    Node temp_node = nodes[i];
    nodes[i] = nodes[max_index];
    nodes[max_index] = temp_node;
  }
}

Node* create_node(const Frequency freq, Node* left, Node* right)
{
  Node* node = (Node*) malloc(sizeof(Node));
  *node = (Node) {
    .freq = freq,
    .left = left,
    .right = right,
  };

  return node;
}

Node* init_nodes(const Frequency* freq)
{
  int freq_size = get_frequency_length(freq);
  Node* node = (Node*) malloc((freq_size+1) * sizeof(Node));

  for (size_t i = 0; i < freq_size; ++i) {
    node[i] = (Node) {
      .freq = freq[i],
      .left = NULL,
      .right = NULL,
    };
  }

  node[freq_size] = (Node) {0};
  
  return node;
}

Node* get_last_node(Node* nodes)
{
  int node_size = get_nodes_length(nodes);

  Node node = nodes[node_size-1];
  nodes[node_size-1] = (Node) {0};
  
  Node* last_node = create_node(node.freq,
				node.left,
				node.right);
  return last_node;
}

void add_new_node(Node* nodes, Node new_node)
{
  int node_size = get_nodes_length(nodes);
  nodes[node_size] = new_node;
}

#endif // NODE_IMPLEMENTATION
