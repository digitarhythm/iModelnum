#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

int main(int argc, char *argv[]) {
    regex_t preg;
    size_t nmatch = 5;
    regmatch_t pmatch[nmatch];
    int i, j, flag = 0, model, gen, psize;
    char model2, model_tmp, add, footer[3];
     
    if (argc < 2) {
        flag = 1;
    } else {
        if (strcmp(argv[1], "3G") == 0) {
            gen = 2;
            strcpy(footer, "nd");
        } else
        if (strcmp(argv[1], "3GS") == 0) {
            gen = 3;
            strcpy(footer, "rd");
        } else {
            strcpy(footer, "th");
            if (regcomp(&preg, "^([0-9])([sS]?)$", REG_EXTENDED) != 0) {
                printf("regex compile failed.\n");
                exit(1);
            }
           
            model_tmp = argv[1][pmatch[1].rm_so];
            model = atoi(&model_tmp);

            if (regexec(&preg, argv[1], nmatch, pmatch, 0) != 0 || model < 4) {
                flag = 1;
            } else {
                model2 = argv[1][pmatch[2].rm_so];
                add = model - 4;
                if (model2 == 's' || model2 == 'S') {
                    add++;
                }
                gen = model + add;
            }
        }
    }

    if (flag == 1) {
        puts("please input vaid model number.");
        exit(1);
    } else {
        printf("Your iPhone is 'iPhone %d%s Generation'.\n", gen, footer);
    }
}
