#include "internal/utils.h"


namespace aes {
    namespace internal {
        void sub_word(word w) noexcept {
            for (uint8_t &i : w)
                i = internal::SBOX[i];
        }

        void rot_word(word w) noexcept {
            uint8_t tmp{w[0]};
            std::copy(w.begin() + 1, w.end(), w.begin());
            w[3] = tmp;
        }

        void word_xor(word dst, const_word src) noexcept {
            for (size_t i = 0; i < dst.size(); ++i)
                dst[i] ^= src[i];
        }

        uint8_t xtime(uint8_t x) noexcept {
            if (x & 0x80)
                return (x << 1) ^ 0x1B;
            else
                return x << 1;
        }

        void sub_bytes(block b) noexcept {
            for (uint8_t &i : b)
                i = internal::SBOX[i];
        }

        void shift_rows(block b) noexcept {
            uint8_t tmp[6]{b[1], b[2], b[3], b[6], b[7], b[11]};
            b[1] = b[5]; b[5] = b[9]; b[9] = b[13]; b[13] = tmp[0];
            b[2] = b[10]; b[6] = b[14]; b[10] = tmp[1]; b[14] = tmp[3];
            b[3] = b[15]; b[7] = tmp[2]; b[11] = tmp[4], b[15] = tmp[5];
        }

        uint8_t mult(uint8_t a, uint8_t b) {
            uint8_t tmp{0};
            uint8_t s = 0x01;

            do {
                if (b & s) tmp ^= a;
                a = xtime(a);
                s <<= 1;
            } while (s < 0x80);

            return tmp;
        }

        void mix_columns(block b) noexcept {
            std::array<uint8_t, BLOCK_SIZE> tmp{};

            for (size_t c = 0; c < BLOCK_WSIZE; ++c) {
                const_word scol{b.data() + c * WORD_SIZE, WORD_SIZE};
                word dcol{tmp.data() + c * WORD_SIZE, WORD_SIZE};

                dcol[0] = xtime(scol[0]) ^ mult(scol[1], 3) ^ scol[2] ^ scol[3];
                dcol[1] = scol[0] ^ xtime(scol[1]) ^ mult(scol[2], 3) ^ scol[3];
                dcol[2] = scol[0] ^ scol[1] ^ xtime(scol[2]) ^ mult(scol[3], 3);
                dcol[3] = mult(scol[0], 3) ^ scol[1] ^ scol[2] ^ xtime(scol[3]);
            }

            std::copy(tmp.begin(), tmp.end(), b.begin());
        }

        void block_xor(block dst, const_block src) noexcept {
            for (size_t i = 0; i < dst.size(); ++i)
                dst[i] ^= src[i];
        }

        void inverse_sub_bytes(block b) noexcept {
            for (uint8_t &i : b)
                i = internal::INVERSE_SBOX[i];
        }

        void inverse_shift_rows(block b) noexcept {
            uint8_t tmp[4]{b[13], b[10], b[14], b[3]};
            b[13] = b[9];
            b[9] = b[5], b[5] = b[1], b[1] = tmp[0];
            b[10] = b[2];
            b[14] = b[6];
            b[2] = tmp[1];
            b[6] = tmp[2];
            b[3] = b[7];
            b[7] = b[11];
            b[11] = b[15];
            b[15] = tmp[3];
        }

        void inverse_mix_columns(block b) noexcept {
            std::array<uint8_t, BLOCK_SIZE> tmp{};

            for (size_t c = 0; c < BLOCK_WSIZE; ++c) {
                const_word scol{b.data() + c * WORD_SIZE, WORD_SIZE};
                word dcol{tmp.data() + c * WORD_SIZE, WORD_SIZE};

                dcol[0] = mult(scol[0], 0x0E) ^ mult(scol[1], 0x0B) ^ mult(scol[2], 0x0D) ^ mult(scol[3], 0x09);
                dcol[1] = mult(scol[0], 0x09) ^ mult(scol[1], 0x0E) ^ mult(scol[2], 0x0B) ^ mult(scol[3], 0x0D);
                dcol[2] = mult(scol[0], 0x0D) ^ mult(scol[1], 0x09) ^ mult(scol[2], 0x0E) ^ mult(scol[3], 0x0B);
                dcol[3] = mult(scol[0], 0x0B) ^ mult(scol[1], 0x0D) ^ mult(scol[2], 0x09) ^ mult(scol[3], 0x0E);
            }

            std::copy(tmp.begin(), tmp.end(), b.begin());
        }
    }
}
