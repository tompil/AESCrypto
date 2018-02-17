#ifndef CRYPTOAES_DEFS_H
#define CRYPTOAES_DEFS_H

#include "internal/internal_defs.h"

#include <array>
#include <gsl/span>


namespace aes {
    constexpr size_t KEY128_SIZE{internal::WORD_SIZE * internal::KEY128_WSIZE};
    constexpr size_t KEY192_SIZE{internal::WORD_SIZE * internal::KEY192_WSIZE};
    constexpr size_t KEY256_SIZE{internal::WORD_SIZE * internal::KEY256_WSIZE};
    constexpr size_t BLOCK_SIZE{internal::WORD_SIZE * internal::BLOCK_WSIZE};

    using aes128_key = gsl::span<const uint8_t, KEY128_SIZE>;
    using aes192_key = gsl::span<const uint8_t, KEY192_SIZE>;
    using aes256_key = gsl::span<const uint8_t, KEY256_SIZE>;
    using block = gsl::span<uint8_t, BLOCK_SIZE>;
    using const_block = gsl::span<const uint8_t, BLOCK_SIZE>;
}

#endif //CRYPTOAES_DEFS_H
