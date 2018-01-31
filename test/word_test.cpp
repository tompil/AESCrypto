#include <gtest/gtest.h>
#include <word.h>
#include <array>


TEST(WordTestCase, DefaultConstructorTest) {
    using namespace aes::internal;
    word w;
    for (int i = 0; i < word::size(); ++i)
        EXPECT_EQ(w[i], 0);
}

TEST(WordTestCase, SpanConstructorTest) {
    using namespace aes::internal;
    std::array<uint8_t, WORD_SIZE> src = {1, 4, 2, 7};
    word w{src};
    for (int i = 0; i < word::size(); ++i)
        EXPECT_EQ(w[i], src[i]);
}

TEST(WordTestCase, CopyConstructorTest) {
    using namespace aes::internal;
    std::array<uint8_t, WORD_SIZE> src = {1, 4, 2, 7};
    word w1{src};
    word w2{w1};
    for (int i = 0; i < word::size(); ++i)
        EXPECT_EQ(w1[i], w2[i]);
}

TEST(WordTestCase, MoveConstructorTest) {
    using namespace aes::internal;
    std::array<uint8_t, WORD_SIZE> src = {1, 4, 2, 7};
    word w1{src};
    word w2{std::move(w1)};
    for (int i = 0; i < word::size(); ++i)
        EXPECT_EQ(w2[i], src[i]);
}

TEST(WordTestCase, CopyAssignmentOpTest) {
    using namespace aes::internal;
    std::array<uint8_t, WORD_SIZE> src = {1, 4, 2, 7};
    word w1{src};
    word w2 = w1;
    for (int i = 0; i < word::size(); ++i)
        EXPECT_EQ(w1[i], w2[i]);
}

TEST(WordTestCase, MoveAssignmentOpTest) {
    using namespace aes::internal;
    std::array<uint8_t, WORD_SIZE> src = {1, 4, 2, 7};
    word w1{src};
    word w2 = std::move(w1);
    for (int i = 0; i < word::size(); ++i)
        EXPECT_EQ(w2[i], src[i]);
}

TEST(WordTestCase, SizeTest) {
    using namespace aes::internal;
    EXPECT_EQ(word::size(), WORD_SIZE);
}
