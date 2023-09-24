#ifndef C7_SMARTCALC_V1_0_0_SRC_STACK_H_
#define C7_SMARTCALC_V1_0_0_SRC_STACK_H_

typedef struct list {
  int leksema;
  double numb;
  int priority;
  int type;
  int start;
  struct list *top;  // number, operand, math, x
} LIST;

LIST *init();
LIST *push(LIST *root);
void pop_end(LIST **root);
void destroy(LIST *root);
LIST *top_elem(LIST *root);
void copy_elem(LIST *stack, LIST *list);
void pop_next_elem(LIST *elem);

#endif  // C7_SMARTCALC_V1_0_0_SRC_STACK_H_
