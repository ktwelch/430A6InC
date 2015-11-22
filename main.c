#include "AST.h"
#include <stdio.h>
#include <string.h>
#include "values.h"
#include "env.h"

// left and right are Values, returns a Value
void* eval_binop(char* symbol, void* left_void, void* right_void) {
  int* left = (int*)left_void;
  int* right = (int*)right_void;
  switch(symbol[0]) {
    case '+':
      if (*left == 0 && *right == 0) {
        return alloc_numV(((numV*) left_void)->num + ((numV*) right_void)->num);
      }
      return NULL;

    case '-':
      if (*left == 0 && *right == 0) {
        return alloc_numV(((numV*) left_void)->num - ((numV*) right_void)->num);
      }
      return NULL;

    case '*':
      if (*left == 0 && *right == 0) {
        return alloc_numV(((numV*) left_void)->num * ((numV*) right_void)->num);
      }
      return NULL;

    case '/':
      if (*left == 0 && *right == 0) {
        if (((numV*) left_void)->num == 0.0f)
          return NULL;
        else
          return alloc_numV(((numV*) left_void)->num / ((numV*) right_void)->num);
      }
      return NULL;

    case 'e':
      if (left[0] == right[0]) {
        if (left[0] == 0) // two numV's
          return alloc_boolV(((numV*) left_void)->num - ((numV*) right_void)->num < 0.001f);
        if (left[0] == 1) // two boolV's
          return alloc_boolV(((numV*) left_void)->num == ((numV*) right_void)->num);
        return alloc_boolV(0);
      }
      else
         return alloc_boolV(0);

    case '<':
      if (*left == 0 && *right == 0) {
        return alloc_numV(((numV*) left_void)->num <= ((numV*) right_void)->num);
      }
      return NULL;
      
    default:
      return NULL;
  }
}

// evaluates an ExprC into a Value
void* interp(void* expr, binding* env) { // add environment support
  ifC *ifc;
  lamC *lamc;
  binopC *binopc;
  appC *appc;

  void *left_val;
  void *right_val;

  switch(*(int*)expr) {
    case 0: //numC
			return alloc_numV(((struct numC*) expr)->num);
		case 1: //boolC
			return alloc_boolV(((struct boolC*) expr)->bool);
		case 2: ///idC
			return look_up(((struct idC*) expr)->id, env);
		case 3:	//ifC
			ifc = (ifC*)expr;
			void* cond = interp(ifc->cond, env);
			if (*(int*)cond == 1) {
				if (((boolV*) cond)->bool) {
					return interp(ifc->left, env);
				} else {
					return interp(ifc->right, env);
				}
			} else {
				printf("error: ifC conditional was of type: %d \n", *(int*)cond);
			}
    case 4:  // lamiC
      lamc = (lamC*)expr;  // need environments
      return NULL;
      
    case 5:  // binopC
      binopc = (binopC*)expr;
      left_val = interp(binopc->left, env);
      right_val = interp(binopc->right, env);
      return eval_binop(binopc->op, left_val, right_val);
      
    case 6:  // appC
      appc = (appC*)expr;  // need environments
      return NULL;
     
    default:
      return NULL;
  }
}

char *serialize(void *expr) {
  void *result = interp(expr, NULL);
  char *string;
  float num_result;
  int bool_result;

  string = malloc(16);
  switch (*(int*)result) {
    case 0:
      num_result = ((numV*)result)->num;
      snprintf(string, 16, "%.3f", num_result);
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
  	binding *env = new_binding();
	add_binding(&env, "x", alloc_numV(42));
  
  printf("interp tests\n");
	printf("%s \n", (((boolV*) interp(alloc_boolC(1), NULL))->bool == 1) ? "pass" : "fail");
	printf("%s \n", (((numV*) interp(alloc_numC(-1), NULL))->num == -1) ? "pass" : "fail");
	printf("%s \n", (((numV*) interp(alloc_idC("x"), env))->num == 42) ? "pass" : "fail");
	printf("%s \n", (((numV*) interp(alloc_idC("y"), env)) == NULL) ? "pass" : "fail");
	printf("%s \n", (((numV*) interp(alloc_ifC(alloc_boolC(1), alloc_numC(42), alloc_numC(21)), NULL))->num == 42) ? "pass" : "fail");

  printf("serialize tests\n");
  printf("%s \n", strcmp(serialize(interp(alloc_numC(2), NULL)),
    "2.000") ? "fail" : "pass");
  printf("%s \n", strcmp(serialize(interp(alloc_binopC("+", alloc_numC(5), alloc_numC(3)), NULL)),
    "8.000") ? "fail" : "pass");
  printf("%s \n", strcmp(serialize(interp(alloc_binopC("/", alloc_numC(15), alloc_numC(3)), NULL))),
    "3.000") ? "fail" : "pass");
  printf("%s \n", strcmp(serialize(interp(alloc_numC(2), NULL)),
    "2.000") ? "fail" : "pass");
  
  return 0;
}








