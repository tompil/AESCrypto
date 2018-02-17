#ifndef CRYPTOAES_AES_DECIPHERER_H
#define CRYPTOAES_AES_DECIPHERER_H

#include "internal/expanded_key.h"


namespace aes {
    class aes_decipherer {
    public:
        explicit aes_decipherer(aes128_key key) noexcept : ekey_{key} {}

        explicit aes_decipherer(aes192_key key) noexcept : ekey_{key} {}

        explicit aes_decipherer(aes256_key key) noexcept : ekey_{key} {}

        void decipher(const_block in, block out) const;

    private:
        internal::expanded_key ekey_;
    };
}

#endif //CRYPTOAES_AES_DECIPHERER_H
