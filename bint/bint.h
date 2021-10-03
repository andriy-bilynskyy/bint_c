#ifndef BINT_BINT_H_
#define BINT_BINT_H_

#include <stdint.h>
#include <stdbool.h>

/* Define platform base type */
typedef uint32_t    uintb_t;

#define bint_sizeof(a)      (sizeof(a) / sizeof(uintb_t))
#define bint_sizebytes(a)   (a / sizeof(uintb_t) + ((a % sizeof(uintb_t)) ? 1 : 0))

void    bint_set(uintb_t * words, uintb_t words_len, uintb_t value);
void    bint_set_max(uintb_t * words, uintb_t words_len);
uintb_t bint_length(const uintb_t * words, uintb_t words_len);
bool    bint_iszero(const uintb_t * words, uintb_t words_len);
bool    bint_increment(uintb_t * words, uintb_t words_len);
bool    bint_decrement(uintb_t * words, uintb_t words_len);
bool    bint_shift_left(uintb_t * words, uintb_t words_len);
bool    bint_shift_right(uintb_t * words, uintb_t words_len);
bool    bint_assign(uintb_t * a_words, uintb_t a_words_len, const uintb_t * b_words, uintb_t b_words_len);
int     bint_compare(const uintb_t * a_words, uintb_t a_words_len, const uintb_t * b_words, uintb_t b_words_len);

#endif
