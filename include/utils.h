#ifndef CRYPTOAES_UTILS_H
#define CRYPTOAES_UTILS_H

#include "defs.h"

#include <algorithm>


namespace aes {
    namespace internal {
        void sub_word(word w) noexcept;
        void rot_word(word w) noexcept;
        void word_xor(word dst, const_word src) noexcept;
        uint8_t xtime(uint8_t x) noexcept;
        uint8_t xtime3(uint8_t p) noexcept;

        inline void copy(word dst, const_word src) noexcept {
            std::copy(src.begin(), src.end(), dst.begin());
        }

        void sub_bytes(block b) noexcept;
        void shiftrows(block b) noexcept;
        void mixcolumns(block b) noexcept;
        void block_xor(block dst, const_block src) noexcept;
    }
}

#endif //CRYPTOAES_UTILS_H
