#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isnewline(char c) { return c == '\r' || c == '\n'; }
int issymbol(char c) { return !(isdigit(c) || isnewline(c) || c == '.' || c == 0); }

void leftof(char *c, int *nums, int *count) {
    if (isdigit(*(c - 1))) {
        char *p = c - 1;
        while (isdigit(*p)) p --;
        nums[(*count)++] = atoi(p + 1);
    }
}

void rightof(char *c, int *nums, int *count) {
    if (isdigit(*(c + 1)))
        nums[(*count)++] = atoi(c + 1);
}

int main() { FILE *fp = fopen("input", "rb");
    fseek(fp, 0, SEEK_END);
    int fs = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    int columns = 0;
    char a = 0;
    while (!isnewline(a)) {
        a = fgetc(fp);
        columns ++; 
    }
    columns += fgetc(fp) == '\n';
    fseek(fp, 0, SEEK_SET);

    char *buf = calloc(fs + 2 * columns + 2, 1);
    char *ptr = buf + columns + 1;
    fread(ptr, fs, 1, fp);
    fclose(fp);

    int sum = 0;
    while (*ptr) {
        if (*(ptr ++) != '*') continue;

        char *c = ptr - 1;
        char *t = c - columns;
        char *b = c + columns;
        int nums[6] = {0};
        int count = 0;

        leftof(c, nums, &count);
        rightof(c, nums, &count);

        if (isdigit(*t)) {
            leftof(t + 1, nums, &count);
        } else {
            leftof(t, nums, &count);
            rightof(t, nums, &count);
        }

        if (isdigit(*b)) {
            leftof(b + 1, nums, &count);
        } else {
            leftof(b, nums, &count);
            rightof(b, nums, &count);
        }

        if (count == 2) sum += nums[0] * nums[1];
    }

    printf("%d\n", sum);
    return 0;
}
