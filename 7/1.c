#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct {
    size_t bid, type;
    char cards[5];
} hand;

typedef struct {
    size_t cap;
    size_t count;
    hand *arr;
} hand_array;

int compare_cards(hand *h1, hand *h2) {
    if (h1->type != h2->type)
        return h1->type > h2->type;

    for (int j = 0; j < 5; j ++)
        if (h1->cards[j] != h2->cards[j])
            return h1->cards[j] > h2->cards[j];

    return 0;
}

void append_hand_sorted(hand_array *a, hand h) {
    if (a->count == a->cap) {
        if (a->arr) {
            a->cap *= 2;
            a->arr = realloc(a->arr, a->cap * sizeof(*a->arr));
        } else {
            a->cap = 8;
            a->count = 1;
            a->arr = calloc(a->cap, sizeof(*a->arr));
        }
    }

    int i = a->count - 1;
    a->count ++;

    for (; !compare_cards(&h, a->arr + i); i --)
        a->arr[i + 1] = a->arr[i];
    a->arr[i + 1] = h;
}

int get_type(int *hand) {
    int inc = 1;
    int type = 1;
    
    for (int i = 0; i < 5; i ++) {
        if (hand[i] == hand[i - 1]) {
            type += inc;
            inc ++;
        } else {
            inc = 1;
        }
    }

    return type;
}

int main() {
    size_t n = 1024;
    char linebuffer[1024];
    char *lineptr = linebuffer;
    FILE *fp = fopen("input", "rb");
    hand_array hands = {0};

    while (getline(&lineptr, &n, fp) != -1) {
        hand h = {0};
        int buf[6] = {-1, 0, 0, 0, 0};
        int *sorted = buf + 1; // index 0 is dummy

        for (int i = 0; i < 5; i ++) {
            char card = lineptr[i];
            switch(card) {
                case 'A': card = '9' + 5; break;
                case 'K': card = '9' + 4; break;
                case 'Q': card = '9' + 3; break;
                case 'J': card = '9' + 2; break;
                case 'T': card = '9' + 1; break;
            }

            card -= '0';
            h.cards[i] = card;

            int j = i - 1;
            for (; card < sorted[j]; j --)
                sorted[j + 1] = sorted[j];
            sorted[j + 1] = card;
        }

        h.type = get_type(sorted);
        h.bid = atoi(lineptr + 6);
        append_hand_sorted(&hands, h);
    }

    size_t winnings = 0;
    for (size_t i = 1; i < hands.count; i ++)
        winnings += i * hands.arr[i].bid;

    printf("%ld\n", winnings);

    fclose(fp);
}
