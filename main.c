#include <stdlib.h>


#include <stdio.h>
#include "parse.h"
#include "big_num.h"
int main(int argc, char *argv[])
{
        (void)argc;(void)argv;
         
        char input[1000];
        fscanf(stdin, "%s", input);
        big_num_p new_num = parse_big_num(input);
        fscanf(stdin, "%s", input);
        big_num_p new_num2 = parse_big_num(input);
        //new_num = resize_big_num(new_num, 10);
        big_num_p result;
        //result = add(new_num, new_num2);      
        result = subtract(new_num, new_num2);
        print_all_info(result);
        print_big_num(result);
        fprintf(stdout, "\n");
        free_big_num(result);
        free_big_num(new_num2);
        free_big_num(new_num);
        /* 
        char *new_input = readline(stdin);
        big_num_p result = parse_binary_exp(new_input); 
        fprintf(stderr, "parsing second\n");
        big_num_p result2 = parse_binary_exp(new_input);
        fprintf(stderr, "done\n");
        big_num_p final = add(result, result2);
        free(new_input);
        print_big_num(final);
        print_all_info(result);
        fprintf(stdout, "\n");
        free_big_num(result2);
        free_big_num(final);
        free_big_num(result);
        */
        return EXIT_SUCCESS;
}
