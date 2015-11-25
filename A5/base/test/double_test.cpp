#include "gtest/gtest.h"
#include "oset/oset.hpp"
#include <vector>
#include <iostream>
#include <string>
using std::vector;
using std::string;
using std::cout;
using std::endl;

class DoubleTest : public ::testing::Test {
    protected:
        oset<double> os;
        void virtual SetUp(){}
        void virtual TearDown(){}
};

TEST_F(DoubleTest, InsertWithOrder){
    vector<double> s_init = {3.0,2.0,4.0,5.0,7.0,3.0};
    for(auto &&it:s_init) os += it;

    vector<double> s_res = {2.0,3.0,4.0,5.0,7.0};

    int i = 0;
    for(auto it = os.begin(); it != os.end(); it++){
        EXPECT_EQ(*it, s_res[i]);
        ++i;
    }
}

TEST_F(DoubleTest, UnionTest){
    vector<double> vu = {2, 6, 10, 30};
    vector<double> vv = {6, 7, 15, 20, 30};
    vector<double> vres = {2, 6, 7, 10, 15, 20, 30};
    oset<double> osu, osv;
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

TEST_F(DoubleTest, UnionEmpty){
    vector<double> vu = {};
    vector<double> vv = {2, 6, 10};
    vector<double> vres = {2, 6, 10};
    oset<double> osu, osv, ores;
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

TEST_F(DoubleTest, DifferenceTest){
    vector<double> vu = {2, 6, 10};
    vector<double> vv = {6, 7, 10};
    vector<double> vres = {2};
    oset<double> osu, osv;
    for(auto &&it:vu) osu += it;
    for(auto &&it:vv) osv += it;

    //diff osu with osv
    osu -= osv;
    //print(osu);

    int i = 0;
    for(auto it = osu.begin(); it != osu.end() ; it++){
        EXPECT_EQ(*it, vres[i]);
        ++i;
    }

    ASSERT_EQ(i, vres.size());
}

TEST_F(DoubleTest, DifferenceEmpty){
    vector<double> vu = {2,6,10};
    vector<double> vv = {};
    vector<double> vres = {2,6,10};
    oset<double> osu, osv;
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

TEST_F(DoubleTest, IntersectionTest){
    vector<double> vu = {2,7,10,15};
    vector<double> vv = {4,7,10,20};
    vector<double> vres = {7,10};
    oset<double> osu, osv;
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

TEST_F(DoubleTest, IntersectionEmpty){
    vector<double> vu = {3, 4};
    vector<double> vv = {};
    vector<double> vres = {};
    oset<double> osu, osv;
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
