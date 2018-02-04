#ifndef CRYPTOAES_AES_CIPHER_H
#define CRYPTOAES_AES_CIPHER_H

#include <defs.h>

namespace aes {

    class aes_cipherer {
    public:
        aes_cipherer(aes128_key key) noexcept {}
        aes_cipherer(aes192_key key) noexcept {}
        aes_cipherer(aes256_key key) noexcept {}

        void cipher(const_block in, block out) {}
    };

}

#endif //CRYPTOAES_AES_CIPHER_H
