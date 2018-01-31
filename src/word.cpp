#include <word.h>

#include <algorithm>

namespace aes {
    namespace internal {
        word::word() : word_{std::make_unique<std::array<uint8_t, WORD_SIZE>>()} {
        }

        word::word(gsl::span<uint8_t> w) : word{} {
            Expects(w.size() == WORD_SIZE);
            std::copy(w.begin(), w.end(), (*word_).begin());
        }

        word::word(const word& w) : word{} {
            std::copy(w.word_->begin(), w.word_->end(), this->word_->begin());
        }

        word::word(word&& w) {
            this->word_ = std::move(w.word_);
        }

        word& word::operator=(const word& w) {
            std::copy(w.word_->begin(), w.word_->end(), this->word_->begin());
        }

        word& word::operator=(word&& w) {
            this->word_ = std::move(w.word_);
        }

        uint8_t& word::operator[](size_t pos) {
            return (*word_)[pos];
        }

        const uint8_t& word::operator[](size_t pos) const {
            return (*word_)[pos];
        }
    }
}
