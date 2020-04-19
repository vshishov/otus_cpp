#include "../src/ip_filter.h"

#include <gtest/gtest.h>
 
TEST(VersionTest, ValidVersion) { 
    ASSERT_NE(0, 1);
}
 
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}