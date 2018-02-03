#include <utils.h>
#include <defs.h>

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

    std::array <uint8_t, internal::WORD_SIZE> get_rcon(size_t i) {
        std::array <uint8_t, internal::WORD_SIZE> tmp{0};
        uint8_t x = 0x01;
        for (size_t j = 0; j < i - 1; ++j) {
            x = xtime(x);
        }
        tmp[0] = x;
        return tmp;
    }

    uint8_t xtime(uint8_t x) {
        if (x & 0x80)
            return (x << 1) ^ 0x1B;
        else
            return x << 1;
    }
}
