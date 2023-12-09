#include <stdio.h>
#include <ctype.h>

int solve(int *nums, int count) {
    int done = 1;
    int res = nums[0];
    for (int i = 1; i < count; i ++) {
        nums [i - 1] = nums[i] - nums[i - 1];
        done &= nums[i - 1] == 0;
    }

    return done ? res : res - solve(nums, count - 1);
}

int readnums(int *nums, char **ptr, char delim) {
    int count = 0;
    int sign = 1;
    char *line = *ptr;
    while (*line != delim) {
        if (*line == '-') {
            sign = -1;
            line ++;
        } else if (isdigit(*line)) {
            nums[count] = 0;
            while (isdigit(*line)) {
                nums[count] *= 10;
                nums[count] += *line - '0';
                line++;
            }
            nums[count ++] *= sign;
            sign = 1;
        } else {
            line ++;
        }
    }

    *ptr = line + 1;
    return count;
}

int main() {
    size_t n = 1024;
    char linebuffer[1024];
    char *lineptr = linebuffer;
    FILE *fp = fopen("input", "rb");
    int linelen = 0;

    int total = 0;
    while ((linelen = getline(&lineptr, &n, fp)) != -1) {
        char *charptr = lineptr;
        charptr[linelen - 1] = '|';

        int nums[1000] = {0};
        int count = readnums(nums, &charptr, '|');

        total += solve(nums, count);
    }

    printf("%d\n", total);

    fclose(fp);
}
