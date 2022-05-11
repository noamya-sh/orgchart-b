#include "OrgChart.hpp"
namespace ariel{
    OrgChart& OrgChart::add_root(string s) {
        return *this;
    }

    ostream &operator<<(ostream &output, const OrgChart &orgChart) {
        return output;
    }

    OrgChart& OrgChart::add_sub(string s1, string s2) {
        return *this;
    }


    OrgChart *OrgChart::end_level_order() {
        return nullptr;
    }

    OrgChart *OrgChart::begin_preorder() {
        return nullptr;
    }

    OrgChart *OrgChart::end_preorder() {
        return nullptr;
    }

    OrgChart *OrgChart::reverse_order() {
        return nullptr;
    }

    OrgChart *OrgChart::begin_reverse_order() {
        return nullptr;
    }

    OrgChart *OrgChart::begin_level_order() {
        return nullptr;
    }
}

