#include "../src/common.h"
#include "../src/ip_filter.h"

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <vector>
#include <string>

using namespace testing;

TEST(Common, SplitTabSeparator) { 
    ASSERT_THAT(split("", '\t'), ElementsAre(StrEq("")));
    ASSERT_THAT(split("1234\t5678", '\t'), ElementsAre(StrEq("1234"), StrEq("5678")));
    ASSERT_THAT(split("qwer\tasdf", '\t'), ElementsAre(StrEq("qwer"), StrEq("asdf")));
    ASSERT_THAT(split("..\t111\t222", '\t'), ElementsAre(StrEq(".."), StrEq("111"), StrEq("222")));
    ASSERT_THAT(split("1.2.3.4", '\t'), ElementsAre(StrEq("1.2.3.4")));
}

TEST(Common, SplitDotSeparator) { 
    ASSERT_THAT(split("", '.'), ElementsAre(StrEq("")));
    ASSERT_THAT(split("11", '.'), ElementsAre(StrEq("11")));
    ASSERT_THAT(split("..", '.'), ElementsAre(StrEq(""), StrEq(""), StrEq("")));
    ASSERT_THAT(split("11.", '.'), ElementsAre(StrEq("11"), StrEq("")));
    ASSERT_THAT(split(".11", '.'), ElementsAre(StrEq(""), StrEq("11")));
    ASSERT_THAT(split("11.22", '.'), ElementsAre(StrEq("11"), StrEq("22")));
    ASSERT_THAT(split("11.22.", '.'), ElementsAre(StrEq("11"), StrEq("22"), StrEq("")));
    ASSERT_THAT(split("11.22.33", '.'), ElementsAre(StrEq("11"), StrEq("22"), StrEq("33")));
}

TEST(IPv4, ReadValidStr) {     
    std::vector<std::string> vValidStrIp = {
        "1.2.3.4",
        "192.168.1.1"    
    };

    CIPv4 ip;
    for (auto& strIp : vValidStrIp) {
        ASSERT_TRUE(ip.readFromStr(strIp));
    }
}

TEST(IPv4, ReadInvalidStr) {
    std::vector<std::string> vInvalidStrIp = { 
        "q.168.1.1",
        "192.w.1.1",
        "192.168.e.1",
        "192.168.1.r",
        "s.w.a.t",
        "1",
        "1.2",
        "1.2.3",
        "1.2.3.4.5",    
        "256.2.3.4",
        "1.256.3.4",
        "1.2.256.4",
        "1.2.3.256",
        "-1.2.3.4",
        "1.-2.3.4",
        "1.2.-3.4",
        "1.2.3.-4"
    };

    CIPv4 ip;
    for (auto& strIp : vInvalidStrIp) {
        EXPECT_FALSE(ip.readFromStr(strIp)) << strIp;
    }
}

TEST(IPv4, Print) {
    // This can be an ofstream as well or any other ostream
    std::stringstream buffer;
    // Save cout's buffer here
    std::streambuf *sbuf = std::cout.rdbuf();
    // Redirect cout to our stringstream buffer or any other ostream
    std::cout.rdbuf(buffer.rdbuf());
    // Use cout as usual
    //std::cout << ip;
    // When done redirect cout to its old self
    std::cout.rdbuf(sbuf);
    //ASSERT_EQ(std::string(buffer.str()), "1.2.3.4");
}

TEST(IpPool, Read) {
    // This can be an ofstream as well or any other ostream
    std::stringstream bufIn;
    bufIn << "1.2.3.4\t0\t0\n" << "s.w.a.t\n" << "192.168.1.1\n";


    CIpPool<CIPv4> ipPool;
    ipPool.read(bufIn);

    std::stringstream bufOut;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(bufOut.rdbuf());
    std::cout << ipPool;
    std::cout.rdbuf(sbuf);
    ASSERT_EQ(std::string(bufOut.str()), "1.2.3.4\n192.168.1.1");
}

TEST(IpPool, Sort) {
    // This can be an ofstream as well or any other ostream
    std::stringstream bufIn;
    bufIn << "1.2.3.4\t0\t0\n" 
        << "s.w.a.t\n" 
        << "1.1.234.8\n"
        << "1.29.168.152\n"
        << "1.70.44.170\n"
        << "222.82.198.61\n"
        << "222.130.177.64\n"
        << "222.173.235.246\n";       

    CIpPool<CIPv4> ipPool;
    ipPool.read(bufIn);
    ipPool.sort_reverse();

    std::stringstream bufOut;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(bufOut.rdbuf());
    std::cout << ipPool;
    std::cout.rdbuf(sbuf);
    ASSERT_EQ(std::string(bufOut.str()), "222.173.235.246\n"
        "222.130.177.64\n"
        "222.82.198.61\n"
        "1.70.44.170\n"
        "1.29.168.152\n"
        "1.2.3.4\n"
        "1.1.234.8"
    );
}

TEST(IpPool, Filter_1arg) {
    // This can be an ofstream as well or any other ostream
    std::stringstream bufIn;
    bufIn << "1.2.3.4\t0\t0\n" 
        << "s.w.a.t\n" 
        << "1.1.234.8\n"
        << "1.29.168.152\n"
        << "1.70.44.170\n"
        << "222.82.198.61\n"
        << "222.130.177.64\n"
        << "222.173.235.246\n";       

    CIpPool<CIPv4> ipPool;
    ipPool.read(bufIn);
    ipPool.sort_reverse();    

    std::stringstream bufOut;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(bufOut.rdbuf());
    std::cout << ipPool.filter(222);
    std::cout.rdbuf(sbuf);
    ASSERT_EQ(std::string(bufOut.str()), "222.173.235.246\n"
        "222.130.177.64\n"
        "222.82.198.61"
    );
}

TEST(IpPool, Filter_2arg) {
    // This can be an ofstream as well or any other ostream
    std::stringstream bufIn;
    bufIn << "1.29.3.4\t0\t0\n" 
        << "s.w.a.t\n" 
        << "1.1.234.8\n"
        << "1.29.168.152\n"
        << "1.70.44.170\n"
        << "222.82.198.61\n"
        << "222.130.177.64\n"
        << "222.173.235.246\n";       

    CIpPool<CIPv4> ipPool;
    ipPool.read(bufIn);
    ipPool.sort_reverse();    

    std::stringstream bufOut;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(bufOut.rdbuf());
    std::cout << ipPool.filter(1, 29);
    std::cout.rdbuf(sbuf);
    ASSERT_EQ(std::string(bufOut.str()), "1.29.168.152\n1.29.3.4");
}

TEST(IpPool, FilterAny) {
    // This can be an ofstream as well or any other ostream
    std::stringstream bufIn;
    bufIn << "1.29.3.4\t0\t0\n" 
        << "s.w.a.t\n" 
        << "1.1.130.8\n"
        << "1.29.168.152\n"
        << "1.70.44.130\n"
        << "222.82.198.61\n"
        << "222.130.177.64\n"
        << "222.173.235.246\n";       

    CIpPool<CIPv4> ipPool;
    ipPool.read(bufIn);
    ipPool.sort_reverse();    

    std::stringstream bufOut;
    std::streambuf *sbuf = std::cout.rdbuf();
    std::cout.rdbuf(bufOut.rdbuf());
    std::cout << ipPool.filter_any(130);
    std::cout.rdbuf(sbuf);
    ASSERT_EQ(std::string(bufOut.str()), "222.130.177.64\n1.70.44.130\n1.1.130.8");
}