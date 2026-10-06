#include "stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void init(Stack *s);
void destroy(Stack *s);
void push(Stack *s, int element);
int pop(Stack *s);
bool isEmpty(const Stack *s);

void init(Stack *s) {
  if (s == NULL)
    return;
  s->size = 0;
  s->capacity = 0;
  s->data = malloc(INIT_CAP * sizeof(int));
  if (s->data == NULL) {
    s->status = STACK_ERR_NULL;
    return;
  }
  s->capacity = INIT_CAP;
}

void destroy(Stack *s) {
  if (s == NULL) {
    s->status = STACK_ERR_EMPTY;
    return;
  }
  free(s->data);
  s->size = 0;
  s->capacity = 0;
}

bool expand(Stack *s) {
  size_t new_cap;
  if (s->capacity == 0)
    new_cap = INIT_CAP;
  else {
    if (s->capacity > SIZE_MAX / CAP_FACTOR) {
      s->status = STACK_ERR_ALLOC;
      return false;
    }
    new_cap = s->capacity * CAP_FACTOR;
  }
  if (new_cap > SIZE_MAX / sizeof(int)) {
    s->status = STACK_ERR_ALLOC;
    return false;
  }

  int *tmp = realloc(s->data, new_cap * sizeof(int));
  if (tmp == NULL) {
    s->status = STACK_ERR_ALLOC;
    return false;
  }

  s->data = tmp;
  s->capacity = new_cap;
  return true;
}

void push(Stack *s, int element) {
  if (s == NULL)
    return;
  if (s->size == s->capacity && !expand(s))
    return;
  s->data[s->size++] = element;
}

int pop(Stack *s) {
  if (s == NULL || s->size <= 0)
    return 0;
  return s->data[s->size--];
}

bool isEmpty(const Stack *s) { return s == NULL || s->size <= 0; }
