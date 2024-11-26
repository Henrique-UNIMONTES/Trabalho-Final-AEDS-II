#include "Abb.h"

// Stores the memory accesses count of the ABB algorithm
int access = 0;

// Stores the search stack path of the ABB algorithm
String *searchStackTree;

Abb *insertNode(Abb *root, char *id, int index) {
  if (root == NULL) {
    Abb *new = (Abb *) malloc(sizeof(Abb));
    new->right = new->left = NULL;
    new->index = index;
    strcpy(new->id, id);
    return new;
  }

  int rootID = 0;

  for (int i = 1; i < strlen(root->id); i++) {
    rootID += root->id[i] - '0';
    rootID *= 10;
  }

  int nodeID = 0;

  for (int i = 1; i < strlen(id); i++) {
    nodeID += id[i] - '0';
    nodeID *= 10;
  }

  if (rootID < nodeID) {
    root->right = insertNode(root->right, id, index);
  }

  else {
    root->left = insertNode(root->left, id, index);
  }

  return root;
}

Abb *searchNode(Abb *root, char *id) {
  access++;

  if (root == NULL) return NULL;

  pushString(searchStackTree, '[');

  for (int i = 0; i < strlen(root->id); i++) {
    pushString(searchStackTree, root->id[i]);
  }

  pushString(searchStackTree, ']');
  pushString(searchStackTree, ' ');
  pushString(searchStackTree, '-');
  pushString(searchStackTree, '>');
  pushString(searchStackTree, ' ');

  int rootID = 0;

  for (int i = 1; i < strlen(root->id); i++) {
    rootID += root->id[i] - '0';
    rootID *= 10;
  }

  int nodeID = 0;

  for (int i = 1; i < strlen(id); i++) {
    nodeID += id[i] - '0';
    nodeID *= 10;
  }

  if (nodeID == rootID) return root;

  if (rootID < nodeID) {
    return searchNode(root->right, id);
  }

  return searchNode(root->left, id);
}

void freeAbb(Abb *root) {
  if (root == NULL) return;

  freeAbb(root->left);
  freeAbb(root->right);
  free(root);
}

void initializeAbb() {
  Abb *root = NULL;
  int op;
  
  printf("What kind of search you would like do perform?\n");
  printf("[1] - By ID");
  printf("[2] - By date");
  printf("[3] - None (Back to main menu)");
  scanf("%d", &op);

  if (op == 1) {
    for (int i = 0; i < titles_size; i++) {
      root = insertNode(root, titles_data[i].id, titles_data[i].index);
    }
  }

  else {
    printf("Not implemented yet");
    return;
  }

  printf("Nodes inserted on the ABB\n\n");

  searchStackTree = createString();
  access = 0;

  char *ans = "s563";
  printf("Starting search for the node with ID: %s\n\n", ans);
  printf("Initial time : ");
  time_t initialTime = showTime();

  Abb *node = searchNode(root, ans);

  printf("Final time   : ");
  time_t finalTime = showTime();

  printf("Total time   : %ld second(s)\n\n", finalTime - initialTime);

  printf("Total memory accesses: %d\n\n", access);

  if (node != NULL) printf("Node found at index: [%d]\n\n", node->index);
  else printf("Node not found\n\n");

  printf("Search stack path:\n");
  printf("[BEGIN] -> ");
  printString(searchStackTree);
  printf("[END]\n\n");

  freeAbb(root);
}