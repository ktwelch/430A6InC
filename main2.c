#include "AST.h"
#include "values.h"
#include "env.h"
#include <stdio.h>


void* interp(void* expr, binding *env) {
	ifC *ifc;
	switch (*(int*)expr) {
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
	}
}


void main() {
	binding *env = new_binding();
	add_binding(&env, "x", alloc_numV(42));
	printf("%s \n", (((boolV*) interp(alloc_boolC(1), NULL))->bool == 1) ? "pass" : "fail");
	printf("%s \n", (((numV*) interp(alloc_numC(-1), NULL))->num == -1) ? "pass" : "fail");
	printf("%s \n", (((numV*) interp(alloc_idC("x"), env))->num == 42) ? "pass" : "fail");
	printf("%s \n", (((numV*) interp(alloc_idC("y"), env)) == NULL) ? "pass" : "fail");
	printf("%s \n", (((numV*) interp(alloc_ifC(alloc_boolC(1), alloc_numC(42), alloc_numC(21)), NULL))->num == 42) ? "pass" : "fail");
}