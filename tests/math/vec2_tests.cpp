//
// Created by robbie on 24-10-2016.
//

#include "gtest/gtest.h"
#include "../../src/math/vec2.hpp"

class vec2_fixture : public ::testing::Test {
protected:
    virtual void TearDown() {
    }

    virtual void SetUp() {
    }

public:
    math::vec2_t * vec2;

    vec2_fixture() : Test() {
        vec2 = new math::vec2_t{5, 10};
    }

    virtual ~vec2_fixture() {
        delete vec2;
    }
};

TEST_F(vec2_fixture, vec2_basic_test) {
    EXPECT_EQ(5, vec2->x);
    EXPECT_EQ(10, vec2->y);
}

TEST_F(vec2_fixture, vec2_clamp_test) {
    vec2->clamp(4, 8);
    EXPECT_EQ(5, vec2->x);
    EXPECT_EQ(8, vec2->y);
    vec2->clamp(6, 15);
    EXPECT_EQ(6, vec2->x);
    EXPECT_EQ(8, vec2->y);
}
