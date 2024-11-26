#ifndef IMPORTS_H
  #define IMPORTS_H
  #include "../imports.h"
#endif

/**
 * @description Prints the current time
 * @return time_t The current timein seconds
**/
time_t showTime();

/**
 * @description Shuffle the titles order
 * @param int * Array of indexes
 * @param int Size of the array
**/
void getShuffledIndexes(int *indexes, int size);

/**
 * Setup the titles order so it loses any ordenation
**/
void configIndexes();

/**
 * @description Load the titles from the binary file and store its resumed versions on the titles_data global
**/
void loadData();

/**
 * @description Execute the tests
 * @param int Test to be executed
**/
void initializeTests(int test);