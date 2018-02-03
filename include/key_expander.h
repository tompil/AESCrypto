#ifndef CRYPTOAES_KEY_EXPANDER_H
#define CRYPTOAES_KEY_EXPANDER_H

#include <defs.h>

#include <cstdint>
#include <cstddef>
#include <gsl/span>


namespace aes {

    class KeyExpander {
    public:
        explicit KeyExpander(gsl::span<const uint8_t> key);
        gsl::span<const uint8_t> get_round_key(size_t key_idx) const;
        ~KeyExpander();

    private:
        uint8_t* expanded_key;
        size_t number_of_rounds = 10;
        using word = gsl::span<uint8_t>;

        void expand_key(gsl::span<const uint8_t> key);
        word get_word(size_t i);
        void subword(word& w);
        void rotword(word w);
        void word_xor(word& d, const word& s);
        std::array<uint8_t, internal::WORD_SIZE> get_rcon(size_t i);

        uint8_t xtime(uint8_t x) const;
    };

}
#endif //CRYPTOAES_KEY_EXPANDER_H
