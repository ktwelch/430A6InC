#include <stdlib.h>
#include <string.h>

typedef struct numV {
  int type; // 0
  int num;
} numV;

void* alloc_numV(int num) {
  numV *result = malloc(sizeof(numV));
  result->type = 0;
  result->num = num;
  return result;
}


typedef struct boolV {
  int type; // 1
  int bool;
} boolV;

void* alloc_boolV(int bool) {
  boolV *result = malloc(sizeof(boolV));
  result->type = 1;
  result->bool = bool;
  return result;
}


typedef struct cloV {
  int type; // 2
  char params[64][64];
  void* body; // ExprC
  // environment
} cloV;

void* alloc_cloV(char** params, void* body) {
  cloV *result = malloc(sizeof(cloV));
  result->type = 2;
  memcpy(result->params, params, sizeof(result->params));
  result->body = body;
  return result;
}

