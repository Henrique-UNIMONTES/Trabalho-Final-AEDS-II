#include "Menu.h"

int mainMenu(int menuOk) {
  int option;

  if (menuOk) {
    if (titles_size == 0) loadTitleSize();
    
    printf("========== System main menu ==========\n");
    int invalid;
    
    do {
      invalid = FALSE;
      printf("Please select an option:\n");
      printf("[1] - Initiate QuickSort test\n");
      printf("[2] - Initiate ABB test\n");
      printf("[3] - Exit\n");
  
      scanf("%d", &option);
      clearBuffer();
  
      if (option < 1 || option > 3) {
        printf("\nInvalid option\n\n");
        invalid = TRUE;
      }
    } while (invalid);

    return option;
  }

  else {
    char ans;
    printf("The system could not connect to the database.\n");
    printf("Do you like to reinitiate the database? [Y/n]\n");
    scanf("%c", &ans);
    clearBuffer();
    
    if (ans == 'Y' || ans == 'y') {
      printf("The system will reinitiate the database.\n");
      
      transferToBinary();
      int fileOk = verifyBinaryFile();

      if (fileOk) {
        printf("Database restored successfully.\n\n");
        return mainMenu(TRUE);
      }

      else {
        printf("The system failed trying to reinitiate the database.\n");
        exit(1);
      }
    }

    else {
      printf("Program terminated");
      exit(0);
    }
  }
}

void clearBuffer() {
  while (getchar() != '\n');
}

void printLine() {
  printf("===============================================\n\n");
}