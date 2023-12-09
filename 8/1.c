#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    size_t L, R;
} node;

int main() {
    size_t n = 1024;
    char linebuffer[1024];
    char *lineptr = linebuffer;
    FILE *fp = fopen("input", "rb");

    char insbuffer[1024];
    char *insptr = insbuffer;
    size_t inslength = getline(&insptr, &n, fp);
    getline(&lineptr, &n, fp);

    inslength -= insptr[inslength - 1] == '\n';
    inslength -= insptr[inslength - 1] == '\r';

    node *map = calloc(26 * 26 * 26, sizeof(node));

    while (getline(&lineptr, &n, fp) != -1) {
        char *charptr = lineptr;
        size_t start = 0, left = 0, right = 0;

        start = start * 26 + *(charptr++) - 'A';
        start = start * 26 + *(charptr++) - 'A';
        start = start * 26 + *(charptr++) - 'A';
        charptr += 4;

        left = left * 26 + *(charptr++) - 'A';
        left = left * 26 + *(charptr++) - 'A';
        left = left * 26 + *(charptr++) - 'A';
        charptr += 2;

        right = right * 26 + *(charptr++) - 'A';
        right = right * 26 + *(charptr++) - 'A';
        right = right * 26 + *(charptr++) - 'A';

        map[start] = (node){left, right};
    }

    size_t steps = 0;
    size_t end = 25 * 26 * 26 + 25 * 26 + 25; // ZZZ

    for (size_t at = 0; at != end; steps ++) {
        char ins = insptr[steps % inslength];
        at = ins == 'L' ? map[at].L : map[at].R;
    }

    printf("%ld\n", steps);

    free(map);
    fclose(fp);
}
