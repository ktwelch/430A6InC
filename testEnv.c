#include <stdio.h>
#include <stdlib.h>
#include "env.h"
#include "values.h"
#include "AST.h"

int main()
{
  char testName[] = "test name";
  char testName2[] = "test name 2";
  numV *testValue = alloc_numV(4.0);
  numV *testValue2 = alloc_numV(5.0);
  
  binding *env = new_binding();
  add_binding(&env, testName, testValue);
  add_binding(&env, testName2, testValue2);

  binding *temp = env;
  
  while((env->next != NULL))
  {
    printf("Name %s\n", env->name);
    numV * retNumV = env->value;
    printf("Value %lf\n", retNumV->num);
    env = env->next;
  }

  numV *luv = look_up(testName, temp);
  
  if(luv)
  {
    printf("found value %lf bound to the name %s\n", luv->num, "'test name'");
  }
  else
  {
    printf("the id was not found in the env\n");
  }
  
  return 0;
}
