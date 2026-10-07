#pragma once

#include <stdbool.h>
#include <stddef.h>

typedef enum {
  STACK_OK = 0,
  STACK_ERR_ALLOC,
  STACK_ERR_EMPTY,
  STACK_ERR_NULL
} Status;

typedef struct {
  int *data;
  size_t size;
  size_t capacity;
  Status status;
} Stack;

void init(Stack *s);
void destroy(Stack *s);
void push(Stack *s, int element);
int pop(Stack *s);
bool isEmpty(const Stack *s);
