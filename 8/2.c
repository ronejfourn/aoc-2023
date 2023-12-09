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
    size_t *pts = calloc(26 * 26, sizeof(size_t));
    size_t ptscount = 0;

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
        right = right * 26 + *(charptr++) - 'A'; right = right * 26 + *(charptr++) - 'A';
        map[start] = (node){left, right};

        if (start % 26 == 0) {
            pts[ptscount ++] = start;
        }
    }

    size_t min = pts[0];
    for (size_t i = 0; i < ptscount; i ++) {
        size_t steps = 0;
        
        for (size_t at = pts[i]; at % 26 != 25; steps++) {
            char ins = insptr[steps % inslength];
            at = ins == 'L' ? map[at].L : map[at].R;
        }

        pts[i] = steps;
        min = steps < min ? steps : min;
    }

    unsigned long long lcm = pts[0];
    for (size_t i = 1; i < ptscount; i ++) {
        size_t hcf = pts[i], a = pts[i];
        for (; a % hcf != 0 || lcm % hcf != 0; hcf --);
        lcm = lcm * a / hcf;
    }

    printf("%lld\n", lcm);

    free(map);
    fclose(fp);
}
