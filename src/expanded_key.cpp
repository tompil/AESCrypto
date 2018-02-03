#include <expanded_key.h>
#include <algorithm>

namespace aes {

    expanded_key::expanded_key(aes128_key key) : key_wsize_(4), number_of_rounds_(10)
    {
        expand_key(key);
    }

    expanded_key::expanded_key(aes192_key key) : key_wsize_(6), number_of_rounds_(12)
    {
        expand_key(key);
    }

    expanded_key::expanded_key(aes256_key key) : key_wsize_(8), number_of_rounds_(14)
    {
        expand_key(key);
    }

    aes::round_key expanded_key::get_round_key(size_t key_idx) const
    {
        return {expanded_key_ + key_idx * BLOCK_SIZE, BLOCK_SIZE};
    }

    void expanded_key::expand_key(gsl::span<const uint8_t> key)
    {
        std::copy(key.begin(), key.end(), expanded_key_);

        uint8_t rcon = 0x01;
        for (size_t i = key_wsize_; i < (number_of_rounds_ + 1) * internal::BLOCK_WSIZE; ++i)
        {
            word ith_word = get_word(i);
            copy(ith_word, get_word(i - 1));

            if (i % key_wsize_ == 0)
            {
                rotword(ith_word);
                subword(ith_word);
                ith_word[0] ^= rcon;
                rcon = xtime(rcon);
            }
            else if (key_wsize_ > 6 && i % key_wsize_ == 4)
            {
                subword(ith_word);
            }
            word_xor(ith_word, get_word(i - key_wsize_));
        }
    }

    aes::word expanded_key::get_word(size_t i)
    {
        return {expanded_key_ + i * internal::WORD_SIZE, internal::WORD_SIZE};
    }

}
