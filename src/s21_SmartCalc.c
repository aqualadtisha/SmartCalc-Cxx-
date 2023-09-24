#include "s21_SmartCalc.h"

double s21_SmartCalc(const char *str, double x, int *Error) {
  Counts C = {0};
  C.x = x;
  double result = 0;
  LIST *root_l = init();
  if (strlen((const char *)str) > 255) C.error = ERROR;
  if (root_l != NULL && C.error == OK) {
    int line[256] = {0};
    no_tab_str(str, line, &C);
    if (strlen((const char *)line) == 0) C.error = ERROR;
    validator(line, &C);
    if (C.error == OK) {
      parsing_init(line, &C, root_l);
      result = calculate(root_l, &C);
    } else
      C.error = -1;
    destroy(root_l);
  }
  *Error = C.error;
  return result;
}

void no_tab_str(const char *str, int *line, Counts *C) {
  int j = 0, is_number = 0, is_tab = 0;
  for (int i = 0; str[i] != '\0'; i++) {
    if (str[i] != ' ') {
      line[j++] = (int)str[i];
      if (is_numb((int)str[i])) {
        if (is_number == 1 && is_tab == 1) C->error = ERROR;
        is_number = 1;
      } else {
        is_number = 0;
      }
      is_tab = 0;
    } else {
      is_tab = 1;
    }
  }
  line[j] = '\0';
}

void validator(int *line, Counts *C) {
  if ((is_operand(line[0])) && line[0] != '+' && line[0] != '-')
    C->error = ERROR;
  for (; !C->error && line[C->i] != '\0'; C->i++) {
    if (is_math_word(line[C->i])) {  // check maths
      math_validator(line, C);
      memset(C->str, 0, 6);
    } else if (line[C->i] == ')') {  // check brackets
      if (C->l_count == 0 || line[C->i - 1] == '(' ||
          is_numb_or_math(line[C->i + 1]))
        C->error = ERROR;
      C->r_count++;
    } else if (line[C->i] == '(') {
      if (C->i != 0 && is_numb(line[C->i - 1])) C->error = ERROR;
      C->l_count++;
    } else if (is_numb(line[C->i])) {  // check numb
      numb_validator(line, C);
      if (line[C->i + 1] != '\0' &&
          (is_word(line[C->i + 1]) && line[C->i + 1] != 'm'))
        C->error = ERROR;
    } else if (is_operand(line[C->i])) {  // check operands
      if (!(line[C->i + 1] == '+' || line[C->i + 1] == '-' ||
            is_numb_or_math(line[C->i + 1]) || line[C->i + 1] == '('))
        C->error = ERROR;
    } else if (line[C->i] == 'x') {
      if (line[C->i + 1] == 'x') C->error = ERROR;
    } else {  // error symbols
      C->error = ERROR;
    }
  }
  if (C->r_count != C->l_count) C->error = ERROR;
  C->i = 0;
}

void math_validator(const int *line, Counts *C) {
  for (int j = 0;  j < 6 && is_word(line[C->i]) && line[C->i] != '\0';
       C->i++, j++) {
    C->str[j] = (char)line[C->i];
  }
  if (!(is_math_func(C->str))) C->error = ERROR;
  if (!strcmp(C->str, "mod")) {
    if (!is_numb(line[C->i - 4]) || !is_numb(line[C->i])) C->error = ERROR;
  } else {
    if (line[C->i] != '(') {
      C->error = ERROR;
    } else {
      C->l_count++;
      if (!(is_numb_or_math(line[C->i + 1]) || is_bracket(line[C->i + 1]) ||
            line[C->i + 1] == '-'))
        C->error = ERROR;
    }
  }
}

void numb_validator(const int *line, Counts *C) {
  int p_count = 0;
  for (; !C->error && (is_numb(line[C->i]) || is_point(line[C->i])); C->i++) {
    if (is_point(line[C->i])) {
      if (p_count) {
        C->error = ERROR;
      } else {
        p_count++;
      }
    }
  }
  C->i--;
}

void parsing_init(const int *line, Counts *C, LIST *root_l) {
  LIST *root_s = init();
  if (root_s == NULL) {
    C->error = ERROR;
  } else {
    LIST *top_s = root_s;
    LIST *top_l = root_l;
    for (; line[C->i] != '\0' && C->error != ERROR; C->i++) {
      if (line[C->i] == '-' && (C->i == 0 || line[C->i - 1] == '(' ||
                                is_operand(line[C->i - 1]))) {  // unary - check
        unary_minus_add(line, C, root_s, top_s);
      } else {
        parser(line, C, root_l, root_s, top_s, top_l);
      }
    }
    top_s = top_elem(root_s);
    take_from_stack(top_s, &root_s, root_l, 0);
    destroy(root_s);
  }
}

void unary_minus_add(const int *line, Counts *C, LIST *root_s, LIST *top_s) {
  if (is_numb_or_math(line[C->i + 1]) || line[C->i + 1] == '(' ||
      line[C->i + 1] == '-' || line[C->i + 1] == '+') {
    top_s = push(root_s);
    top_s->leksema = unary_SUB;
    top_s->type = Function;
    top_s->priority = 8;
  } else {
    C->error = ERROR;
  }
}

LIST *take_from_stack(LIST *top, LIST **root_s, LIST *root_l, int priority) {
  top = top_elem(*root_s);
  while (top->start != 1 && *root_s != NULL && top->leksema != L_bracket &&
         priority <= top->priority) {
    copy_elem(top, root_l);
    pop_end(root_s);
    top = top_elem(*root_s);
  }
  return top;
}

void parser(const int *line, Counts *C, LIST *root_l, LIST *root_s, LIST *top_s,
            LIST *top_l) {
  top_s = top_elem(root_s);

  if (line[C->i] == ')') {                       // bracket
    take_from_stack(top_s, &root_s, root_l, 0);  // top_s =
    pop_end(&root_s);
  } else if (line[C->i] == '(') {
    top_s = push(root_s);
    if (top_s == NULL)
      C->error = ERROR;
    else
      top_s->leksema = L_bracket;
  } else {  // isn't bracket

    if (is_numb(line[C->i]) || line[C->i] == 'x') {  // numb
      numb_add_to_list(line, C, top_l, root_l);
    } else {  // isn't numb

      if (is_operand(line[C->i])) {
        int priority = priority_check(line[C->i]);
        if (top_s != NULL && top_s->start != 1 && top_s->priority >= priority &&
            !(is_max_priority(top_s->priority, priority))) {
          top_s = take_from_stack(top_s, &root_s, root_l, priority);
        }
        if (top_s != NULL) {
          if (top_s->leksema != 0 || top_s->start == 1) {
            top_s = push(root_s);
          }
        }
        if (top_s == NULL) {
          C->error = ERROR;
        } else {
          top_s->priority = priority;
          top_s->leksema = operand_check(line[C->i]);
        }

      } else if (is_math_word(line[C->i])) {
        math_add_to_list(line, C, top_s, root_l, root_s);
      }
      if (C->error == OK) {
        top_s = top_elem(root_s);
        top_s->type = Function;
      }
    }
  }
}

void numb_add_to_list(const int *line, Counts *C, LIST *top_l, LIST *root_l) {
  if (C->i != 0 || top_l->start == 1) top_l = push(root_l);
  if (line[C->i] == 'x') {
    top_l->numb = C->x;
  } else {
    if (is_numb(line[C->i + 1]) || is_point(line[C->i + 1])) {
      top_l->numb = numb_count(line, C);
    } else {
      top_l->numb = (line[C->i] - '0');
    }
  }
  top_l->type = Number;
}

void math_add_to_list(const int *line, Counts *C, LIST *top_s, LIST *root_l,
                      LIST *root_s) {
  math_validator(line, C);
  if (line[0] == line[1]) C->error = ERROR;
  C->i--;
  int leksema = math_check(C->str);
  if (leksema == -1) C->error = ERROR;
  int priority = leksema == MOD ? 2 : 8;
  if (top_s->priority >= priority &&
      !(is_max_priority(top_s->priority, priority))) {
    take_from_stack(top_s, &root_s, root_l, priority);
  }
  if (top_s->leksema != 0) top_s = push(root_s);
  if (top_s == NULL)
    C->error = ERROR;
  else {
    top_s->priority = priority;
    top_s->leksema = leksema;
  }
  memset(C->str, 0, 6);
}

double numb_count(const int *line, Counts *C) {
  double result = 0;
  result_mul(line, C, &result, NULL);
  if (line[C->i] == '.') {
    C->i++;
    int len = 0;
    result_mul(line, C, &result, &len);
    while (len > 0) {
      result *= 0.1;
      len--;
    }
  }
  C->i--;
  return result;
}

void result_mul(const int *line, Counts *C, double *result, int *len) {
  while (is_numb(line[C->i])) {
    *result *= 10;
    *result += (int)(line[C->i++] - '0');
    if (len != NULL) (*len)++;
  }
}

int priority_check(int operand) {
  int priority = 0;
  if (operand == '^') {
    priority = 8;
  } else if (operand == '*' || operand == '/') {
    priority = 2;
  } else if (operand == '-' || operand == '+') {
    priority = 1;
  }
  return priority;
}

int math_check(const char *str) {
  int type = -1;
  char a[10][5] = {"sin",  "cos", "tan", "asin", "acos",
                   "atan", "log", "ln",  "sqrt", "\0"};
  int i = 0;
  while (i < 10 && strcmp(str, a[i])) {
    i++;
  }
  if (i < 9)
    type = i + 2;
  else if (!strcmp(str, "mod"))
    type = MOD;
  return type;
}

int operand_check(int c) {
  int type = -1;
  if (c == '-') {
    type = SUB;
  } else if (c == '+') {
    type = SUM;
  } else if (c == '*') {
    type = MUL;
  } else if (c == '/') {
    type = DIV;
  } else if (c == '^') {
    type = POW;
  }
  return type;
}

double calculate(LIST *root_l, Counts *C) {
  LIST *run = root_l;
  while (root_l->top != NULL && run->top->top != NULL) {
    while (run->top->top != NULL && run->top->top->type != Function) {
      run = run->top;
    }

    if (run->top->type == Number && run->type == Number &&
        run->top->top->type == Function && run->top->top->leksema > unary_SUB) {
      if (run->top->top->leksema == SUM) run->numb = run->numb + run->top->numb;
      if (run->top->top->leksema == SUB) run->numb = run->numb - run->top->numb;
      if (run->top->top->leksema == MUL) run->numb = run->numb * run->top->numb;
      if (run->top->top->leksema == DIV) run->numb = run->numb / run->top->numb;
      if (run->top->top->leksema == MOD)
        run->numb = fmod(run->numb, run->top->numb);
      if (run->top->top->leksema == POW)
        run->numb = pow(run->numb, run->top->numb);
      pop_next_elem(run);
      pop_next_elem(run);
    } else if (run->top->type == Number && run->top->top->type == Function) {
      if (run->top->top->leksema == SIN) run->top->numb = sin(run->top->numb);
      if (run->top->top->leksema == ASIN) run->top->numb = asin(run->top->numb);
      if (run->top->top->leksema == COS) run->top->numb = cos(run->top->numb);
      if (run->top->top->leksema == ACOS) run->top->numb = acos(run->top->numb);
      if (run->top->top->leksema == TAN) run->top->numb = tan(run->top->numb);
      if (run->top->top->leksema == ATAN) run->top->numb = atan(run->top->numb);
      if (run->top->top->leksema == LOG) run->top->numb = log10(run->top->numb);
      if (run->top->top->leksema == LN) run->top->numb = log(run->top->numb);
      if (run->top->top->leksema == SQRT) run->top->numb = sqrt(run->top->numb);
      if (run->top->top->leksema == unary_SUB) run->top->numb = -run->top->numb;
      pop_next_elem(run->top);
    } else
      C->error = ERROR;
    run = root_l;
  }
  if (run->top == NULL) C->error = ERROR;
  return run->top != NULL ? run->top->numb : -1;
}
