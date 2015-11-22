#include "AST.h"
#include <stdio.h>
#include "values.h"

// left and right are Values, returns a Value
void* eval_binop(char* symbol, void* left_void, void* right_void) {
  int* left = (int*)left_void;
  int* right = (int*)right_void;
  switch(symbol[0]) {
    case '+':
      if (*left == 0 && *right == 0) {
        return alloc_numV(left[1] + right[1]);
      }
      return NULL;

    case '-':
      if (*left == 0 && *right == 0) {
        return alloc_numV(left[1] - right[1]);
      }
      return NULL;

    case '*':
      if (*left == 0 && *right == 0) {
        return alloc_numV(left[1] * right[1]);
      }
      return NULL;

    case '/':
      if (*left == 0 && *right == 0) {
        if (right[1] == 0)
          return NULL;
        else
          return alloc_numV(left[1] / right[1]);
      }
      return NULL;

    case 'e':
      //if ()
      return NULL;

    case '<':
      return NULL;
      
    default:
      return NULL;
  }
}

// evaluates an ExprC into a Value
void* interp(void* expr) { // add environment support
  lamC *lamc;
  binopC *binopc;
  appC *appc;

  switch(*(int*)expr) {
    case 0:  // numC
      return alloc_numV(0);

    case 1:  // boolC
      return alloc_numV(0);

    case 2:  // idC
      return alloc_numV(0);

    case 3:  // ifC
      return alloc_numV(0);

    case 4:  // lamC
      lamc = (lamC*)expr;
      return NULL;
      
    case 5:  // binopC
      binopc = (binopC*)expr;
      return NULL;
      
    case 6:  // appC
      appc = (appC*)expr;
      return NULL;
     
    default:
      return NULL;
  }
}

int main(char** args) {
  printf("Hello world.\n");
  return 0;
}

