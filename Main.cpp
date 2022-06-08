
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "sources/OrgChart.hpp"
using namespace ariel;

int main() {
    const int stop = 0,root =1,sub=2,level=3,reverse=4,preorder=5,example=6;
    OrgChart organization;
    int mode;
    while(1){
        cout << "Please choose from the following options:\n"
                "0 - stop main           | 1 - add/replace root\n"
                "2 - add sub             | 3 - print level order\n"
                "4 - print reverse order | 5 - print preorder\n"
                "6 - init exemple" << endl;
        cin >> mode;
        if (mode == stop) break;
        if (mode == root) {
            string s;
            cout << "please insert name of new root." << endl;
            cin >> s;
            try{
                organization.add_root(s);
            }
            catch (exception &ex){
                cout << ex.what() << endl;
            }
            continue;
        }
        if (mode == sub) {
            string father,child;
            cout << "please insert name of father." << endl;
            cin >> father;
            cout << "please insert name of new child." << endl;
            cin >> child;
            try{
                organization.add_sub(father,child);
            }
            catch (exception &ex){
                cout << ex.what() << endl;
            }
            continue;
        }
        if (mode == level) {
            try{
                for (const string& element: organization) {
                    cout << element << " ";
                }
                cout << endl;
            }
            catch (exception &ex){
                cout << ex.what() << endl;
            }
            continue;
        }
        if (mode == reverse) {
            try {
                for (auto it = organization.begin_reverse_order(); it != organization.reverse_order(); ++it) {
                    cout << (*it) << " ";
                }
                cout << endl;
            }
            catch (exception &ex){
                cout << ex.what() << endl;
            }
            continue;
        }
        if (mode == preorder) {
            try {
                for (auto it = organization.begin_preorder(); it != organization.end_preorder(); ++it) {
                    cout << (*it) << " ";
                }
                cout << endl;
            }
            catch (exception &ex){
                cout << ex.what() << endl;
            }
            continue;
        }
        if (mode == example){
            organization.add_root("AAA")
                    .add_sub("AAA", "BBB")         // Now the BBB is subordinate to the AAA
                    .add_sub("AAA", "CCC")         // Now the CCC is subordinate to the AAA
                    .add_sub("AAA", "DDD")         // Now the DDD is subordinate to the AAA
                    .add_sub("BBB", "EE") // Now the EE is subordinate to the BBB
                    .add_sub("DDD", "FF");      // Now the FF is subordinate to the DDD
            continue;
        }
    }
}

