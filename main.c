#include "AST.h"
#include <stdio.h>
#include "values.h"
#include "env.h"
#include "interp.h"

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

binding *extend_env_args(char params[64][64], void* args[64], binding *clo_env, binding *top_env) {
  
  return NULL;
}

// evaluates an ExprC into a Value
void* interp(void* expr, binding* env) {
  lamC *lamc;
  binopC *binopc;
  appC *appc;

  void *left_val;
  void *right_val;
  void *temp;

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
      lamc = (lamC*)expr;  // need environments
      return NULL;
      
    case 5:  // binopC
      binopc = (binopC*)expr;
      left_val = interp(binopc->left, env);
      right_val = interp(binopc->right, env);
      return eval_binop(binopc->op, left_val, right_val);
      
    case 6:  // appC
      appc = (appC*)expr;  // need environments
      temp = interp(appc->fun, env);  // hoping is cloV
      if (*(int*)temp == 2) {
        return interp(((cloV*)temp)->body, extend_env_args(((cloV*)temp)->params, appc->args, ((cloV*)temp)->env, env));  // ASSUMING length of params == length of args
      }
      return NULL;
     
    default:
      return NULL;
  }
}

char *serialize(void *result) {
  char *string;
  float num_result;
  int bool_result;

  string = malloc(16);

  if (!result) {
    return "Error detected.\n";
  }

  switch (*(int*)result) {
    case 0:
      num_result = ((numV*)result)->num;
      snprintf(string, 16, "%.3f\n", num_result);
      return string;
    case 1:
      bool_result = ((boolV*)result)->bool;
      return bool_result ? "true" : "false";
    case 2:
      return "<#procedure>";
  }
}

int main(char** args) {
  char *string;

  //tests
  string = serialize(interp(alloc_binopC("+", alloc_numC(5), alloc_numC(3)), new_binding()));
  printf(string);
  
  return 0;
}








