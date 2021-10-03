#include "bint_test.h"
#include "bint.h"
#include <stdio.h>

#pragma GCC diagnostic ignored "-Wunused-function"
static void bint_print(const char* comment, uintb_t * words, uintb_t words_len) {

    printf("%s [%u]:", comment, (unsigned int)(words_len * sizeof(uintb_t)));
    for(size_t i = words_len * sizeof(uintb_t); i > 0; i--) {
        printf(" %02x", ((uint8_t*) words)[i - 1]);
    }
    printf("\n");
}

void bint_test_run(void) {

    printf("bint test start\n");

    uintb_t a[bint_sizebytes(9)];

    bint_set(a, bint_sizeof(a), 0);
    bint_print("set a:", a, bint_sizeof(a));

    printf("actual length of a: %u\n", bint_length(a, bint_sizeof(a)));

    printf("is zero a: %u\n", bint_iszero(a, bint_sizeof(a)));

    if(bint_increment(a, bint_sizeof(a))) {
        printf("overflow\n");
    }
    bint_print("increment a:", a, bint_sizeof(a));

    if(bint_decrement(a, bint_sizeof(a))) {
        printf("overflow\n");
    }
    bint_print("decrement a:", a, bint_sizeof(a));

    if(bint_decrement(a, bint_sizeof(a))) {
        printf("overflow\n");
    }
    bint_print("decrement a:", a, bint_sizeof(a));

    if(bint_increment(a, bint_sizeof(a))) {
        printf("overflow\n");
    }
    bint_print("increment a:", a, bint_sizeof(a));

    bint_set_max(a, bint_sizeof(a));
    bint_print("set max a:", a, bint_sizeof(a));

    printf("actual length of a: %u\n", bint_length(a, bint_sizeof(a)));

    printf("msb: %u\n", bint_shift_left(a, bint_sizeof(a)));
    bint_print("shift left a:", a, bint_sizeof(a));

    printf("msb: %u\n", bint_shift_left(a, bint_sizeof(a)));
    bint_print("shift left a:", a, bint_sizeof(a));

    printf("lsb: %u\n", bint_shift_right(a, bint_sizeof(a)));
    bint_print("shift right a:", a, bint_sizeof(a));

    printf("lsb: %u\n", bint_shift_right(a, bint_sizeof(a)));
    bint_print("shift right a:", a, bint_sizeof(a));

    printf("lsb: %u\n", bint_shift_right(a, bint_sizeof(a)));
    bint_print("shift right a:", a, bint_sizeof(a));

    uintb_t b[5] = {1, 2, 3, 4, 5};

    if(bint_assign(a, bint_sizeof(a), b, bint_sizeof(b))) {
        printf("overflow\n");
    }
    bint_print("assign a:", a, bint_sizeof(a));

    printf("compare: %d\n", bint_compare(a, bint_sizeof(a), b, bint_sizeof(b)));

    printf("bint test finish\n");
}
