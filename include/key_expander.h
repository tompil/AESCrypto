#ifndef CRYPTOAES_KEY_EXPANDER_H
#define CRYPTOAES_KEY_EXPANDER_H

#include <cstdint>
#include <cstddef>
#include <gsl/span>

namespace aes {
    namespace internal {
        constexpr size_t WORD_SIZE = 4;
        constexpr size_t KEY128_WSIZE = 4;
        constexpr size_t KEY192_WSIZE = 6;
        constexpr size_t KEY256_WSIZE = 8;
        constexpr size_t BLOCK_WSIZE = 4;
    }

    constexpr size_t KEY128_SIZE = internal::WORD_SIZE * internal::KEY128_WSIZE;
    constexpr size_t KEY192_SIZE = internal::WORD_SIZE * internal::KEY192_WSIZE;
    constexpr size_t KEY256_SIZE = internal::WORD_SIZE * internal::KEY256_WSIZE;
    constexpr size_t BLOCK_SIZE = internal::WORD_SIZE * internal::BLOCK_WSIZE;

    using round_key = std::array<uint8_t, BLOCK_SIZE>;

    class KeyExpander {
        round_key tmp;
    public:
        KeyExpander(gsl::span<uint8_t> key) {}
        const round_key& get_round_key(size_t key_idx) {return tmp;}
    };

}
#endif //CRYPTOAES_KEY_EXPANDER_H
