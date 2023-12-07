#include <stdio.h>
#include <stdlib.h>

int main() {
    int sumpower = 0;
    char buffer[1024] = {};
    char *lineptr = buffer;
    size_t n = 1024;

    FILE *fp = fopen("input", "rb");
    int len;

    while ((len = getline(&lineptr, &n, fp)) != -1) {
        int minrequired[] = {0, 0, 0};
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
            if (count > minrequired[len - 3])
                minrequired[len - 3] = count;
        }

        int power = 1;
        for (int i = 0; i < 3; i ++)
            power *= minrequired[i];
        sumpower += power;
    }

    fclose(fp);
    printf("%d\n", sumpower);
}
