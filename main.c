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
    fileOk = TRUE;
    
    switch (option) {
      case 1: case 2:
        initializeTests(option);
        break;
      default:
        return 0;
    }
  } while (TRUE);

  for (int i = 0; i < titles_size; i++) {
    free(titles_data[i].id);
    free(titles_data[i].title);
  }

  free(indexes);
  free(titles_data);
}