#include <key_expander.h>
#include <algorithm>

namespace aes {
    KeyExpander::KeyExpander(gsl::span<const uint8_t> key)
    {
        size_t ekey_size = (number_of_rounds + 1) * BLOCK_SIZE;
        expanded_key = new uint8_t[ekey_size];
        expand_key(key);
    }

    aes::round_key KeyExpander::get_round_key(size_t key_idx) const
    {
        return {expanded_key + key_idx * BLOCK_SIZE, BLOCK_SIZE};
    }

    KeyExpander::~KeyExpander()
    {
        delete[] expanded_key;
    }

    void KeyExpander::expand_key(gsl::span<const uint8_t> key)
    {
        std::copy(key.begin(), key.end(), expanded_key);

        size_t nk = key.size() / internal::WORD_SIZE;

        for (size_t i = nk; i < (number_of_rounds + 1) * internal::BLOCK_WSIZE; ++i)
        {
            word prev = get_word(i - 1);
            word temp = get_word(i);
            std::copy(prev.begin(), prev.end(), temp.begin());

            if (i % nk == 0)
            {
                rotword(temp);
                subword(temp);
                std::array<uint8_t, internal::WORD_SIZE> rcon = get_rcon(i / nk);
                word_xor(temp, rcon);
            }
            else if (nk > 6 && i % nk == 4)
            {
                subword(temp);
            }
            word_xor(temp, get_word(i - nk));
        }
    }

    aes::word KeyExpander::get_word(size_t i)
    {
        return {expanded_key + i * internal::WORD_SIZE, internal::WORD_SIZE};
    }
}
