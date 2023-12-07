#include <stdio.h>
#include <ctype.h>
#include <math.h>

int readnums(size_t *nums, char **ptr, char delim) {
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
    int linelen;
    char linebuffer[1024];
    char *lineptr = linebuffer, *charptr;
    FILE *fp = fopen("input", "rb");

    size_t times[100], distances[100];

    linelen = getline(&lineptr, &n, fp);
    lineptr[linelen - 1] = '|';
    charptr = lineptr;
    readnums(times, &charptr, '|');

    linelen = getline(&lineptr, &n, fp);
    lineptr[linelen - 1] = '|';
    charptr = lineptr;
    int count = readnums(distances, &charptr, '|');

    int product = 1;

    for (int i = 0; i < count; i ++) {
        double disc = sqrt(times[i] * times[i] - 4 * distances[i]);
        double a = floor((times[i] - disc) / 2.0 + 1);
        double b = ceil((times[i] + disc) / 2.0 - 1);
        int ways = b - a + 1;
        product *= ways;
    }

    printf("%d\n", product);

    fclose(fp);
}
