#include <stdio.h>
#include <stdlib.h>

#define K 26
#define MAX_TRIE 100

typedef struct Vertex {
  int next[K];
  unsigned int output;
} Vertex;

typedef Vertex *Trie[MAX_TRIE];

Trie trie;

int NODES = 1;

Vertex *create_vertex() {
  Vertex *vertex = (struct Vertex *)malloc(sizeof(struct Vertex));
  if (!vertex) {
    fprintf(stderr, "Memory allocation not work");
  }
  vertex->output = 0;
  for (int i = 0; i < K; i++) {
    vertex->next[i] = -1;
  }
  return vertex;
}

void init_trie(Trie *trie) {
  for (int i = 0; i < MAX_TRIE; i++) {
    (*trie)[i] = create_vertex();
  }
}

int get_char_number(char ch) { return ch - 'a'; }

void insert_trie(const char *text) {
  int current = 0;

  for (int i = 0; text[i] != '\0'; i++) {
    int ch = get_char_number(text[i]);
    if (trie[current]->next[ch] == -1) {
      trie[current]->next[ch] = NODES++;
    }
    current = trie[current]->next[ch];
  }

  trie[current]->output = 1;
}

void print_trie() {
  for (int i = 0; i < NODES; i++) {
    printf("Node %d, Output: %d, Next: [", i, trie[i]->output);
    for (int j = 0; j < K; j++) {
      if (trie[i]->next[j] != -1) {
        printf(" %d (%d %c) ", trie[i]->next[j], j, (char)j + 'a');
      }
    }
    printf(" ]\n");
  }
}

int search(char *text) {
  printf("Search Word: %s\n", text);

  int current = 0;

  for (int i = 0; text[i] != '\0'; i++) {
    int ch = get_char_number(text[i]);
    if (trie[current]->next[ch] == -1) {
      return 0;
    }

    current = trie[current]->next[ch];
  }

  if (trie[current]->output == 1) {
    return 1;
  }

  return 0;
}

int main() {
  char text[] = "hello";
  char text2[] = "holly";
  char text3[] = "help";
  char text4[] = "holl";

  init_trie(&trie);

  insert_trie(text);
  insert_trie(text2);
  insert_trie(text3);

  print_trie();

  printf("String %s %s na trie\n", text4,
         search(text4) ? "existe" : "não existe");

  return 0;
}
