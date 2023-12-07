#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    size_t start, length;
    int mapped;
} range;

typedef struct {
    size_t count, cap;
    range *arr;
} range_array;

int inrange(size_t v, range r) {
    return v >= r.start && v <= r.start + r.length;
}

void arr_remove(range_array *a, int i) {
    a->count --;
    for (int j = i; j < a->count; j ++)
        a->arr[j] = a->arr[j + 1];
}

void arr_append(range_array *a, range r) {
    if (a->count == a->cap) {
        a->cap *= 2;
        a->arr = realloc(a->arr, a->cap * sizeof(range));
    }
    a->arr[a->count ++] = r;
}

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

    range_array ranges;
    ranges.cap = 32;
    ranges.arr = calloc(ranges.cap, sizeof(range));
    ranges.count = seedcount / 2; 

    for (int i = 0; i < seedcount / 2; i ++) {
        ranges.arr[i].start = seeds[i * 2];
        ranges.arr[i].length = seeds[i * 2 + 1];
    }

    while ((linelen = getline(&lineptr, &n, fp)) != -1) {
        linelen = getline(&lineptr, &n, fp);

        for (int i = 0; i < ranges.count; i ++)
            ranges.arr[i].mapped = 0;
    
        while(linelen != -1 && isdigit(lineptr[0])) {
            char *charptr = lineptr;
            size_t data[3];
            lineptr[linelen - 1] = '|';
            readnums(data, &charptr, '|');
    
            size_t dst_start = data[0];
            size_t src_start = data[1];
            size_t length = data[2];
            size_t src_end = src_start + length;
            range given_range = {src_start, length, 0};

            for (size_t i = 0; i < ranges.count; i ++) {
                if (ranges.arr[i].mapped) continue;
                range ur = ranges.arr[i];
                int start_in_range = inrange(src_start, ur);
                int end_in_range = inrange(src_end, ur);
                if (inrange(ur.start, given_range) && inrange(ur.start + ur.length, given_range)) {
                    ranges.arr[i].start = dst_start + ur.start - src_start;
                    ranges.arr[i].mapped = 1;
                } else if (start_in_range && end_in_range) {
                    range r1 = { ur.start, src_start - ur.start, 0 };
                    range r2 = { dst_start, length, 1 };
                    range r3 = { src_end, ur.start + ur.length - src_end, 0 };
                    arr_remove(&ranges, i);
                    if (r1.length) arr_append(&ranges, r1);
                    if (r2.length) arr_append(&ranges, r2);
                    if (r3.length) arr_append(&ranges, r3);
                } else if (start_in_range) {
                    range r1 = { ur.start, src_start - ur.start, 0 };
                    range r2 = { dst_start, ur.start + ur.length - src_start, 1 };
                    arr_remove(&ranges, i);
                    if (r1.length) arr_append(&ranges, r1);
                    if (r2.length) arr_append(&ranges, r2);
                } else if (end_in_range) {
                    range r1 = { ur.start - src_start + dst_start, length + src_start - ur.start, 1 };
                    range r2 = { ur.start + r1.length, ur.length - r1.length, 0 };
                    arr_remove(&ranges, i);
                    if (r1.length) arr_append(&ranges, r1);
                    if (r2.length) arr_append(&ranges, r2);
                }
            }

            linelen = getline(&lineptr, &n, fp);
        }
    }

    size_t min = ranges.arr[0].start;
    for (int i = 1; i < ranges.count; i ++) {
        if (min > ranges.arr[i].start) {
            min = ranges.arr[i].start;
        }
    }

    printf("%ld\n", min);

    fclose(fp);
}
