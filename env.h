#ifndef ENV_H
#define ENV_H

#include <stdlib.h>
#include <string.h>

typedef struct binding {
  char name[64];
  void *value;
  struct binding *next;
} binding;

binding *new_binding() {
  binding *newBind = malloc(sizeof(binding));
  strcpy(newBind->name, "");
  newBind->value = NULL;
  newBind->next = NULL;
}

void *add_binding(binding **head, char newName[64], void *newValue)
{
  binding * newBinding = malloc(sizeof(binding));
  strcpy(newBinding->name, newName);
  newBinding->value = newValue;
  newBinding->next = *head;
  *head = newBinding;

  return *head;
}

void *look_up(char name[64], binding *env)
{
  while(env != NULL && env->next != NULL)
  {
    if(strcmp(env->name, name) == 0)
    {
      return env->value;
    }
    else
    {
      env = env->next;
    }
  }

  return NULL;
}

void *append(binding *fstHead, binding *sndHead)
{
  binding *temp = fstHead;

  while(temp->next)
  {
    temp = temp->next;
  }

  temp->next = sndHead;
  
  return *fstHead;
}

#endif
