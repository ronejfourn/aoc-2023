#include <stdio.h>
#include <stdlib.h>

int main() {
    int sumid = 0;
    int bagcontains[] = { 12 /*red*/, 14 /*blue*/, 13 /*green*/ };
    char buffer[1024] = {};
    char *lineptr = buffer;
    size_t n = 1024;

    FILE *fp = fopen("input", "rb");
    int len;
    int id = 1;

    while ((len = getline(&lineptr, &n, fp)) != -1) {
        int possible = 1;
        char *line = lineptr;
        line[len - 1] = ';';
        line[len + 0] = 0;
        line[len + 1] = 0;
        while (*line != ':') line ++;
        line += 2;

        while (*line){
            int count = atoi(line);
            while (*line >= '0' && *line <= '9') line ++;
            line ++;
            char *color = line;
            while (*line != ';' && *line != ',') line ++;
            int len = line - color;
            line += 2;

            // exploit nature of data or something idk ¯\_(ツ)_/¯
            if (count > bagcontains[len - 3]) {
                possible = 0;
                break;
            }
        }

        if (possible) sumid += id;
        id += 1;
    }

    fclose(fp);
    printf("%d\n", sumid);
}
