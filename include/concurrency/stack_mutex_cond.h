#ifndef STACK_MUTEX_COND_H
#define STACK_MUTEX_COND_H

#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct Node {
  struct Node *next;
  char data[];

} Node;

typedef struct Stack {
  Node *top;
  size_t elem_size;
  pthread_mutex_t lock;
  pthread_cond_t not_empty;
} Stack;

#ifdef __cplusplus
extern "C" {
#endif

int stack_init(Stack *s, size_t elem_size);

int stack_push(Stack *s, const void *elem);

void stack_pop(Stack *s, void *out_elem);

bool stack_try_pop(Stack *s, void *out_elem);

void stack_destroy(Stack *s);

#ifdef __cplusplus
}
#endif

#endif // STACK_MUTEX_COND_H