#include "expanded_key.h"

#include <algorithm>


namespace aes {
    namespace internal {
        expanded_key::expanded_key(aes128_key key) noexcept
                : key_wsize_{KEY128_WSIZE}, number_of_keys_{AES128_ROUNDS_NUMBER + 1} {
            expand_key(key);
        }

        expanded_key::expanded_key(aes192_key key) noexcept
                : key_wsize_{KEY192_WSIZE}, number_of_keys_{AES192_ROUNDS_NUMBER + 1} {
            expand_key(key);
        }

        expanded_key::expanded_key(aes256_key key) noexcept
                : key_wsize_{KEY256_WSIZE}, number_of_keys_{AES256_ROUNDS_NUMBER + 1} {
            expand_key(key);
        }

        round_key expanded_key::operator[](size_t key_idx) const noexcept {
            return {expanded_key_ + key_idx * BLOCK_SIZE, BLOCK_SIZE};
        }

        void expanded_key::expand_key(gsl::span<const uint8_t> key) noexcept {
            std::copy(key.begin(), key.end(), expanded_key_);

            uint8_t rcon{0x01};
            for (size_t i = key_wsize_; i < number_of_keys_ * internal::BLOCK_WSIZE; ++i) {
                word ith_word = get_word(i);
                copy(ith_word, get_word(i - 1));

                if (i % key_wsize_ == 0) {
                    rot_word(ith_word);
                    sub_word(ith_word);
                    ith_word[0] ^= rcon;
                    rcon = xtime(rcon);
                } else if (key_wsize_ > 6 && i % key_wsize_ == 4) {
                    sub_word(ith_word);
                }
                word_xor(ith_word, get_word(i - key_wsize_));
            }
        }

        word expanded_key::get_word(size_t i) noexcept {
            return {expanded_key_ + i * internal::WORD_SIZE, internal::WORD_SIZE};
        }
    }
}
