#ifndef BIG_NUM_H
#define BIG_NUM_H

struct big_num_s;
typedef struct big_num_s *big_num_p;

typedef size_t num_index;

// eventually remove this from the header
extern big_num_p expand_big_num(big_num_p num);
extern big_num_p init_big_num(void);
extern big_num_p parse_big_num(char *input);
extern void print_big_num(big_num_p num);
extern void free_big_num(big_num_p num);
extern big_num_p resize_big_num(big_num_p num, num_index len);
extern big_num_p add(big_num_p operand1, big_num_p operand2);

#endif
