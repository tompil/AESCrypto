#include <utils.h>

#include <gtest/gtest.h>

#include <array>
#include <limits>
#include <numeric>
#include <random>


using aes::internal::WORD_SIZE;
using ByteType = aes::internal::word::value_type;
using word_array = std::array<ByteType, WORD_SIZE>;


TEST(UtilsTestCase, SubwordTest) {
    using aes::internal::SBOX;
    using aes::internal::const_word;
    constexpr size_t words_in_sbox = SBOX.size() / WORD_SIZE;

    for (size_t i = 0; i < words_in_sbox; ++i) {
        word_array input_word{};
        std::iota(input_word.begin(), input_word.end(), i * WORD_SIZE);
        aes::internal::subword(input_word);

        const_word correct_word{SBOX.data() + i * WORD_SIZE, WORD_SIZE};
        EXPECT_EQ(const_word{input_word}, correct_word);
    }
}

TEST(UtilsTestCase, RotwordTest) {
    word_array input_word{};
    std::iota(input_word.begin(), input_word.end(), 0);
    aes::internal::rotword(input_word);

    word_array correct_word{};
    std::iota(correct_word.begin(), correct_word.end() - 1, 1);
    *(correct_word.end()) = 0;
    EXPECT_EQ(input_word, correct_word);
}

TEST(UtilsTestCase, WordXorTest) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, std::numeric_limits<ByteType>::max());
    auto byte_rand = [&dis, &gen]() { return dis(gen); };

    word_array first{};
    std::generate(first.begin(), first.end(), byte_rand);
    word_array second{};
    std::generate(second.begin(), second.end(), byte_rand);

    word_array input_word{};
    std::copy(input_word.begin(), input_word.end(), first.begin());
    aes::internal::word_xor(input_word, second);

    word_array correct_word{};
    for (size_t i = 0; i < correct_word.size(); ++i) {
        correct_word[i] = first[i] ^ second[i];
    }
    EXPECT_EQ(input_word, correct_word);
}

TEST(UtilsTestCase, XtimeTest) {
    using aes::internal::xtime;
    EXPECT_EQ(xtime(0x01), 0x02);
    EXPECT_EQ(xtime(0x08), 0x10);
    EXPECT_EQ(xtime(0x80), 0x1B);
    EXPECT_EQ(xtime(0x1B), 0x36);
}

TEST(UtilsTestCase, CopyWordTest) {
    word_array src{};
    std::iota(src.begin(), src.end(), 0);
    word_array dst{};
    aes::internal::copy(dst, src);
    EXPECT_EQ(src, dst);
}
