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

    void KeyExpander::subword(aes::word w)
    {
        for (uint8_t& i : w)
            i = internal::SBOX[i];
    }

    void KeyExpander::rotword(aes::word w)
    {
        uint8_t tmp = w[0];
        std::copy(w.begin() + 1, w.end(), w.begin());
        w[3] = tmp;
    }

    void KeyExpander::word_xor(aes::word dst, aes::const_word src)
    {
        for (size_t i = 0; i < internal::WORD_SIZE; ++i)
            dst[i] ^= src[i];
    }

    std::array<uint8_t, internal::WORD_SIZE> KeyExpander::get_rcon(size_t i)
    {
        std::array<uint8_t, internal::WORD_SIZE> tmp{0};
        uint8_t x = 0x01;
        for (size_t j = 0; j < i - 1; ++j)
        {
            x = xtime(x);
        }
        tmp[0] = x;
        return tmp;
    }

    uint8_t KeyExpander::xtime(uint8_t x) const
    {
        if (x & 0x80)
            return (x << 1) ^ 0x1B;
        else
            return x << 1;
    }
}
