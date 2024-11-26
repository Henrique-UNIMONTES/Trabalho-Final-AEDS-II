#ifndef IMPORTS_H
  #define IMPORTS_H
  #include "imports.h"
#endif

int main(void) {
  srand(time(NULL));

  int fileOk = verifyBinaryFile();
  int option;
  
  do {
    option = mainMenu(fileOk);
  
    switch (option) {
      case 1: case 2:
        initializeTests(option);
        break;
      default:
        return 0;
    }
  } while (TRUE);
}