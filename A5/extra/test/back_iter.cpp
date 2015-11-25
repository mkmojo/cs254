#include "gtest/gtest.h"
#include "oset/oset.hpp" // to be tested
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <ctype.h>
using std::vector;
using std::string;
using std::cout;
using std::endl;

class BackIterTest : public ::testing::Test {
    protected:
        void virtual SetUp(){}
        void virtual TearDown(){}
};

TEST_F(BackIterTest, InsertWithOrder){
    oset<string> os;
    vector<string> s_init = {"a", "b", "a", "c", "hello", "HellO"};
    for(auto &&it:s_init) os += it;
    vector<string> s_res = {"HellO", "a", "b", "c", "hello"};
    reverse(s_res.begin(), s_res.end());

    int i = 0;
    for(auto it = os.rbegin(); it != os.rend(); it++){
        EXPECT_EQ(*it, s_res[i]);
        ++i;
    }
}
