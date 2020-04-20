#include "../src/ip_filter.h"

#include <gtest/gtest.h>
#include <vector>
#include <string>

TEST(Split, SplitStr) { 
    std::vector<std::string> v = split("11", '.');
    ASSERT_EQ(v[0], "11");
}