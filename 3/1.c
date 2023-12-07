#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int isnewline(char c) { return c == '\r' || c == '\n'; }
int issymbol(char c) { return !(isdigit(c) || isnewline(c) || c == '.' || c == 0); }

int main() {
    FILE *fp = fopen("input", "rb");
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
        char c = *(ptr ++);
        if (!isdigit(c)) continue;

        char *beg = ptr - 1;
        while (isdigit(*ptr)) ptr ++;
        int shouldadd = issymbol(*(beg - 1)) || issymbol(*ptr);
        int len = ptr - beg + 2;

        if (!shouldadd) {
            char *p = beg - columns - 1;
            for (int i = 0; i < len && !shouldadd; i ++)
                shouldadd = issymbol(p[i]);
        }

        if (!shouldadd) {
            char *p = beg + columns - 1;
            for (int i = 0; i < len && !shouldadd; i ++)
                shouldadd = issymbol(p[i]);
        }

        if (shouldadd) {
            sum += atoi(beg);
        }
    }

    printf("%d\n", sum);
    return 0;
}
