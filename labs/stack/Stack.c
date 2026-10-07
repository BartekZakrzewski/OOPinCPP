#include "Stack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define INIT_CAP 4
#define CAP_FACTOR 2

void init(Stack *s) {
  if (s == NULL)
    return;
  s->size = 0;
  s->capacity = 0;
  s->status = STACK_OK;
  s->data = malloc(INIT_CAP * sizeof(int));
  if (s->data == NULL) {
    s->status = STACK_ERR_ALLOC;
    return;
  }
  s->capacity = INIT_CAP;
}

void destroy(Stack *s) {
  if (s == NULL)
    return;
  free(s->data);
  s->data = NULL;
  s->size = 0;
  s->capacity = 0;
}

static bool expand(Stack *s) {
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
  s->status = STACK_OK;
}

int pop(Stack *s) {
  if (s == NULL)
    return 0;
  if (s->size == 0) {
    s->status = STACK_ERR_EMPTY;
    return 0;
  }
  s->status = STACK_OK;
  return s->data[--s->size];
}

bool isEmpty(const Stack *s) { return s == NULL || s->size == 0; }
