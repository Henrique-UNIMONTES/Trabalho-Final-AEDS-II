#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Qsort(int v[], int ini, int fim){
  int i, j, pivo, aux;
  i=ini;
  j=fim;
  pivo = ini;
  if(ini>=fim)return;
  while(i<j){
    while(v[i]<v[pivo]) i++;
    while(v[j]>v[pivo]) j--;
    if(i<=j){
      aux=v[i];
      v[i]=v[j];
      v[j]=aux;
      if(pivo==i) pivo = j;
      else if (pivo==j) pivo = i;
    }
  }
  Qsort(v, ini, pivo-1);
  Qsort(v, pivo+1, fim);
}
