#ifndef CRYPTOAES_UTILS_H
#define CRYPTOAES_UTILS_H

#include <defs.h>

#include <algorithm>

namespace aes {

    void subword(word w);
    void rotword(word w);
    void word_xor(word dst, const_word src);
    uint8_t xtime(uint8_t x);

    inline void copy(word dst, const_word src) {
        std::copy(src.begin(), src.end(), dst.begin());
    }
}

#endif //CRYPTOAES_UTILS_H
