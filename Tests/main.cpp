/**
 * @file main.cpp
 * @author paul
 * @date 09.03.19
 * @brief main @TODO
 */

#include <gtest/gtest.h>
#include <gmock/gmock.h>
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}