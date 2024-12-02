#ifndef IMPORTS_H
  #define IMPORTS_H
  #include "../imports.h"
#endif

#ifndef STRING_STRUCT
  #define STRING_STRUCT
  /**
   * @description A custom object that uses the concepts of a liked list to make a dynamic string
  **/
  typedef struct character {
    char c;
    struct character *next;
  } Character;

  typedef struct {
    Character *begin, *end;
    int length;
  } String;
#endif

#ifndef TITLE_STRUCT
  #define TITLE_STRUCT
  /**
   * @description Object for representating the Title objects of the database
  **/
  typedef struct {
    String *id, *type, *title, *director, *cast, *country, *data_added, *rating, *duration, *listed_in, *description;

    int release_year;
  } Title;

  typedef struct {
    char *id, *date;
    int index;
  } ResumedTitle;
#endif

/**
 * @description Initializate a dynamic string object
 * @return String* A pointer to the object created
**/
String *createString();

/**
 * @description Print the content of a dynamic string object
 * @param String * String to be printed
**/
void printString(String *s);

/**
 * @description Push a new character into a String object
 * @param String* A pointer to the object to push the character
 * @param char The character to push
**/
void pushString(String *s, char c);

/**
 * @description Converts a dynamic string object to a char array
 * @param String* A pointer to the object to convert
 * @param char* A pointer to the char array where the result will be placed (Be sure to initialize a char array with size of 1 + the length of the String object)
**/
void stringToCharArray(String *s, char *c);

/**
 * @description Converts a char array to a dynamic string object
 * @param String* A pointer to the string that will receive the data
 * @param char* A pointer to the char array containing the string
**/
void charArrayToString(String *s, char *c);

/**
 * @description Returns the length of a dynamic string object
 * @param String* A pointer to the object to get the length
**/
int stringLength(String *s);

/**
 * @description Clears a dynamic string object freeing the memory allocated
 * @param String* The String to be cleared
**/
void clearString(String *s);

/**
 * @description Initialize a Title object
 * @param Title* A pointer to the object to initialize
**/
void createTitle(Title *t);

/**
 * @description Clear the components of a Title object
 * @param Title* The object to be cleared
**/
void clearModel(Title *t);

/**
 * @description Prints the data of a Title object into the console
 * @param Title* The Title object to be printed
**/
void printModel(Title t);