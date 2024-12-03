#include "Model.h"

String *createString() {
  String *s = (String *) malloc(sizeof(String));
  s->begin = s->end = NULL;
  s->length = 0;
  return s;
}

void printString(String *s) {
  for (Character *c = s->begin; c != NULL; c = c->next) {
    printf("%c", c->c);
  }
}

void pushString(String *s, char c) {
  Character *new = (Character *) malloc(sizeof(Character));
  Character *ch;

  new->c = c;
  new->next = NULL;

  if (s->begin == NULL) {
    s->begin = s->end = new;
  }

  else {
    s->end->next = new;
    s->end = new;
  }

  s->length++;
}

void stringToCharArray(String *s, char *c) {
  int i = 0;

  for (Character *ch = s->begin; ch != NULL; ch = ch->next, i++) {
    c[i] = ch->c;
  }

  c[i] = '\0';
}

void charArrayToString(String *s, char *c) {
  for (int i = 0; i < strlen(c); i++) {
    pushString(s, c[i]);
  }
}

int stringLength(String *s) {
  return s->length;
}

void clearString(String *s) {
  Character *tmp, *ch = s->begin;

  while (ch != NULL) {
    tmp = ch->next;
    free(ch);
    ch = tmp;
  }

  free(s);
}

void createTitle(Title *t) {
  t->id = createString();
  t->type = createString();
  t->title = createString();
  t->director = createString();
  t->cast = createString();
  t->country = createString();
  t->data_added = createString();
  t->rating = createString();
  t->duration = createString();
  t->listed_in = createString();
  t->description = createString();
}

void clearModel(Title *t) {
  clearString(t->id);
  clearString(t->type);
  clearString(t->title);
  clearString(t->director);
  clearString(t->cast);
  clearString(t->country);
  clearString(t->data_added);
  clearString(t->rating);
  clearString(t->duration);
  clearString(t->listed_in);
  clearString(t->description);
}

void printModel(Title t) {
  printf("ID: ");
  printString(t.id);
  printf("\nType: ");
  printString(t.type);
  printf("\nTitle: ");
  printString(t.title);
  printf("\nDirectors: ");
  printString(t.director);
  printf("\nCast: ");
  printString(t.cast);
  printf("\nCountry: ");
  printString(t.country);
  printf("\nDate Added: ");
  printString(t.data_added);
  printf("\nYear: %d", t.release_year);
  printf("\nRating: ");
  printString(t.rating);
  printf("\nDuration: ");
  printString(t.duration);
  printf("\nListed in: ");
  printString(t.listed_in);
  printf("\nDescription: ");
  printString(t.description);
}
