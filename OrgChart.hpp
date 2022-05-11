#ifndef ORGCHART_A_ORGCHART_H
#define ORGCHART_A_ORGCHART_H
#include <iostream>
using namespace std;
namespace ariel{
    class OrgChart{
    public:
        void add_root(string s);
        void sub_root(string s1,string s2);
        friend ostream &operator<<(ostream &output, const OrgChart &orgChart);

    };
}
#endif //ORGCHART_A_ORGCHART_H
