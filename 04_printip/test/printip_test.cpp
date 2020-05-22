#include "print_ip.h"

#include <gtest/gtest.h>
#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <sstream>

using namespace testing;

TEST(print_ip, string) { 
  std::stringstream ss { };

  print_ip(std::string(""), ss);
  EXPECT_EQ(ss.str(), "\n");
  ss.str("");

  print_ip(std::string("Test stl string"), ss);
  EXPECT_EQ(ss.str(), "Test stl string\n");
  ss.str("");
}

TEST(print_ip, c_string) { 
  std::stringstream ssout { };

  print_ip("", ssout);
  EXPECT_EQ(ssout.str(), "\n");
  ssout.str("");

  print_ip("Test stl c-string", ssout);
  EXPECT_EQ(ssout.str(), "Test stl c-string\n");
  ssout.str("");
}

TEST(print_ip, number) { 
  std::stringstream ssout { };

  print_ip(char(-1), ssout);
  EXPECT_EQ(ssout.str(), "255\n");
  ssout.str("");

  print_ip(short(0), ssout);
  EXPECT_EQ(ssout.str(), "0.0\n");
  ssout.str("");

  print_ip(int(2130706433), ssout);
  EXPECT_EQ(ssout.str(), "127.0.0.1\n");
  ssout.str("");

  print_ip(long(8875824491850138409), ssout);
  EXPECT_EQ(ssout.str(), "123.45.67.89.101.112.131.41\n");
  ssout.str("");
}

TEST(print_ip, container) { 
  std::stringstream ssout { };

  print_ip(std::vector<int>{192, 168, 1, 1}, ssout);
  EXPECT_EQ(ssout.str(), "192.168.1.1\n");
  ssout.str("");

  print_ip(std::vector<std::string> {"sim", "ple", "str", "ing"}, ssout);
  EXPECT_EQ(ssout.str(), "sim.ple.str.ing\n");
  ssout.str("");

  print_ip(std::list<int>{127, 0, 0, 1}, ssout);
  EXPECT_EQ(ssout.str(), "127.0.0.1\n");
  ssout.str("");

  std::list<std::string> vecIp {"sim", "ple", "str", "ing"};
  print_ip(vecIp, ssout);
  EXPECT_EQ(ssout.str(), "sim.ple.str.ing\n");
  ssout.str("");
}

TEST(print_ip, tuple) { 
  std::stringstream ssout { };
  print_ip(std::make_tuple(2, 4, 8, 16), ssout);
  EXPECT_EQ(ssout.str(), "2.4.8.16\n");
  ssout.str("");

  print_ip(std::make_tuple("qwe", "asd", "zxc"), ssout);
  EXPECT_EQ(ssout.str(), "qwe.asd.zxc\n");
  ssout.str("");
}