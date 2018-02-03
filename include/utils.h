#ifndef CRYPTOAES_UTILS_H
#define CRYPTOAES_UTILS_H

#include <defs.h>

namespace aes {
    void subword(word w);
    void rotword(word w);
    void word_xor(word dst, const_word src);
    std::array <uint8_t, internal::WORD_SIZE> get_rcon(size_t i);
    uint8_t xtime(uint8_t x);
}
#endif //CRYPTOAES_UTILS_H
