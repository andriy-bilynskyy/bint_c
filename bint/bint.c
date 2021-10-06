#include "bint.h"

void bint_set(uintb_t * words, uintb_t words_len, uintb_t value) {

    if(words && words_len) {
        uintb_t * const words_fin = words + words_len;
        *(words++) = value;
        for(; words < words_fin; ++words) {
            *words = 0;
        }
    }
}

void bint_set_max(uintb_t * words, uintb_t words_len) {

    if(words) {
        uintb_t * const words_fin = words + words_len;
        for(; words < words_fin; ++words) {
            *words = (uintb_t)-1;
        }
    }
}

uintb_t bint_length(const uintb_t * words, uintb_t words_len) {

    if(words) {
        const uintb_t * words_last = words + words_len - 1;
        for(; words_last >= words && !*words_last; --words_last);
        words_len = words_last - words + 1;
    }
    return words_len;
}

bool bint_iszero(const uintb_t * words, uintb_t words_len) {

    bool result = true;

    if(words) {
        const uintb_t * const words_fin = words + words_len;
        for(; words < words_fin && !words; ++words);
        result = !*words;
    }

    return result;
}

bool bint_increment(uintb_t * words, uintb_t words_len) {

    uintb_t i = 0;
    if(words) {
        for(; i < words_len; ++i) {
            if(++*(words++) != 0) {
                break;
            }
        }
    }
    return i == words_len;
}

bool bint_decrement(uintb_t * words, uintb_t words_len) {

    uintb_t i = 0;
    if(words) {
        for(; i < words_len; ++i) {
            if(--*(words++) != (uintb_t)-1) {
                break;
            }
        }
    }
    return i == words_len;
}

bool bint_shift_left(uintb_t * words, uintb_t words_len) {

    bool msb = 0;
    if(words) {
        uintb_t * words_fin = words + words_len;
        uintb_t * words_last = words_fin - 1;
        for(; words_last >= words && !*words_last; --words_last);
        for(; words <= words_last;) {
            bool tmp = *words & ~((uintb_t)-1 >> 1);
            *words <<= 1;
            *(words++) |= msb;
            msb = tmp;
        }
        if(words < words_fin) {
            *words = msb;
            msb = 0;
        }
    }
    return msb;
}

bool bint_shift_right(uintb_t * words, uintb_t words_len) {

    bool lsb = false;
    if(words) {
        uintb_t * words_last = words + words_len - 1;
        for(; words_last >= words && !*words_last; --words_last);
        for(; words <= words_last;) {
            bool tmp = *words_last & 1;
            *words_last >>= 1;
            *(words_last--) |= (uintb_t)lsb << (sizeof(uintb_t) * 8 - 1);
            lsb = tmp;
        }
    }
    return lsb;
}

bool bint_assign(uintb_t * a_words, uintb_t a_words_len, const uintb_t * b_words, uintb_t b_words_len) {

    if(a_words && b_words) {
        const uintb_t * b_words_last = b_words + b_words_len - 1;
        for(; b_words_last >= b_words && !*b_words_last; --b_words_last);
        b_words_len = b_words_last - b_words + 1;
        uintb_t cpy_length = a_words_len < b_words_len ? a_words_len : b_words_len;
        for(uintb_t i = 0; i < cpy_length; ++i) {
            *(a_words++) = *(b_words++);
        }
        for(uintb_t i = cpy_length; i < a_words_len; ++i) {
            *(a_words++) = 0;
        }
    }
    return a_words_len < b_words_len;
}

int bint_compare(const uintb_t * a_words, uintb_t a_words_len, const uintb_t * b_words, uintb_t b_words_len) {

    int result = 0;
    if(a_words && b_words) {
        const uintb_t * a_words_last = a_words + a_words_len - 1;
        for(; a_words_last >= a_words && !*a_words_last; --a_words_last);
        a_words_len = a_words_last - a_words + 1;
        const uintb_t * b_words_last = b_words + b_words_len - 1;
        for(; b_words_last >= b_words && !*b_words_last; --b_words_last);
        b_words_len = b_words_last - b_words + 1;
        if(a_words_len < b_words_len) {
            result = -1;
        } else if(a_words_len > b_words_len) {
            result = 1;
        } else {
            for(; !result && a_words_last >= a_words; a_words_last--, b_words_last--) {
                if(*a_words_last < *b_words_last) {
                    result = -1;
                } else if(*a_words_last > *b_words_last) {
                    result = 1;
                }
            }
        }
    }
    return result;
}
