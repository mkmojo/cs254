#include "gtest/gtest.h"
#include "oset/oset.hpp" // to be tested
#include <vector>
#include <iostream>
#include <string>
#include <ctype.h>
using std::vector;
using std::string;
using std::cout;
using std::endl;

struct str_insensitive_ge{
    bool operator()(const string& a, const string& b)const{
        for(int i=0;i<a.size() && i<b.size();i++){
            char ca = tolower(a[i]);
            char cb = tolower(b[i]);
            if(ca < cb) return false;
        }
        if(a.size() < b.size()) return false;
        return true;
    }
};

class StringTest : public ::testing::Test {
    protected:
        void virtual SetUp(){}
        void virtual TearDown(){}
};

TEST_F(StringTest, InsertWithOrder){
    oset<string> os;
    vector<string> s_init = {"a", "b", "a", "c", "hello", "HellO"};
    for(auto &&it:s_init) os += it;
    vector<string> s_res = {"HellO", "a", "b", "c", "hello"};

    int i = 0;
    for(auto it = os.begin(); it != os.end(); it++){
        EXPECT_EQ(*it, s_res[i]);
        ++i;
    }
}

TEST_F(StringTest, UnionTest){
    vector<string> vu = {"a", "h", "MM", "zz"};
    vector<string> vv = {"e", "f", "MM", "pp", "zz"};
    vector<string> vres = {"a", "e", "f", "h", "MM", "pp", "zz"};
    oset<string, str_insensitive_ge> osu, osv;
    for(auto &&it:vu) osu += it;
    for(auto &&it:vv) osv += it;

    //union osu with osv
    osu += osv;
    int i = 0;
    for(auto it = osu.begin(); it != osu.end(); it++){
        EXPECT_EQ(vres[i], *it);
        ++i;
    }
    ASSERT_EQ(i, vres.size());
}

TEST_F(StringTest, UnionEmpty){
    vector<string> vu = {};
    vector<string> vv = {"b", "F", "h"};
    vector<string> vres = {"b", "F", "h"};
    oset<string,str_insensitive_ge> osu, osv, ores;
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

TEST_F(StringTest, DifferenceTest){
    vector<string> vu = {"b", "f", "h"};
    vector<string> vv = {"b", "g", "h"};
    vector<string> vres = {"f"};
    oset<string> osu, osv;
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

TEST_F(StringTest, DifferenceEmpty){
    vector<string> vu = {"b", "f", "h"};
    vector<string> vv = {};
    vector<string> vres = {"b", "f", "h"};
    oset<string> osu, osv;
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

TEST_F(StringTest, IntersectionTest){
    vector<string> vu = {"a", "h", "mm", "zz"};
    vector<string> vv = {"c", "h", "mm", "yy"};
    vector<string> vres = {"h", "mm"};
    oset<string> osu, osv;
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

TEST_F(StringTest, IntersectionEmpty){
    vector<string> vu = {"c", "d"};
    vector<string> vv = {};
    vector<string> vres = {};
    oset<string> osu, osv;
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

