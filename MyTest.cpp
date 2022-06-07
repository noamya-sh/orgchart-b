#include "doctest.h"
#include <iostream>
#include <vector>
#include "sources/OrgChart.hpp"

using namespace std;
using namespace ariel;


TEST_CASE("input test"){
    OrgChart o1;
    //invalid inputs
    CHECK_THROWS(o1.add_root(""));
    CHECK_THROWS(o1.add_root("g\n"));
    CHECK_THROWS(o1.add_root("\th"));
    CHECK_THROWS(o1.add_root("r\r"));
    //valid inputs
    CHECK_NOTHROW(o1.add_root("AA#"));
    CHECK_NOTHROW(o1.add_root("HEAD"));
    //invalid inputs
    CHECK_THROWS(o1.add_sub("HEAD",""));
    CHECK_THROWS(o1.add_sub("HEAD","eee\n"));
    CHECK_THROWS(o1.add_sub("HEAD","hg\tgd"));
    CHECK_THROWS(o1.add_sub("HEAD","ewe\r"));
}
TEST_CASE("hierarchy - test"){
    OrgChart o1;
    CHECK_THROWS(o1.add_sub("HEAD","VICE")); // not exist root
    CHECK_NOTHROW(o1.add_root("HEAD"));
    CHECK_THROWS(o1.add_sub("II","FF")); // not exist "II"
    CHECK_NOTHROW(o1.add_root("DD"));
    CHECK_NOTHROW(o1.add_sub("DD","HH"));
    CHECK_THROWS(o1.add_sub("HEAD","LL")); // "HEAD" replaced by "DD"
    for(auto it = o1.begin();it != o1.end();++it){
        CHECK_EQ(it.size(),2);
    }
    }
TEST_CASE("operators test"){
    OrgChart o1;
    string s = "AAA";
    o1.add_root(s).add_sub("AAA","BBB").add_sub("AAA","CCC").add_sub("AAA","DDD");
    auto it = o1.begin_level_order();
    CHECK_EQ(s,*it); //operator *
    auto t = it++;
    CHECK_EQ(*t,s); //operator it++
    CHECK_EQ(t->at(2),'A'); //operator ->
    CHECK(t!=it); //operator !=
    CHECK_EQ(*(++t),*it); //operator ++it
    CHECK(t==it); //operator ==

}
TEST_CASE("level order test")
{
    OrgChart o2;
    CHECK_THROWS(auto it = o2.begin_level_order()); //the root is nullptr
    o2.add_root("1").add_sub("1", "2").add_sub("1", "3").add_sub("1", "4")
    .add_sub("2", "5").add_sub("2", "6").add_sub("2", "7").add_sub("2", "8")
    .add_sub("3", "9").add_sub("3", "10").add_sub("3", "11").add_sub("3", "12")
    .add_sub("4", "13").add_sub("4", "14").add_sub("4", "15").add_sub("4", "16")
    .add_sub("5", "17").add_sub("5", "18").add_sub("5", "19").add_sub("5", "20");

    size_t i = 1;
    for (auto it = o2.begin_level_order(); it != o2.end_level_order(); ++it,i++) {
                CHECK_EQ(to_string(i), (*it));
    }
    i = 1;
    //for each test (default is level order)
    for (auto node:o2){
        CHECK_EQ(to_string(i++), node);
    }

}
TEST_CASE("preorder test"){
    OrgChart o2;
    CHECK_THROWS(auto it = o2.begin_preorder()); //the root is nullptr
    o2.add_root("1").add_sub("1", "2").add_sub("2", "3").add_sub("3", "4")
    .add_sub("3", "5").add_sub("2", "6").add_sub("6", "7").add_sub("6", "8")
    .add_sub("2","9").add_sub("9","10").add_sub("9","11").add_sub("9","12")
    .add_sub("9","13").add_sub("2","14").add_sub("14","15").add_sub("14","16")
    .add_sub("14","17").add_sub("2","18").add_sub("18","19").add_sub("18","20");
    size_t j = 1,i = 2;
    //check it++
    for (auto it = o2.begin_preorder(); it != o2.end_preorder();j++) {
                CHECK_EQ(to_string(j), (*(it++)));
    }
    //check ++it
    for (auto it = o2.begin_preorder();;i++) {
        auto temp = ++it;
        if (it ==  o2.end_preorder()){
            break;
        }
        CHECK_EQ(to_string(i), *temp);

    }
}
TEST_CASE("reverse order test"){
    OrgChart o2;
    CHECK_THROWS(auto it = o2.begin_reverse_order()); //the root is nullptr
    o2.add_root("1").add_sub("1", "2").add_sub("1", "3").add_sub("2", "4")
    .add_sub("2", "5").add_sub("3", "6").add_sub("3", "7").add_sub("4", "8")
    .add_sub("4", "9").add_sub("5", "10").add_sub("5", "11").add_sub("6", "12")
    .add_sub("6", "13").add_sub("7", "14").add_sub("7", "15");
    vector<int> v1{8,9,10,11,12,13,14,15,4,5,6,7,2,3,1};
    size_t i = 0;
    for (auto it = o2.begin_reverse_order(); it != o2.reverse_order(); ++it,i++) {
                CHECK_EQ(to_string(v1.at(i)), (*it));
    }
}
