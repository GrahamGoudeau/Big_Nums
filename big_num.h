#ifndef BIG_NUM_H
#define BIG_NUM_H

#include <stdbool.h>

typedef size_t num_index;

struct big_num_s;
typedef struct big_num_s *big_num_p;

/* parse either a single big_num or the result of arithmetic expression
 * from string input, with null terminating character; 
 * expects all-numeric input with either zero or one operator
 */
extern big_num_p parse_big_num(char *input);

extern void print_big_num(big_num_p num);

extern void free_big_num(big_num_p num);

/* Arithmetic functions return new big_num_p with result of calculation 
 * They have the form add(op1, op2) = op1 + op2 and sub(op1, op2) = op1 - op2
 */
extern big_num_p add(big_num_p operand1, big_num_p operand2);
extern big_num_p subtract(big_num_p operand1, big_num_p operand2);


/* true if operand1 <= operand2, false otherwise */
extern bool leq(big_num_p operand1, big_num_p operand2);
/* check if operand1 == operand2 */
extern bool eq(big_num_p operand1, big_num_p operand2);

/* has behavior: for (i = start; i < end; i += incr) {loop_body()} */
extern void for_loop(big_num_p start, big_num_p incr, big_num_p end, 
                     void loop_body(big_num_p i, void *cl), void *cl);



#endif
