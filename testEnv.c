#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "values.h"
#include "AST.h"

int main()
{
  char testName[] = "test name";
  numV *testValue = alloc_numV(4.0);
  
  binding *env = new_binding();
  add_binding(&env, testName, testValue);
  add_binding(&env, testName, testValue);
  
  while((env->next != NULL) && strcmp(env->next->name, ""))
  {
    printf("Name %s\n", env->name);
    printf("Value \n");
    env = env->next;
  }
  
  return 0;
}
