#include <word.h>

#include <algorithm>

namespace aes {
    namespace internal {
        word::word() : word_{new std::array<uint8_t, WORD_SIZE>} {
        }

        word::word(gsl::span<uint8_t> w) : word_{new std::array<uint8_t, WORD_SIZE>} {
            Expects(w.size() == WORD_SIZE);
            std::copy(w.begin(), w.end(), (*word_).begin());
        }

        uint8_t& word::operator[](size_t pos) {
            return (*word_)[pos];
        }

        const uint8_t& word::operator[](size_t pos) const {
            return (*word_)[pos];
        }
    }
}
