#ifndef IMPORTS_H
#define IMPORTS_H
#include "../imports.h"
#endif

/**
 * @description Verify if the binary file exists
 * @return int TRUE if the file exists, FALSE otherwise
 **/
int verifyBinaryFile();

/**
 * @description Transfer the data from the csv file to a binary file
 **/
void transferToBinary();

/**
 * @description Load a csv field into the string object
 * @param String * String where the data will be put in
 * @param FILE * File where the data will be read from
 **/
void readField(String *str, FILE *f);

/**
 * @description Load a title from the binary file basead on its position
 * @param Title * Title where the data will be put in
 * @param int Position of the title in the binary file
 **/
void getTitle(Title *t, int position);

/**
 * @description Loads the number of titles stored on the binary file
 **/
void loadTitleSize();

/**
 * @description Save a title to the binary file
 * @param FILE * File where the data will be saved
 * @param Title * Title to be saved
 **/
void serializeModel(FILE *f, Title *t);

/**
 * @description Reads a title from the binary file
 * @param Title * Title where the data will be put in
 * @param int Position of the title in the binary file
 **/
void deserializeModel(Title *t, int pos);