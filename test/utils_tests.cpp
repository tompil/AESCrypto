#include "utils.h"

#include <gtest/gtest.h>
#include <numeric>
#include <random>


using aes::internal::WORD_SIZE;
using aes::BLOCK_SIZE;
using ByteType = aes::internal::word::value_type;
using word_array = std::array<ByteType, WORD_SIZE>;
using block_array = std::array<ByteType, BLOCK_SIZE>;


TEST(UtilsTestCase, SubWordTest) {
    using aes::internal::SBOX;
    using aes::internal::const_word;
    constexpr size_t words_in_sbox{SBOX.size() / WORD_SIZE};

    for (size_t i = 0; i < words_in_sbox; ++i) {
        word_array input_word{};
        std::iota(input_word.begin(), input_word.end(), i * WORD_SIZE);
        aes::internal::sub_word(input_word);

        const_word correct_word{SBOX.data() + i * WORD_SIZE, WORD_SIZE};
        EXPECT_EQ(const_word{input_word}, correct_word);
    }
}

TEST(UtilsTestCase, RotWordTest) {
    word_array input_word{};
    std::iota(input_word.begin(), input_word.end(), 0);
    aes::internal::rot_word(input_word);

    word_array correct_word{};
    std::iota(correct_word.begin(), correct_word.end() - 1, 1);
    *(correct_word.end()) = 0;
    EXPECT_EQ(input_word, correct_word);
}

TEST(UtilsTestCase, WordXorTest) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<ByteType>::max()};
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

TEST(UtilsTestCase, XTimeTest) {
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

TEST(UtilsTestCase, SubBytesTest) {
    using aes::internal::SBOX;
    using aes::const_block;
    constexpr size_t blocks_in_sbox = SBOX.size() / BLOCK_SIZE;

    for (size_t i = 0; i < blocks_in_sbox; ++i) {
        block_array input_block{};
        std::iota(input_block.begin(), input_block.end(), i * BLOCK_SIZE);
        aes::internal::sub_bytes(input_block);

        const_block correct_block{SBOX.data() + i * BLOCK_SIZE, BLOCK_SIZE};
        EXPECT_EQ(const_block{input_block}, correct_block);
    }
}

TEST(UtilsTestCase, ShiftRowsTest) {
    block_array input_block{
        0xB4, 0x15, 0xF8, 0x01,
        0x68, 0x58, 0x55, 0x2E,
        0x4B, 0xB6, 0x12, 0x4C,
        0x5F, 0x99, 0x8A, 0x4C
    };

    block_array correct_block{
        0xB4, 0x58, 0x12, 0x4C,
        0x68, 0xB6, 0x8A, 0x01,
        0x4B, 0x99, 0xF8, 0x2E,
        0x5F, 0x15, 0x55, 0x4C
    };

    aes::internal::shift_rows(input_block);
    EXPECT_EQ(input_block, correct_block);
}

TEST(UtilsTestCase, MixColumnsTest) {
    block_array input_block{
            0xB4, 0x58, 0x12, 0x4C,
            0x68, 0xB6, 0x8A, 0x01,
            0x4B, 0x99, 0xF8, 0x2E,
            0x5F, 0x15, 0x55, 0x4C
    };

    block_array correct_block{
            0xC5, 0x7E, 0x1C, 0x15,
            0x9A, 0x9B, 0xD2, 0x86,
            0xF0, 0x5F, 0x4B, 0xE0,
            0x98, 0xC6, 0x34, 0x39
    };

    aes::internal::mix_columns(input_block);
    EXPECT_EQ(input_block, correct_block);
}

TEST(UtilsTestCase, BlockXorTest) {
    block_array first{
            0x47, 0xF7, 0xF7, 0xBC, 0x95, 0x35, 0x3E, 0x03, 0xF9, 0x6C, 0x32, 0xBC, 0xFD, 0x05, 0x8D, 0xFD
    };
    block_array second{
            0x63, 0x85, 0xB7, 0x9F, 0xFC, 0x53, 0x8D, 0xF9, 0x97, 0xBE, 0x47, 0x8E, 0x75, 0x47, 0xD6, 0x91
    };
    block_array correct_word{
            0x24, 0x72, 0x40, 0x23, 0x69, 0x66, 0xB3, 0xFA, 0x6E, 0xD2, 0x75, 0x32, 0x88, 0x42, 0x5B, 0x6C
    };

    aes::internal::block_xor(first, second);
    EXPECT_EQ(first, correct_word);
}

TEST(UtilsTestCase, InverseSubBytesTest) {
    using aes::internal::INVERSE_SBOX;
    using aes::const_block;
    constexpr size_t blocks_in_sbox = INVERSE_SBOX.size() / BLOCK_SIZE;

    for (size_t i = 0; i < blocks_in_sbox; ++i) {
        block_array input_block{};
        std::iota(input_block.begin(), input_block.end(), i * BLOCK_SIZE);
        aes::internal::inverse_sub_bytes(input_block);

        const_block correct_block{INVERSE_SBOX.data() + i * BLOCK_SIZE, BLOCK_SIZE};
        EXPECT_EQ(const_block{input_block}, correct_block);
    }
}

TEST(UtilsTestCase, InverseShiftRowsTest) {
    block_array input_block{
            0xB4, 0x58, 0x12, 0x4C,
            0x68, 0xB6, 0x8A, 0x01,
            0x4B, 0x99, 0xF8, 0x2E,
            0x5F, 0x15, 0x55, 0x4C
    };

    block_array correct_block{
            0xB4, 0x15, 0xF8, 0x01,
            0x68, 0x58, 0x55, 0x2E,
            0x4B, 0xB6, 0x12, 0x4C,
            0x5F, 0x99, 0x8A, 0x4C
    };

    aes::internal::inverse_shift_rows(input_block);
    EXPECT_EQ(input_block, correct_block);
}

TEST(UtilsTestCase, InverseMixColumnsTest) {
    block_array input_block{
            0xC5, 0x7E, 0x1C, 0x15,
            0x9A, 0x9B, 0xD2, 0x86,
            0xF0, 0x5F, 0x4B, 0xE0,
            0x98, 0xC6, 0x34, 0x39

    };

    block_array correct_block{
            0xB4, 0x58, 0x12, 0x4C,
            0x68, 0xB6, 0x8A, 0x01,
            0x4B, 0x99, 0xF8, 0x2E,
            0x5F, 0x15, 0x55, 0x4C
    };

    aes::internal::inverse_mix_columns(input_block);
    EXPECT_EQ(input_block, correct_block);
}
