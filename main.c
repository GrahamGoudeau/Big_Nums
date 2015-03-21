#include <stdlib.h>


#include <stdio.h>
#include <limits.h>
#include "parse.h"
#include "big_num.h"

void loop_body(big_num_p i, void *cl)
{
        (void)cl;
        print_big_num(i);
}

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
        print_big_num(result);
        free_big_num(result);
        free_big_num(new_num2);
        free_big_num(new_num);
        
        /*
        fprintf(stderr, "i start: \n");
        fscanf(stdin, "%s", input);
        big_num_p start = parse_big_num(input);
        big_num_p incr = parse_big_num("1");
        fprintf(stderr, "i end: \n");
        fscanf(stdin, "%s", input);
        big_num_p end = parse_big_num(input);
        for_loop(start, incr, end, loop_body, NULL);
        free_big_num(start);
        free_big_num(incr);
        end = trim_storage(end);
        free_big_num(end);
        */
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
