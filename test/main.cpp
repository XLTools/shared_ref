//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/*
 *  \addtogroup Tests
 *  \brief Test runner.
 */

#include "shared_ref.hpp"
#include <gtest/gtest.h>


struct X
{
    int a;

    X() = delete;
    X(int a): a(a) {}
};

// SUITE
// -----


TEST(shared_ref, Simple)
{
    auto ref = shared_ref<int>(1);
    auto copy = shared_ref<int>(ref);
    EXPECT_EQ(ref, 1);
    EXPECT_EQ(ref, copy);

    shared_ref<int> moved(std::move(copy));
    EXPECT_EQ(moved, 1);
    EXPECT_EQ(copy, 0);
}


TEST(shared_ref, Class)
{
    shared_ref<X> ref(1);
    shared_ref<X> copy(2);
    copy = std::move(ref);
}


/** \brief Execute test suite.
 */
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
