#include "gtest/gtest.h"
#include "oset/oset.hpp"
#include <vector>
#include <iostream>
#include <string>
using std::vector;
using std::string;
using std::cout;
using std::endl;

class IntTest : public ::testing::Test {
    protected:
        oset<int> os;
        void virtual SetUp(){}
        void virtual TearDown(){}
};

TEST_F(IntTest, InsertWithOrder){
    os += 5;
    rprint(os);
    os += 3;
    rprint(os);
    os += 4;
    rprint(os);
    vector<int> s_res = {3, 4, 5};

    int i = 0;
    for(auto it = os.begin(); it != os.end(); it++){
        EXPECT_EQ(*it, s_res[i]);
        ++i;
    }
    ASSERT_EQ(s_res.size(), i);
}

TEST_F(IntTest, UnionTest){
    vector<int> vu = {2, 6, 10, 30};
    vector<int> vv = {6, 7, 15, 20, 30};
    vector<int> vres = {2, 6, 7, 10, 15, 20, 30};
    oset<int> osu, osv;
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

TEST_F(IntTest, UnionEmpty){
    vector<int> vu = {};
    vector<int> vv = {2, 6, 10};
    vector<int> vres = {2, 6, 10};
    oset<int> osu, osv, ores;
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

TEST_F(IntTest, DifferenceTest){
    vector<int> vu = {2, 6, 10};
    vector<int> vv = {2, 6, 10};
    vector<int> vres = {};
    oset<int> osu, osv;
    for(auto &&it:vu) osu += it;
    for(auto &&it:vv) osv += it;

    //diff osu with osv
    osu -= osv;
    print(osu);

    int i = 0;
    for(auto it = osu.begin(); it != osu.end() ; it++){
        EXPECT_EQ(*it, vres[i]);
        ++i;
    }

    ASSERT_EQ(i, vres.size());
}

TEST_F(IntTest, DifferenceEmpty){
    vector<int> vu = {2,6,10};
    vector<int> vv = {};
    vector<int> vres = {2,6,10};
    oset<int> osu, osv;
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

TEST_F(IntTest, IntersectionTest){
    vector<int> vu = {2,7,10,15};
    vector<int> vv = {4,7,10,20};
    vector<int> vres = {7,10};
    oset<int> osu, osv;
    for(auto &&it:vu) osu += it;
    for(auto &&it:vv) osv += it;

    osu *= osv;

    int i = 0;
    for(auto it = osu.begin(); it != osu.end(); it++){
        EXPECT_EQ(*it, vres[i]);
        ++i;
    }

    ASSERT_EQ(i, vres.size());
}

TEST_F(IntTest, IntersectionEmpty){
    vector<int> vu = {3, 4};
    vector<int> vv = {};
    vector<int> vres = {};
    oset<int> osu, osv;
    for(auto &&it:vu) osu += it;
    for(auto &&it:vv) osv += it;

    osu *= osv;
    //print(osu);

    int i = 0;
    for(auto it = osu.begin(); it != osu.end(); it++){
        EXPECT_EQ(*it, vres[i]);
        ++i;
    }
}

