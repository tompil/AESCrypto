#ifndef CRYPTOAES_AES_DECIPHERER_H
#define CRYPTOAES_AES_DECIPHERER_H

#include "defs.h"


namespace aes {
    class aes_decipherer {
    public:
        explicit aes_decipherer(aes128_key key) noexcept {}
        explicit aes_decipherer(aes192_key key) noexcept {}
        explicit aes_decipherer(aes256_key key) noexcept {}
        void decipher(const_block in, block out) const {}
    };
}

#endif //CRYPTOAES_AES_DECIPHERER_H
