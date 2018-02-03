#ifndef CRYPTOAES_KEY_EXPANDER_H
#define CRYPTOAES_KEY_EXPANDER_H

#include <defs.h>
#include <utils.h>

#include <cstdint>
#include <cstddef>
#include <gsl/span>


namespace aes {

    class KeyExpander {
    public:
        explicit KeyExpander(gsl::span<const uint8_t> key);
        aes::round_key get_round_key(size_t key_idx) const;
        ~KeyExpander();

    private:
        uint8_t* expanded_key;
        size_t number_of_rounds = 10;

        void expand_key(gsl::span<const uint8_t> key);
        word get_word(size_t i);
    };

}
#endif //CRYPTOAES_KEY_EXPANDER_H
