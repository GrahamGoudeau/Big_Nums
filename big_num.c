#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "big_num.h"

typedef signed char digit_type;
const digit_type DEC_BASE = 10;

#define MOD(x) (x % DEC_BASE < 0) ? (x % DEC_BASE) + DEC_BASE : x % DEC_BASE
#define XOR(A,B) A ? !B : B

const unsigned INT_32_LEN = 32;
const signed char NUM_DELIM = -1;
const unsigned INPUT_DELIM = 0;



/* FOR NOW:
 * numbers can only be indexed by numbers within size_t 
 */

/* DIGITS STORED LITTLE ENDIAN */

/* store each digit in 1 byte, NUM_DELIM indicating end of representation */
struct big_num_s
{
        digit_type *dig_seq;
        bool is_positive;
};

typedef struct big_num_s big_num_s;


big_num_p init_big_num(void)
{
        big_num_p new_num = malloc(sizeof(big_num_s));
        new_num->dig_seq = malloc(INT_32_LEN * sizeof(char));

        unsigned i;
        for (i = 0; i < INT_32_LEN; i++) {
                if (i == INT_32_LEN - 1)
                        new_num->dig_seq[i] = NUM_DELIM;
                else new_num->dig_seq[i] = 0;
        }
        new_num->is_positive = true;

        return new_num;
}

big_num_p init_big_num_len(num_index num_len)
{
        // take this out?
        num_len += 1;
        big_num_p new_num = malloc(sizeof(big_num_s));
        new_num->dig_seq = malloc(num_len * sizeof(char));

        num_index i;
        for (i = 0; i < num_len; i++) {
                if (i == num_len - 1)
                        new_num->dig_seq[i] = -1;
                else new_num->dig_seq[i] = 0;
        }
        new_num->is_positive = true;

        return new_num;
}

num_index get_num_len(big_num_p num)
{
        num_index count = 0;
        while (num->dig_seq[count] != NUM_DELIM)
                count++;

        return count;
}

big_num_p trim_storage(big_num_p num)
{
        num_index stor_len = get_num_len(num);
        while (num->dig_seq[stor_len] == NUM_DELIM || 
                num->dig_seq[stor_len] == 0)
                stor_len--;
        
        big_num_p trimmed = init_big_num_len(stor_len + 1);
        trimmed->is_positive = num->is_positive;

        while (stor_len != 0) {
                trimmed->dig_seq[stor_len] = num->dig_seq[stor_len];
                stor_len--;
        }
        trimmed->dig_seq[stor_len] = num->dig_seq[stor_len];
        free_big_num(num);
        return trimmed;
}

big_num_p parse_big_num(char *input)
{
        /* get length of input to terminating null character */
        num_index len = 0;
        while (input[len] == ' ')
                len++;
        bool is_positive = true;
        if (input[len] == '-') {
                is_positive = false;
                len++;
        }

        while (input[len] != INPUT_DELIM)
                len++;

        //big_num_p new_num;
        /*
        if (len >= INT_32_LEN)
                new_num = init_big_num_len(len*2);
        else
                new_num = init_big_num();
        */
        big_num_p new_num = init_big_num_len(len + 1);
        num_index i;
        for (i = len; i > 0; i--) {
                if (input[i - 1] != '-') {
                        digit_type digit = (input[i - 1]) - '0';
                        new_num->dig_seq[len - i] = digit;
                }
        }

        new_num->is_positive = is_positive;
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
        if (!num->is_positive)
                fprintf(stdout, "-");

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
        

void print_all_info(big_num_p num)
{
        num_index len = get_num_len(num) + 1;
        for (num_index i = 0; i < len; i++) 
                fprintf(stderr, "%d", num->dig_seq[i]);
        fprintf(stderr, (num->is_positive) ? " positive" : " nonpositive");
        fprintf(stderr, "\n");
}

big_num_p subtract(big_num_p, big_num_p);
num_index first_nonzero(big_num_p, num_index);

big_num_p unsigned_add(big_num_p operand1, big_num_p operand2)
{
        num_index len1 = get_num_len(operand1);
        num_index len2 = get_num_len(operand2);

        /* The maximum new length can be the longest original + 1 (if carry) */
        num_index sum_len = (len1 >= len2) ? len1 + 1 : len2 + 1;

        big_num_p result = init_big_num_len(sum_len + 1);
        digit_type carry = 0;
        num_index i;
        for (i = 0; i < sum_len - 1; i++) {
                /* if we are adding digits past the len of an operand, add 0 */
                digit_type digit1 = (i >= len1) ? 0 : operand1->dig_seq[i];
                digit_type digit2 = (i >= len2) ? 0 : operand2->dig_seq[i];

                /* add the digits and any existing carry bit */
                digit_type sum = digit1 + digit2 + carry;

                /* reset carry bit if necessary */
                carry = (sum >= DEC_BASE) ? 1 : 0;

                result->dig_seq[i] = (sum % 10);
        }
        /* if we have a carry left over, add it in the most significant place */
        if (carry == 1)
                result->dig_seq[i] = 1;

        return result;

}

big_num_p signed_add(big_num_p operand1, big_num_p operand2)
{
        big_num_p result;
        /* - - */
        if ((!operand1->is_positive) && (!operand2->is_positive)) {
                result = unsigned_add(operand1, operand2);
                result->is_positive = false;
        }

        /* + - */
        else if (operand1->is_positive && !operand2->is_positive) {
                operand2->is_positive = true;
                result = subtract(operand1, operand2);
                operand2->is_positive = false;
        }

        /* - + */
        else {
                operand1->is_positive = true;
                result = subtract(operand2, operand1);
                operand1->is_positive = false;
        }
        return result;
}

big_num_p add(big_num_p operand1, big_num_p operand2)
{
        big_num_p result;
        if ((!operand1->is_positive) || (!operand2->is_positive))
                result = signed_add(operand1, operand2);

        else result = unsigned_add(operand1, operand2);
        result = trim_storage(result);
        return result;
}

big_num_p unsigned_subtract(big_num_p operand1, big_num_p operand2)
{
        if (leq(operand1, operand2) && !leq(operand2, operand1)) {
                big_num_p result = unsigned_subtract(operand2, operand1);
                result->is_positive = false;
                return result;
        } 
        
        num_index len1 = get_num_len(operand1);
        num_index len2 = get_num_len(operand2);

        num_index sub_len = (len1 >= len2) ? len1 : len2;

        big_num_p result = init_big_num_len(sub_len + 1);
        num_index i;
        for (i = 0; i < sub_len - 1; i++) {
                digit_type digit1 = (i >= len1) ? 0 : operand1->dig_seq[i];
                digit_type digit2 = (i >= len2) ? 0 : operand2->dig_seq[i];
                digit_type sub = MOD(digit1 - digit2);        
                result->dig_seq[i] = sub;
                if (digit2 > digit1)
                        operand1->dig_seq[i + 1] -= 1;
        } 
        return result;
}

big_num_p signed_subtract(big_num_p operand1, big_num_p operand2)
{
        big_num_p result;
        /* + - */
        if (operand1->is_positive && !(operand2->is_positive)) {
                operand2->is_positive = true;
                result = add(operand1, operand2);
                operand2->is_positive = false;
        }
        /* - + */
        else if ((!(operand1->is_positive)) && (operand2->is_positive)) {
                operand1->is_positive = true;
                result = add(operand1, operand2);
                operand1->is_positive = false;
                result->is_positive = false;
        }
        /* else both negative */
        /* - - */
        else {
                operand1->is_positive = true;
                operand2->is_positive = true;
                result = subtract(operand2, operand1);
                operand1->is_positive = false;
                operand2->is_positive = false;
        }
        return result;
}

/* assume operand2 <= operand1 */
big_num_p subtract(big_num_p operand1, big_num_p operand2)
{
        big_num_p result;
        if (operand1->is_positive && operand2->is_positive)
                result = unsigned_subtract(operand1, operand2);
        else result = signed_subtract(operand1, operand2);

        result = trim_storage(result);
        return result;
}

big_num_p multiply(big_num_p operand1, big_num_p operand2)
{
        num_index len1 = get_num_len(operand1);
        num_index len2 = get_num_len(operand2);
        bool op1_pos = operand1->is_positive;
        bool op2_pos = operand2->is_positive;

        /* XOR the positive indicators from the operands */
        bool result_positive = op1_pos ? !op2_pos : op2_pos;
        
        /* max length of mult result is log(len1) + log(len2) (+ extra space) */
        num_index mult_len = len1 + len2 + 1;
        big_num_p result = init_big_num_len(mult_len); 
        num_index i;
        (void)i;(void)result_positive;return result;
}

num_index first_nonzero(big_num_p operand, num_index start)
{
        num_index index = start;
        while (operand->dig_seq[index] == 0 && index != 0)
                index--;

        return index + 1;
}

/* return true if operand1 <= operand2, false otherwise */
bool leq(big_num_p operand1, big_num_p operand2)
{
        num_index storage_len1 = get_num_len(operand1) - 1;
        num_index storage_len2 = get_num_len(operand2) - 1;
        
        /* find numerical length (disregarding extra storage) of each operand */
        num_index numeric_len1 = first_nonzero(operand1, storage_len1);
        num_index numeric_len2 = first_nonzero(operand2, storage_len2);

        /* check the lengths of both operands */
        if (numeric_len1 != numeric_len2) return numeric_len1 < numeric_len2;

        num_index index = numeric_len1;
        while (index != 0) {
                if (operand1->dig_seq[index] == NUM_DELIM ||
                    operand2->dig_seq[index] == NUM_DELIM) {
                        index--;
                        continue;
                }

                if (operand1->dig_seq[index] > operand2->dig_seq[index]) 
                        return false;
                index--;
        }
        if (operand1->dig_seq[index] > operand2->dig_seq[index]) 
                return false;
        
        return true;
}

bool eq(big_num_p operand1, big_num_p operand2)
{
        return leq(operand1, operand2) && leq(operand2, operand1);
}

big_num_p copy_big_num(big_num_p orig)
{
        num_index len = get_num_len(orig);
        big_num_p copy = init_big_num_len(len + 1);
        num_index i;
        for (i = 0; i < len + 1; i++)
                copy->dig_seq[i] = orig->dig_seq[i];

        return copy;
}

void for_loop(big_num_p start, big_num_p incr, big_num_p end, 
              void loop_body(big_num_p i, void *cl), void *cl)
{
        big_num_p i = copy_big_num(start);

        while (!eq(i, end)) {
                loop_body(i, cl);        
        
                big_num_p new_i = add(i, incr);
                free_big_num(i);
                i = new_i;
        } 

        free_big_num(i);
}

/*
digit_type mod(digit_type dig)
{
        digit_type result = dig % DEC_BASE;
        return (result < 0) ? result + DEC_BASE : result;
}
*/
