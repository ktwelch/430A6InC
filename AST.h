#include <stdlib.h>
#include <string.h>


typedef struct numC {
  int type;
  float num;
} numC;

void *alloc_numC(float num) {
  numC *result = malloc(sizeof(numC));
  result->type = 0;
  result->num = num;
  return result;
}


typedef struct boolC {
  int type;
  int bool;
} boolC;

void *alloc_boolC(int bool) {
  boolC *result = malloc(sizeof(boolC));
  result->type = 1;
  result->bool = bool;
  return result;
}


typedef struct idC {
  int type;
  char id[64];
} idC;

void *alloc_idC(char *id) {
  idC *result = malloc(sizeof(idC));
  result->type = 2;
  strcpy(result->id, id);
  return result;
}


typedef struct ifC {
  int type;
  void *cond;
  void *left;
  void *right;
} ifC;

void *alloc_ifC(void* cond, void* left, void* right) {
  ifC *result = malloc(sizeof(ifC));
  result->type = 3;
  result->cond = cond;
  result->left = left;
  result->right = right;
  return result;
}


typedef struct lamC {
  int type;  // 4
  char params[64][64];
  void* body;
} lamC;

void* alloc_lamC(char** params, void* body) {
  lamC* result = malloc(sizeof(lamC));
  result->type = 4;
  memcpy(result->params, params, sizeof(result->params));
  result->body = body;
  return result;
}


typedef struct binopC {
  int type;  // 5
  char op[4];
  void* left;
  void* right;
} binopC;

void* alloc_binopC(char *op, void *left, void *right) {
  binopC* result = malloc(sizeof(binopC));
  result->type = 5;
  strcpy(result->op, op);
  result->left = left;
  result->right = right;
  return result;
}


typedef struct appC {
  int type;  // 6
  void* fun;
  void* args[64];
} appC;

void* alloc_appC(void *fun) {  // add your args by hand, sorry...
  appC* result = malloc(sizeof(appC));
  result->type = 6;
  int i;

  for (i = 0; i < 64; i++) {
    result->args[i] = NULL;
  }
  return result;
}

