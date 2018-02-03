#include <utils.h>


namespace aes {

    void subword(word w) {
        for (uint8_t &i : w)
            i = internal::SBOX[i];
    }

    void rotword(aes::word w) {
        uint8_t tmp = w[0];
        std::copy(w.begin() + 1, w.end(), w.begin());
        w[3] = tmp;
    }

    void word_xor(aes::word dst, aes::const_word src) {
        for (size_t i = 0; i < internal::WORD_SIZE; ++i)
            dst[i] ^= src[i];
    }

    uint8_t xtime(uint8_t x) {
        if (x & 0x80)
            return (x << 1) ^ 0x1B;
        else
            return x << 1;
    }

}
