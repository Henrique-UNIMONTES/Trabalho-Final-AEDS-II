#include "Abb.h"

// Stores the memory accesses count of the ABB algorithm
int access = 0;

// Stores the search stack path of the ABB algorithm
String *searchStackTree;

// Stores the current index method of the ABB tree
int abbMode;

Abb *insertNode(Abb *root, char *id, int index) {
  access++;
  if (root == NULL) {
    Abb *new = (Abb *) malloc(sizeof(Abb));
    new->right = new->left = NULL;
    new->index = index;
    new->id = (char *) malloc(sizeof(char) * (strlen(id) + 1));
    strcpy(new->id, id);
    return new;
  }

  if (abbMode == 1) {
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
  }

  else if (abbMode == 2) {
    int cmp = strcmp(root->id, id);

    if (cmp == 0) {
      return root;
    }

    else if (cmp < 0) {
      root->right = insertNode(root->right, id, index);
    }

    else {
      root->left = insertNode(root->left, id, index);
    }
  }

  else {
    printf("Abb mode not implemented");
    exit(1);
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

  if (abbMode == 1) {
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

  else if (abbMode == 2) {
    int len1 = strlen(root->id), len2 = strlen(id);
    int cmp = strncmp(root->id, id, len1 > len2 ? len2 : len1);

    if (cmp == 0 && len1 < len2) cmp = -1;

    if (cmp == 0) {
      return root;
    }

    else if (cmp < 0) {
      return searchNode(root->right, id);
    }

    else {
      return searchNode(root->left, id);
    }
  }

  else {
    printf("Search type not implemented");
    exit(1);
  }
}

void freeAbb(Abb *root) {
  if (root == NULL) return;

  freeAbb(root->left);
  freeAbb(root->right);
  free(root);
}

int initializeAbb() {
  Abb *root = NULL;
  int op;
  
  do {
    printf("What kind of search you would like do perform?\n");
    printf("[1] - By ID\n");
    printf("[2] - By Title\n");
    printf("[3] - Perform the default search\n");
    printf("[4] - None (Back to main menu)\n");
    scanf("%d", &op);
    clearBuffer();

    if (op < 1 || op > 4) {
      printf("\nInvalid option\n\n");
    }

    else break;
  } while (TRUE);

  abbMode = op;

  if (op == 3) abbMode = 1;

  if (op == 4) {
    printf("\n");
    return 0;
  }

  if (abbMode == 1) {
    access = 0;
    for (int i = 0; i < titles_size; i++) {
      root = insertNode(root, titles_data[i].id, titles_data[i].index);
    }
    printf("ACCESS: %d\n", access);
  }

  else {
    for (int i = 0; i < titles_size; i++) {
      for (int j = 0; j < strlen(titles_data[i].title); j++) {
        titles_data[i].title[j] = tolower(titles_data[i].title[j]);
      }

      root = insertNode(root, titles_data[i].title, titles_data[i].index);
    }
  }

  printf("Nodes inserted on the ABB\n\n");

  if (op == 3) {
    int ids[4] = { 1, titles_size - 1, (titles_size - 1) / 2, titles_size - 2 };

    for (int i = 0; i < 4; i++) {
      searchStackTree = createString();

      char id[6];
      sprintf(id, "s%d", ids[i]);

      printf("\nStarting search for the node with ID: %s\n\n", id);
      printf("Initial time : ");
      time_t initialTime = showTime();

      Abb *node = searchNode(root, id);

      printf("Final time   : ");
      time_t finalTime = showTime();

      printf("Total time   : %ld second(s)\n\n", finalTime - initialTime);

      printf("Total memory accesses: %d\n\n", access);

      printf("Search stack path:\n");
      printf("[BEGIN] -> ");
      printString(searchStackTree);
      printf("[END]\n\n");

      clearString(searchStackTree);

      printLine();
    }

    return FALSE;
  }

  char op2;
  do {
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

      if (node != NULL) {
        Title t;
        deserializeModel(&t, node->index);
        printModel(t);
        printf("\n\n");
      }

      else printf("Node not found\n\n");

      printf("Search stack path:\n");
      printf("[BEGIN] -> ");
      printString(searchStackTree);
      printf("[END]\n\n");

      printLine();

      printf("Do you wanna make another ID search? [Y/n]\n");
      scanf("%c", &op2);
      clearBuffer();
    }

    else if (abbMode == 2) {
      char title[51];
      printf("This search looks finds the first title that matches with the search string.\n");
      printf("Enter the title you wanna to search for: [MAX LENGTH = 50]\n");
      scanf("%50[^\n]", title);
      clearBuffer();
      printf("\n");

      printf("\nStarting search for the node with title: %s\n\n", title);
      printf("Initial time : ");
      time_t initialTime = showTime();

      Abb *node = searchNode(root, title);

      printf("Final time   : ");
      time_t finalTime = showTime();

      printf("Total time   : %ld second(s)\n\n", finalTime - initialTime);

      printf("Total memory accesses: %d\n\n", access);

      if (node != NULL) {
        Title t;
        deserializeModel(&t, node->index);
        printModel(t);
        printf("\n\n");
      }

      else printf("Node not found\n\n");

      printf("Search stack path:\n");
      printf("[BEGIN] -> ");
      printString(searchStackTree);
      printf("[END]\n\n");

      printLine();

      printf("Do you wanna make another Title search? [Y/n]\n");
      scanf("%c", &op2);
      clearBuffer();
    }

    clearString(searchStackTree);
  } while (op2 == 'Y' || op2 == 'y');

  freeAbb(root);

  printf("\nDo you wanna make another type of search? [Y/n]\n");
  scanf("%c", &op2);
  printf("\n");

  if (op2 == 'Y' || op2 == 'y') {
    return TRUE;
  }

  return FALSE;
}