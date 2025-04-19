#include "concurrency/stack_mutex_cond.h"
#include <stdlib.h>
#include <string.h>

int stack_init(Stack *s, size_t elem_size) {
  s->top = NULL;
  s->elem_size = elem_size;

  if (pthread_mutex_init(&s->lock, NULL) != 0) {
    return -1;
  }

  if (pthread_cond_init(&s->not_empty, NULL) != 0) {
    pthread_mutex_destroy(&s->lock);
    return -1;
  }

  return 0;
}

int stack_push(Stack *s, const void *elem) {
  Node *n = (Node *)malloc(sizeof(Node) + s->elem_size);

  if (!n) {
    return -1;
  }

  memcpy(n->data, elem, s->elem_size);

  pthread_mutex_lock(&s->lock);
  n->next = s->top;
  s->top = n;
  pthread_cond_signal(&s->not_empty);
  pthread_mutex_unlock(&s->lock);
  return 0;
}

void stack_pop(Stack *s, void *out_elem) {
  pthread_mutex_lock(&s->lock);
  while (s->top == NULL) {
    pthread_cond_wait(&s->not_empty, &s->lock);
  }

  Node *n = s->top;
  s->top = n->next;

  pthread_mutex_unlock(&s->lock);

  memcpy(out_elem, n->data, s->elem_size);
  free(n);
}

bool stack_try_pop(Stack *s, void *out_elem) {
  bool success = false;

  pthread_mutex_lock(&s->lock);
  if (s->top) {
    Node *n = s->top;
    s->top = n->next;

    memcpy(out_elem, n->data, s->elem_size);
    free(n);
    success = true;
  }
  pthread_mutex_unlock(&s->lock);

  return success;
}

void stack_destroy(Stack *s) {
  pthread_mutex_lock(&s->lock);
  Node *cur = s->top;

  while (cur) {
    Node *next = cur->next;
    free(cur);
    cur = next;
  }

  s->top = NULL;
  pthread_mutex_unlock(&s->lock);

  pthread_mutex_destroy(&s->lock);
  pthread_cond_destroy(&s->not_empty);
}