#ifndef CRYPTOAES_KEY_EXPANDER_H
#define CRYPTOAES_KEY_EXPANDER_H

#include <defs.h>
#include <utils.h>

#include <gsl/span>

#include <cstdint>
#include <cstddef>


namespace aes {
    namespace internal {

        class expanded_key {
        public:
            explicit expanded_key(aes128_key key);
            explicit expanded_key(aes192_key key);
            explicit expanded_key(aes256_key key);
            round_key get_round_key(size_t key_idx) const;

        private:
            static constexpr size_t AES128_ROUNDS_NUMBER = 10;
            static constexpr size_t AES192_ROUNDS_NUMBER = 12;
            static constexpr size_t AES256_ROUNDS_NUMBER = 14;
            static constexpr size_t MAX_EXPANDED_KEY_LEN = (AES256_ROUNDS_NUMBER + 1) * BLOCK_SIZE;

            uint8_t expanded_key_[MAX_EXPANDED_KEY_LEN];
            const uint8_t number_of_rounds_;
            const uint8_t key_wsize_;

            void expand_key(gsl::span<const uint8_t> key);
            word get_word(size_t i);
        };

    }
}

#endif //CRYPTOAES_KEY_EXPANDER_H
