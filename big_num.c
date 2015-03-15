#include <stdlib.h>
#include <stdio.h>
#include "big_num.h"


const unsigned INT_32_LEN = 32;
const signed char NUM_DELIM = -1;
const unsigned INPUT_DELIM = 0;

const unsigned DEC_BASE = 10;

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
        /* get length of input to terminating null character */
        num_index len = 0;
        while (input[len] != INPUT_DELIM)
                len++;

        big_num_p new_num;
        //if (len > INT_32_LEN)
                new_num = init_big_num_len(len*2);
        /*else
                new_num = init_big_num();
*/
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

        if (num->dig_seq != NULL) {
                free(num->dig_seq);
        }

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
        num_index new_len = num_len * 2 + 1;

        big_num_p new_num = init_big_num_len(new_len);

        /* copy existing data */
        for (i = 0; i < num_len; i++) {
                new_num->dig_seq[i] = old_num->dig_seq[i];
        }

        /* fill the new big_num with leading zeroes/-1 sentinel */
        
        for (i = num_len; i < new_len; i++) {
                if (i == new_len - 1)
                        new_num->dig_seq[i] = NUM_DELIM;
                else new_num->dig_seq[i] = 0;
        }
        
        free_big_num(old_num);
        return new_num;
}


big_num_p resize_big_num(big_num_p num, num_index len)
{
        num_index i;
        num_index old_len = get_num_len(num);
        if (len < old_len) {
                fprintf(stderr, "resize: "
                                "resize length less than original length\n");
                exit(1);
        }
        big_num_p resized = init_big_num_len(len);
        for (i = 0; i < old_len; i++) {
                resized->dig_seq[i] = num->dig_seq[i];
        }

        free_big_num(num);
        return resized;
}
/* Current philosophy: make new big_num for result, so old data preserved */
big_num_p add(big_num_p operand1, big_num_p operand2)
{
        num_index len1 = get_num_len(operand1);
        num_index len2 = get_num_len(operand2);

        /* The maximum new length can be the longest original + 1 (if carry) */
        num_index sum_len = (len1 >= len2) ? len1 + 1 : len2 + 1;

        big_num_p result = init_big_num_len(sum_len);
        unsigned char carry = 0;
        for (num_index i = 0; i < sum_len - 1; i++) {
                unsigned char digit1 = (i >= len1) ? 0 : operand1->dig_seq[i];
                unsigned char digit2 = (i >= len2) ? 0 : operand2->dig_seq[i];
                unsigned char sum = digit1 + digit2 + carry;
                carry = (sum >= DEC_BASE) ? 1 : 0;
                result->dig_seq[i] = (sum % 10);
                
        }
        
        return result;
}
