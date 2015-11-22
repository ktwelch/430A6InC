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
        if (right[1] == 0.0f)
          return NULL;
        else
          return alloc_numV(left[1] / right[1]);
      }
      return NULL;

    case 'e':
      if (left[0] == right[0]) {
        if (left[0] == 0) // two numV's
          return alloc_boolV(left[1] - right[1] < 0.001f);
        if (left[0] == 1) // two boolV's
          return alloc_boolV(left[1] == right[1]);
        return alloc_boolV(0);
      }
      else
         return alloc_boolV(0);

    case '<':
      if (*left == 0 && *right == 0) {
        return alloc_numV(left[1] <= right[1]);
      }
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

  void *left_val;
  void *right_val;

  switch(*(int*)expr) {
    case 0:  // numC
      return alloc_numV(0);

    case 1:  // boolC
      return alloc_numV(0);

    case 2:  // idC
      return alloc_numV(0);

    case 3:  // ifC
      return alloc_numV(0);

    case 4:  // lamiC
      lamc = (lamC*)expr;  // need environments
      return NULL;
      
    case 5:  // binopC
      binopc = (binopC*)expr;
      left_val = interp(binopc->left);
      right_val = interp(binopc->right);
      return eval_binop(binopc->op, left_val, right_val);
      
    case 6:  // appC
      appc = (appC*)expr;  // need environments
      return NULL;
     
    default:
      return NULL;
  }
}

int main(char** args) {
  printf("Hello world.\n");
  return 0;
}

