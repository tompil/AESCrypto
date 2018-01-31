#include <gtest/gtest.h>
#include <word.h>


TEST(WordTestCase, DefaultConstructorTest) {
    using namespace aes::internal;
    word w;
    for (int i = 0; i < word::size(); ++i)
        EXPECT_EQ(w[i], 0);
}

TEST(WordTestCase, SizeTest) {
    using namespace aes::internal;
    EXPECT_EQ(word::size(), WORD_SIZE);
}
