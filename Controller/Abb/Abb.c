#include "Abb.h"

// Stores the memory accesses count of the ABB algorithm
int access = 0;

// Stores the search stack path of the ABB algorithm
String *searchStackTree;

// Stores the current index method of the ABB tree
int abbMode;

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
  printf("[1] - By ID\n");
  printf("[2] - By date\n");
  printf("[3] - None (Back to main menu)\n");
  scanf("%d", &op);

  abbMode = op;

  if (op == 3) {
    return;
  }

  else if (op > 1) {
    printf("Not implemented yet");
    return;
  }

  for (int i = 0; i < titles_size; i++) {
    root = insertNode(root, titles_data[i].id, titles_data[i].index);
  }

  printf("Nodes inserted on the ABB\n\n");

  while (TRUE) {
    searchStackTree = createString();
    access = 0;

    if (abbMode == 1) {
      int id;

      while (TRUE) {
        printf("Informe o ID para realizar a busca: [1 - 8807]\ns");
        scanf("%d", &id);
        clearBuffer();

        if (id < 1 || id > 8807) {
          printf("ID inválido\n\n");
        }

        else {
          break;
        }
      }

      char ans[6];
      ans[0] = 's';

      if (id < 10) {
        ans[1] = '0' + id;
        ans[2] = '\0';
      }

      else if (id < 100) {
        ans[1] = '0' + id / 10;
        ans[2] = '0' + id % 10;
        ans[3] = '\0';
      }

      else if (id < 1000) {
        ans[1] = '0' + id / 100;
        ans[2] = '0' + (id % 100) / 10;
        ans[3] = '0' + (id % 100) % 10;
        ans[4] = '\0';
      }

      else {
        ans[1] = '0' + id / 1000;
        ans[2] = '0' + (id % 1000) / 100;
        ans[3] = '0' + ((id % 1000) % 100) / 10;
        ans[4] = '0' + ((id % 1000) % 100) % 10;
        ans[5] = '\0';
      }

      printf("\nStarting search for the node with ID: %s\n\n", ans);
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
    }

    else if (abbMode == 2) {

    }

    clearString(searchStackTree);
  }

  freeAbb(root);
}