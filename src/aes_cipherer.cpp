#include "aes_cipherer.h"


namespace aes {
    void aes_cipherer::cipher(const_block in, block out) const {
        using namespace internal;
        auto add_round_key{block_xor};

        std::copy(in.begin(), in.end(), out.begin());
        add_round_key(out, ekey_[0]);

        for (uint8_t i = 1; i < ekey_.size() - 1; ++i) {
            sub_bytes(out);
            shift_rows(out);
            mix_columns(out);
            add_round_key(out, ekey_[i]);
        }

        sub_bytes(out);
        shift_rows(out);
        add_round_key(out, ekey_[ekey_.size() - 1]);
    }
}
