#ifndef CRYPTOAES_WORD_SPAN_H
#define CRYPTOAES_WORD_SPAN_H

#include <gsl/span>
#include <array>
#include <memory>
#include "key_expander.h"

namespace aes {
    namespace internal {
        class word {
        public:
            word();
            word(gsl::span<uint8_t> w);
            static constexpr size_t size() { return WORD_SIZE; }
            uint8_t& operator[](size_t pos);
            const uint8_t& operator[](size_t pos) const;
            ~word() {}
        private:
            std::unique_ptr<std::array<uint8_t, WORD_SIZE>> word_;
        };
    }
}

#endif //CRYPTOAES_WORD_SPAN_H
