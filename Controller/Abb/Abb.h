#ifndef IMPORTS_H
#define IMPORTS_H
#include "../../imports.h"
#endif

#ifndef STRUCT_ABB
#define STRUCT_ABB

/**
 * @description Binary Search Tree node representation
 **/
typedef struct abb {
  int index;
  char id[10];
  struct abb *left;
  struct abb *right;
} Abb;
#endif

/**
 * @description Insert a node into the ABB
 * @param Abb * The root of the ABB
 * @param char * The ID of the node to be inserted
 * @param int The index of the node to be inserted
 **/
Abb *insertNode(Abb *root, char *id, int index);

/**
 * @description Search a node in the ABB
 * @param Abb * The root of the ABB
 * @param char * The ID of the node to be searched
 **/
Abb *searchNode(Abb *root, char *id);

/**
 * @description Clears the memory of the ABB
 * @param Abb * The root of the ABB
 **/
void freeAbb(Abb *root);

/**
 * @description Entrypoint for the test
 **/
void initializeAbb();