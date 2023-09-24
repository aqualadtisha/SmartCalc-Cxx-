#include "stack.h"

#include "s21_SmartCalc.h"

LIST *init() {
  LIST *root = (LIST *)calloc(1, sizeof(LIST));
  if (root != NULL) {
    *root = (LIST){0};
    root->top = NULL;
    root->start = 1;
    root->leksema = 1;
  }
  return root;
}

LIST *push(LIST *root) {
  LIST *new = NULL;
  if (root != NULL) {
    new = (LIST *)calloc(1, sizeof(LIST));
    if (new != NULL) {
      *new = (LIST){0};
      LIST *run = root;
      while (run->top != NULL) {
        run = run->top;
      }
      run->top = new;
    }
  }
  return new;
}

LIST *top_elem(LIST *root) {
  LIST *run = root;
  while (run != NULL && run->top != NULL) {
    run = run->top;
  }
  return run;
}

void pop_next_elem(LIST *elem) {
  if (elem != NULL && elem->top != NULL) {
    LIST *run = elem->top;
    elem->top = run->top;
    free(run);
  }
}

void copy_elem(LIST *stack, LIST *list) {
  if (stack != NULL && list != NULL) {
    list = push(list);
    if (list != NULL) {
      list->leksema = stack->leksema;
      list->priority = stack->priority;
      list->type = stack->type;
      list->top = stack->top;
    }
  }
}

void pop_end(LIST **root) {
  LIST *run = *root;
  if (run != NULL && run->top != NULL) {
    while (run->top->top != NULL) {
      run = run->top;
    }
    free(run->top);
    run->top = NULL;
  }
}

void destroy(LIST *root) {  // go to last and while
  LIST *run = root;
  if (run->top != NULL) destroy(run->top);
  free(run);
}

// void destroy(LIST *root) {
//   while(root != NULL) {
//     LIST *run = root;
//     while (run->top != NULL) {
//       run = run->top;
//     }
//     free(run);
//   }
// }