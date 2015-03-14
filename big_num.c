#include <stdlib.h>
#include <stdio.h>
#include "big_num.h"

typedef size_t num_index;

const unsigned INT_32_LEN = 32;
const signed char NUM_DELIM = -1;

/* FOR NOW: LENGTH OF A NUMBER LIMITED TO UNSIGNED LONG LONG MAX */

/* DIGITS STORED LITTLE ENDIAN */

/* store each digit in 1 byte, -1 indicating end of representation */
struct big_num_s
{
        signed char *dig_seq;
};

typedef struct big_num_s big_num_s;

big_num_p init_big_num(void)
{
        big_num_p new_num = malloc(sizeof(big_num_s));
        new_num->dig_seq = malloc(INT_32_LEN * sizeof(char));

        unsigned i;
        for (i = 0; i < INT_32_LEN; i++) {
                if (i == INT_32_LEN - 1)
                        new_num->dig_seq[i] = -1;
                else new_num->dig_seq[i] = 0;
        }

        return new_num;
}

big_num_p init_big_num_len(num_index num_len)
{
        big_num_p new_num = malloc(sizeof(big_num_s));
        new_num->dig_seq = malloc(num_len * sizeof(char));

        num_index i;
        for (i = 0; i < num_len; i++) {
                if (i == num_len - 1)
                        new_num->dig_seq[i] = -1;
                else new_num->dig_seq[i] = 0;
        }

        return new_num;
}

num_index get_num_len(big_num_p num)
{
        num_index count = 0;
        while (num->dig_seq[count] != NUM_DELIM)
                count++;

        return count;
}

big_num_p parse_big_num(char *input)
{
        num_index len = 0;
        while (input[len] != 0)
                len++;

        big_num_p new_num = init_big_num_len(len*2);
        num_index i;
        for (i = len; i > 0; i--) {
                unsigned digit = (input[i - 1]) - '0';
                new_num->dig_seq[len - i] = digit;
        }

        return new_num;
}

void free_big_num(big_num_p num)
{
        if (num == NULL)
                return;

        if (num->dig_seq != NULL)
                free(num->dig_seq);

        free(num);
}

void print_dig(big_num_p num, num_index digit)
{
        fprintf(stdout, "%d", num->dig_seq[digit]);
}

void print_big_num(big_num_p num)
{
        /* get to end of number */
        num_index digit = get_num_len(num);

        /* get to first digit of number */
        digit--;
        while (digit != 0 && num->dig_seq[digit] == 0)
                digit--;

        /* no nonzero digits */
        if (digit <= 0) {
                fprintf(stdout, "%d", num->dig_seq[digit]);
                return;
        }

        while (digit != 0) {
                print_dig(num, digit);
                digit--;
        }
        print_dig(num, digit);
}
        

big_num_p expand_big_num(big_num_p old_num)
{
        num_index i;
        num_index num_len = get_num_len(old_num);

        big_num_p new_num = init_big_num_len(num_len * 2); 
        for (i = 0; i < num_len; i++) {
                new_num->dig_seq[i] = old_num->dig_seq[i];
        }
        for (i = num_len; i < num_len * 2; i++) {
                if (i == (num_len * 2) - 1)
                        new_num->dig_seq[i] = -1;
                else new_num->dig_seq[i] = 0;
        }

        free_big_num(old_num);
        return new_num;
}

