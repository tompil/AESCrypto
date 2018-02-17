#include "aes_decipherer.h"

namespace aes {
    void aes_decipherer::decipher(const_block in, block out) const {
        using namespace internal;
        auto add_round_key{block_xor};

        std::copy(in.begin(), in.end(), out.begin());
        add_round_key(out, ekey_[ekey_.size() - 1]);

        for (int i = ekey_.size() - 2; i >= 1; --i) {
            inverse_shift_rows(out);
            inverse_sub_bytes(out);
            add_round_key(out, ekey_[i]);
            inverse_mix_columns(out);
        }

        inverse_shift_rows(out);
        inverse_sub_bytes(out);
        add_round_key(out, ekey_[0]);
    }
}