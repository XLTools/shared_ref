//  :copyright: (c) 2015-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/*
 *  \addtogroup Tests
 *  \brief Test runner.
 */

#include "shared_ref.hpp"
#include <gtest/gtest.h>

using namespace ref;


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
    auto ref = make_shared<int>(1);
    auto other = make_shared<int>(1);
    shared_ref<int> copy(ref);
    EXPECT_EQ(ref, 1);
    EXPECT_EQ(ref, copy);

    // must invoke the copy constructor, since moved is initially null
    shared_ref<int> moved(std::move(copy));
    EXPECT_EQ(moved, 1);
    EXPECT_EQ(copy, 1);
    moved.get() = 2;
    EXPECT_EQ(ref, 2);
    EXPECT_EQ(other, 1);
    EXPECT_EQ(copy, 2);
    EXPECT_EQ(moved, 2);

    // move assignment can move
    moved = std::move(other);
    EXPECT_EQ(moved, 1);
    EXPECT_EQ(other, 2);
}


TEST(shared_ref, Class)
{
    shared_ref<X> ref = make_shared<X>(1);
    shared_ref<X> other = make_shared<X>(2);
    shared_ref<X> copy = std::move(ref);
}


/** \brief Execute test suite.
 */
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
