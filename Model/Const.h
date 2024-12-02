#ifndef IMPORTS_H
  #define IMPORTS_H
  #include "../imports.h"
#endif

#define TRUE 1
#define FALSE 0

#define databasePath "data.bin"
#define sourcePath "netflix_titles.csv"

#ifndef GLOBALS
  #define GLOBALS

  extern int titles_size;
  extern int tests_loaded;
  extern int *indexes;
  extern ResumedTitle *titles_data;
#endif
