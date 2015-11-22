#include <stdlib.h>


typedef struct numC {
  int type;
  int number;
} numC;

void *alloc_numC() {
  numC *result = malloc(sizeof(numC));
  result->type = 0;
  return result;
}


typedef struct boolC {
  int type;
  int bool;
} boolC;

void *alloc_boolC() {
  boolC *result = malloc(sizeof(boolC));
  result->type = 1;
  return result;
}


typedef struct idC {
  int type;
  char id[64];
} idC;

void *alloc_idC() {
  idC *result = malloc(sizeof(idC));
  result->type = 2;
  return result;
}


typedef struct ifC {
  int type;
  void *cond;
  void *left;
  void *right;
} ifC;

void *alloc_ifC() {
  ifC *result = malloc(sizeof(ifC));
  result->type = 3;
  return result;
}


typedef struct lamC {
  int type;  // 4
  char params[64][64];
  void* body;
} lamC;

void* alloc_lamC() {
  lamC* result = malloc(sizeof(lamC));
  result->type = 4;
  return result;
}


typedef struct binopC {
  int type;  // 5
  char op[4];
  void* left;
  void* right;
} binopC;

void* alloc_binopC() {
  binopC* result = malloc(sizeof(binopC));
  result->type = 5;
  return result;
}


typedef struct appC {
  int type;  // 6
  void* fun;
  void* args[64];
} appC;

void* alloc_appC() {
  appC* result = malloc(sizeof(appC));
  result->type = 6;
  return result;
}

