#include <stdlib.h>


#include <stdio.h>
#include "big_num.h"
int main(int argc, char *argv[])
{
        (void)argc;(void)argv;
        /*char c = ' ';
        char delimiter = '\n';
        while (c != delimiter) {
                c = getchar();
                fprintf(stderr, "%c", c);
        }
        */
        big_num_p num = init_big_num();
        print_big_num(num);
        num = expand_big_num(num);
        print_big_num(num);
        printf("\n");
        free_big_num(num);
        
        char input[10];
        fscanf(stdin, "%s", input);
        big_num_p new_num = parse_big_num(input);
        fscanf(stdin, "%s", input);
        printf("\n");
        big_num_p new_num2 = parse_big_num(input);
        new_num2 = expand_big_num(new_num2);
        new_num = resize_big_num(new_num, 10000);
        print_big_num(new_num);
        free_big_num(new_num2);
        fprintf(stdout, "\n");
        free_big_num(new_num);
        return EXIT_SUCCESS;
}
