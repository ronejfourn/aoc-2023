#include <stdio.h>
#include <ctype.h>
#include <math.h>

size_t getnum(char *p, char d) {
    size_t num = 0;
    for (; *p != d; p++)
        if (isdigit(*p))
            num = num * 10 + *p - '0';

    return num;
}

int main() {
    size_t n = 1024;
    int linelen;
    char linebuffer[1024];
    char *lineptr = linebuffer;
    FILE *fp = fopen("input", "rb");

    linelen = getline(&lineptr, &n, fp);
    lineptr[linelen - 1] = '|';
    size_t T = getnum(lineptr, '|');

    linelen = getline(&lineptr, &n, fp);
    lineptr[linelen - 1] = '|';
    size_t D = getnum(lineptr, '|');

    double disc = sqrt(T * T - 4 * D);
    double a = floor((T - disc) / 2.0 + 1);
    double b = ceil((T + disc) / 2.0 - 1);
    size_t ways = b - a + 1;

    printf("%ld\n", ways);

    fclose(fp);
}
