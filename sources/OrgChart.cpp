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

    OrgChart::iterator OrgChart::begin_level_order() {
        return OrgChart::iterator();
    }

    OrgChart::iterator OrgChart::end_level_order() {
        return OrgChart::iterator();
    }

    OrgChart::iterator OrgChart::begin_reverse_order() {
        return OrgChart::iterator();
    }

    OrgChart::iterator OrgChart::reverse_order() {
        return OrgChart::iterator();
    }

    OrgChart::iterator OrgChart::begin_preorder() {
        return OrgChart::iterator();
    }

    OrgChart::iterator OrgChart::end_preorder() {
        return OrgChart::iterator();
    }
}

