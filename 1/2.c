#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct { 
    uint64_t value;
    uint64_t mask; 
} map[9];

void setupmap(map m) {
    char digits[9][8] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    for (int i = 0; i < 9; i ++) {
        char mask[8] = {0};
        for (char *p = digits[i]; *p; p ++)
            mask[p - digits[i]] = 0xff;

        m[i].value = *(uint64_t *)digits[i];
        m[i].mask = *(uint64_t *)mask;
    }
}

int getnum(char *p, map m) {
    if (*p >= '0' && *p <= '9')
        return *p - '0';

    uint64_t n = *(uint64_t *)p;
    for (int j = 0; j < 9; j ++)
        if ((n & m[j].mask) == m[j].value)
            return j + 1;

    return 0;
}

int main() {
    char buf[1024];
    char *line = buf;
    size_t size = 1024;
    ssize_t len = 0;
    int sum = 0;
    map m;
    setupmap(m);

    FILE *fp = fopen("input", "rb");
    while((len = getline(&line, &size, fp)) != -1) {
        char *p = line;
        int n = 0;
    
        for (; !n; p ++)
            n = getnum(p, m);

        sum += n * 10;

        for (p = p - 1; *p; p ++) {
            int t = getnum(p, m);
            n = t ? t : n;
        }

        sum += n;

        size = 1024;
        memset(line, 0, 1024);
    }
    fclose(fp);
    printf("%d\n", sum);
}
