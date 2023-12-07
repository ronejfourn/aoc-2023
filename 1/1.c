#include <stdio.h>
#include <stdlib.h>

int main() {
    char *line = NULL;
    size_t size = 0;
    ssize_t len = 0;
    int sum = 0;

    FILE *fp = fopen("input", "rb");
    while((len = getline(&line, &size, fp)) != -1) {
        char *p = line;
        for (; !(*p >= '0' && *p <= '9'); p ++);

        sum += (*p - '0') * 10;

        p = line + len;
        for (; !(*p >= '0' && *p <= '9'); p --);

        sum += (*p - '0');

        free(line);
        size = 0;
    }
    fclose(fp);
    printf("%d\n", sum);
}
