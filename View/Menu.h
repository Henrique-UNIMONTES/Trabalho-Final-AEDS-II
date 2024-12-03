#ifndef IMPORTS_H
  #define IMPORTS_H
  #include "../imports.h"
#endif

/**
 * @description Prints the main menu
 * @param int If the database exists or need to be created first
 * @return int The option selected
**/
int mainMenu(int menuOk);

/**
 * @description Clears the keyboard buffer
**/
void clearBuffer();

/**
 * @description Prints a line into the console
 */
void printLine();