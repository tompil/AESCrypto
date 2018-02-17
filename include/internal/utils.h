#ifndef CRYPTOAES_UTILS_H
#define CRYPTOAES_UTILS_H

#include "internal/internal_defs.h"
#include "../defs.h"


namespace aes {
    namespace internal {
        void sub_word(word w) noexcept;
        void rot_word(word w) noexcept;
        void word_xor(word dst, const_word src) noexcept;
        uint8_t xtime(uint8_t x) noexcept;

        inline void copy(word dst, const_word src) noexcept {
            std::copy(src.begin(), src.end(), dst.begin());
        }

        void sub_bytes(block b) noexcept;

        void shift_rows(block b) noexcept;

        void mix_columns(block b) noexcept;
        void block_xor(block dst, const_block src) noexcept;

        void inverse_sub_bytes(block b) noexcept;

        void inverse_shift_rows(block b) noexcept;

        void inverse_mix_columns(block b) noexcept;
    }
}

#endif //CRYPTOAES_UTILS_H
