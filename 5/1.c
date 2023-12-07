#include <stdio.h>
#include <ctype.h>

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
    char linebuffer[1024];
    char *lineptr = linebuffer;
    FILE *fp = fopen("input", "rb");

    int linelen = getline(&lineptr, &n, fp);
    lineptr[linelen - 1] = '|';
    char *charptr = lineptr;

    size_t seeds[100];
    int seedcount = readnums(seeds, &charptr, '|');
    getline(&lineptr, &n, fp);

    while ((linelen = getline(&lineptr, &n, fp)) != -1) {
        linelen = getline(&lineptr, &n, fp);
        char mapped[100] = {0};

        while(linelen != -1 && isdigit(lineptr[0])) {
            char *charptr = lineptr;
            size_t data[3];
            lineptr[linelen - 1] = '|';
            readnums(data, &charptr, '|');

            size_t dst_start = data[0];
            size_t src_start = data[1];
            size_t range = data[2];

            for (int i = 0; i < seedcount; i ++) {
                if (mapped[i]) continue;
                size_t src = seeds[i];
                if (src >= src_start && src < src_start + range) {
                    seeds[i] = src - src_start + dst_start;
                    mapped[i] = 1;
                }
            }
            linelen = getline(&lineptr, &n, fp);
        }
    }

    size_t min = seeds[0];
    for (int i = 1; i < seedcount; i ++) {
        if (seeds[i] < min) {
            min = seeds[i];
        }
    }

    printf("%ld\n", min);
    fclose(fp);
}
