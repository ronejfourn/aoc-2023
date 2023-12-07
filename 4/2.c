#include <stdio.h>
#include <ctype.h>

int readnums(int *nums, char **ptr, char delim) {
    int count = 0;
    char *line = *ptr;
    while (*line != delim) {
        if (!isdigit(*line)) {
            line ++;
        } else {
            nums[count] = 0;
            while (isdigit(*line)) {
                nums[count] *= 10;
                nums[count] += *line - '0';
                line++;
            }
            count ++;
        }
    }

    *ptr = line + 1;
    return count;
}

int main() {
    size_t n = 1024;
    char linebuffer[1024];
    char *lineptr = linebuffer;
    int linelen = 0, linecount = 0;
    FILE *fp = fopen("input", "rb");

    int card = 0;
    int copies[512];
    for (int i = 0; i < 512; i ++)
        copies[i] = 1;

    while ((linelen = getline(&lineptr, &n, fp)) != -1) {
        lineptr[linelen - 1] = '|';
        char *charptr = lineptr;
        while (*charptr != ':') charptr++;

        int winning_nums[100], nums_we_have[100];
        int winning_nums_count = readnums(winning_nums, &charptr, '|');
        int nums_we_have_count = readnums(nums_we_have, &charptr, '|');

        int matches = 0;
        for (int i = 0; i < winning_nums_count; i ++) {
            int winning_num = winning_nums[i];
            for (int j = 0; j < nums_we_have_count; j ++) {
                if (nums_we_have[j] == winning_num) {
                    matches += 1;
                    break;
                }
            }
        }

        int copy = copies[card ++];
        for (int i = 0; i < matches; i ++)
            copies[card + i] += copy;
        linecount ++;
    }

    int total = 0;
    for (int i = 0; i < linecount; i ++)
        total += copies[i];

    printf("%d\n", total);
    fclose(fp);

    return 0;
}
