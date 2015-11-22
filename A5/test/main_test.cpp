#include "gtest/gtest.h"
#include "oset/oset.hpp"
#include <vector>
#include <iostream>
#include <string>
using std::vector;
using std::string;
using std::cout;
using std::endl;

class OsetTest : public ::testing::Test {
    protected:
        oset os;
        void virtual SetUp(){}
        void virtual TearDown(){}
};

TEST_F(OsetTest, InsertWithOrder){
    vector<int> s_init = {3,2,4,5,7,3};
    for(auto &&it:s_init) os += it;

    vector<int> s_res = {2,3,4,5,7};

    int i = 0;
    for(auto it = os.begin(); it != os.end(); it++){
        EXPECT_EQ(*it, s_res[i]);
        ++i;
    }
}

TEST_F(OsetTest, UnionTest){
    vector<int> vu = {2, 6, 10, 30};
    vector<int> vv = {6, 7, 15, 20, 30};
    vector<int> vres = {2, 6, 7, 10, 15, 20, 30};
    oset osu, osv;
    for(auto &&it:vu) osu += it;
    for(auto &&it:vv) osv += it;

    //union osu with osv
    osu += osv;
    //print(osu);
    int i = 0;
    for(auto it = osu.begin(); it != osu.end(); it++){
        EXPECT_EQ(vres[i], *it);
        ++i;
    }
    ASSERT_EQ(i, vres.size());
}

TEST_F(OsetTest, UnionEmpty){
    vector<int> vu;
    vector<int> vv = {2, 6, 10};
    vector<int> vres = {2, 6, 10};
    oset osu, osv, ores;
    for(auto &&it:vu) osu += it;
    for(auto &&it:vv) osv += it;

    //union osu with osv
    osu += osv;

    int i = 0;
    for(auto it = osu.begin(); it != osu.end(); it++){
        EXPECT_EQ(*it, vres[i]);
        ++i;
    }
}

TEST_F(OsetTest, DifferenceTest){
    vector<int> vu = {2, 6, 10};
    vector<int> vv = {6, 7};
    vector<int> vres = {2, 10};
    oset osu, osv;
    for(auto &&it:vu) osu += it;
    for(auto &&it:vv) osv += it;

    //diff osu with osv
    osu -= osv;

    int i = 0;
    for(auto it = osu.begin(); it != osu.end(); it++){
        EXPECT_EQ(*it, vres[i]);
        ++i;
    }
}

TEST_F(OsetTest, DifferenceEmpty){
    vector<int> vu = {2,6,10};
    vector<int> vv = {};
    vector<int> vres = {2,6,10};
    oset osu, osv, ores;
    for(auto &&it:vu) osu += it;
    for(auto &&it:vv) osv += it;

    //diff osu with osv
    osu -= osv;

    int i = 0;
    for(auto it = ores.begin(); it != ores.end(); it++){
        EXPECT_EQ(*it, vres[i]);
        ++i;
    }
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
