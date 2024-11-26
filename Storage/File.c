#include "File.h"

int verifyBinaryFile() {
  FILE *file = fopen(databasePath, "rb");
  int status;

  if (file == NULL) status = FALSE;
  else {
    status = TRUE;
    fclose(file);
  }

  return status;
}

void transferToBinary() {
  FILE *file = fopen(sourcePath, "r");
  FILE *output = fopen(databasePath, "wb");

  char ch;
  while ((ch = fgetc(file)) != '\n' && !feof(file));

  Title t;
  createTitle(&t);

  while (!feof(file)) {
    clearModel(&t);
    createTitle(&t);

    readField(t.id, file);
    readField(t.type, file);
    readField(t.title, file);
    readField(t.director, file);
    readField(t.cast, file);
    readField(t.country, file);
    readField(t.data_added, file);

    String *aux = createString();
    readField(aux, file);

    int length = stringLength(aux);

    char tmp[length + 1];
    stringToCharArray(aux, tmp);
    t.release_year = atoi(tmp);
    readField(t.rating, file);
    readField(t.duration, file);
    readField(t.listed_in, file);
    readField(t.description, file);

    titles_size++;
    serializeModel(output, &t);
  }

  fwrite(&titles_size, sizeof(int), 1, output);

  fclose(file);
  fclose(output);
}

void readField(String *str, FILE *file) {
  char c = fgetc(file);
  int hasMoreThanOne = FALSE;
  int quotations = 0;

  if (c == '\"') {
    hasMoreThanOne = TRUE;
    quotations++;
    c = fgetc(file);
  }

  while (c != EOF) {
    if (!hasMoreThanOne) {
      if (c == ',' || c == '\n') break;
    }

    if (c == '\"' && hasMoreThanOne) {
      c = fgetc(file);
      quotations++;

      if (c == ',' || c == '\n') {
        if (quotations % 2 == 0) {
          hasMoreThanOne = FALSE;
        }

        else {
          pushString(str, '\"');
        }
      }

      else {
        pushString(str, '\"');
      }

      continue;
    }

    pushString(str, c);
    c = fgetc(file);
  }
}

void loadTitleSize() {
  FILE *file = fopen(databasePath, "rb");
  fseek(file, -sizeof(int), SEEK_END);
  fread(&titles_size, sizeof(int), 1, file);
  fclose(file);
}

void serializeModel(FILE *file, Title *t) {
  fwrite(t, sizeof(Title), 1, file);

  int length;

  length = stringLength(t->id);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->type);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->title);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->director);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->cast);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->country);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->data_added);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->rating);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->duration);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->listed_in);
  fwrite(&length, sizeof(int), 1, file);

  length = stringLength(t->description);
  fwrite(&length, sizeof(int), 1, file);

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->id) + 1));
    stringToCharArray(t->id, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->id), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->type) + 1));
    stringToCharArray(t->type, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->type), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->title) + 1));
    stringToCharArray(t->title, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->title), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->director) + 1));
    stringToCharArray(t->director, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->director), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->cast) + 1));
    stringToCharArray(t->cast, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->cast), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->country) + 1));
    stringToCharArray(t->country, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->country), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->data_added) + 1));
    stringToCharArray(t->data_added, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->data_added), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->rating) + 1));
    stringToCharArray(t->rating, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->rating), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->duration) + 1));
    stringToCharArray(t->duration, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->duration), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->listed_in) + 1));
    stringToCharArray(t->listed_in, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->listed_in), 1, file);
    free(tmp);
  }

  {
    char *tmp = (char *) malloc(sizeof(char) * (stringLength(t->description) + 1));
    stringToCharArray(t->description, tmp);
    fwrite(tmp, sizeof(char) * stringLength(t->description), 1, file);
    free(tmp);
  }
}

void deserializeModel(Title *t, int pos) {
  FILE *file = fopen(databasePath, "rb");

  fseek(file, 0, SEEK_SET);

  for (int i = 0; i < pos; i++) {
    fseek(file, sizeof(Title), SEEK_CUR);
    int size[11];

    fread(size, sizeof(int) * 11, 1, file);

    int sum = 0;

    for (int i = 0; i < 11; i++) sum += size[i];
    fseek(file, sizeof(char) * sum, SEEK_CUR);
  }

  fread(t, sizeof(Title), 1, file);

  int lengths[11];
  fread(lengths, sizeof(int), 11, file);

  t->id = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[0] + 1));
    fread(tmp, sizeof(char) * lengths[0], 1, file);
    tmp[lengths[0]] = '\0';
    charArrayToString(t->id, tmp);
    free(tmp);
  }

  t->type = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[1] + 1));
    fread(tmp, sizeof(char) * lengths[1], 1, file);
    tmp[lengths[1]] = '\0';
    charArrayToString(t->type, tmp);
    free(tmp);
  }

  t->title = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[2] + 1));
    fread(tmp, sizeof(char) * lengths[2], 1, file);
    tmp[lengths[2]] = '\0';
    charArrayToString(t->title, tmp);
    free(tmp);
  }

  t->director = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[3] + 1));
    fread(tmp, sizeof(char) * lengths[3], 1, file);
    tmp[lengths[3]] = '\0';
    charArrayToString(t->director, tmp);
    free(tmp);
  }

  t->cast = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[4] + 1));
    fread(tmp, sizeof(char) * lengths[4], 1, file);
    tmp[lengths[4]] = '\0';
    charArrayToString(t->cast, tmp);
    free(tmp);
  }

  t->country = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[5] + 1));
    fread(tmp, sizeof(char) * lengths[5], 1, file);
    tmp[lengths[5]] = '\0';
    charArrayToString(t->country, tmp);
    free(tmp);
  }

  t->data_added = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[6] + 1));
    fread(tmp, sizeof(char) * lengths[6], 1, file);
    tmp[lengths[6]] = '\0';
    charArrayToString(t->data_added, tmp);
    free(tmp);
  }

  t->rating = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[7] + 1));
    fread(tmp, sizeof(char) * lengths[7], 1, file);
    tmp[lengths[7]] = '\0';
    charArrayToString(t->rating, tmp);
    free(tmp);
  }

  t->duration = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[8] + 1));
    fread(tmp, sizeof(char) * lengths[8], 1, file);
    tmp[lengths[8]] = '\0';
    charArrayToString(t->duration, tmp);
    free(tmp);
  }

  t->listed_in = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[9] + 1));
    fread(tmp, sizeof(char) * lengths[9], 1, file);
    tmp[lengths[9]] = '\0';
    charArrayToString(t->listed_in, tmp);
    free(tmp);
  }

  t->description = createString();

  {
    char *tmp = (char *) malloc(sizeof(char) * (lengths[10] + 1));
    fread(tmp, sizeof(char) * lengths[10], 1, file);
    tmp[lengths[10]] = '\0';
    charArrayToString(t->description, tmp);
    free(tmp);
  }

  fclose(file);
}
