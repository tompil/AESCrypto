#ifndef CRYPTOAES_AES_CIPHER_H
#define CRYPTOAES_AES_CIPHER_H

#include "expanded_key.h"


namespace aes {
    class aes_cipherer {
    public:
        explicit aes_cipherer(aes128_key key) noexcept : ekey_{key} {}

        explicit aes_cipherer(aes192_key key) noexcept : ekey_{key} {}

        explicit aes_cipherer(aes256_key key) noexcept : ekey_{key} {}
        void cipher(const_block in, block out) const;

    private:
        internal::expanded_key ekey_;
    };
}

#endif //CRYPTOAES_AES_CIPHER_H
