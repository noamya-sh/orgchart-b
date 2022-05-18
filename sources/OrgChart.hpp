#ifndef ORGCHART_A_ORGCHART_H
#define ORGCHART_A_ORGCHART_H
#include <iostream>
#include <utility>
#include <vector>
#include <queue>
using namespace std;
namespace ariel{
    enum type_it{
        LEVEL,REVERSE_LEVEL,PREORDER
    };
    struct Node {
        string value;
        vector <Node*> boys;
        Node* father = nullptr;
        Node* next_brother = nullptr;
        int height = 0;
        size_t id = 0;
        Node(string &s):value(s){
        }
    };
    class OrgChart{
    private:

        vector<Node*> toSearch;
        vector<Node*> levels;
        Node* root;
//        size_t find_brother(unsigned int height,Node *dad);
    public:

        Node* search(string s);
        OrgChart();
        OrgChart(OrgChart &o);
        OrgChart(OrgChart &&o) noexcept ;
        OrgChart& operator=(const OrgChart& o);
        OrgChart& operator=(OrgChart&& o) noexcept;
        ~OrgChart();
        OrgChart& add_root(string s);
        friend ostream &operator<<(ostream &output, OrgChart &orgChart);
        OrgChart& add_sub(string s1, string s2);


        class iterator {

        private:
            Node* current;
            type_it type = LEVEL;
            Node *getUncle(Node* cur);
            Node *nextLevel();
            Node *nextPreorder();
            Node *nextReverseLevel();
            queue<Node*> toLevel;
            vector<Node*> toReverseLevel;
            size_t idx_reverse = 0;
        public:
            queue<Node*> get_toLevel();
            void set_toReverseLevel(vector<Node*> vec);
            void set_idx_reverse(size_t x);
            size_t get_idx_reverse() const;

            iterator(type_it t,Node* ptr = nullptr)
                    : type(t),current(ptr) {
            }

            string& operator*() const {return current->value;}
            string* operator->() const {return &(current->value);}

            // ++i;
            iterator& operator++();
            // i++;
            iterator operator++(int);
            bool operator==(const iterator& it) const {return current == it.current;}
            bool operator!=(const iterator& it) const {return current != it.current;}
            size_t size(){return current->value.length();}
        };  // END OF CLASS ITERATOR

        iterator begin() {return begin_level_order();}
        iterator end() {return end_level_order();}
        iterator begin_level_order();
        iterator end_level_order();
        iterator begin_reverse_order();
        iterator end_reverse_order();
        iterator begin_preorder();
        iterator end_preorder();
        string get_father(string &boy);

    };
}
#endif //ORGCHART_A_ORGCHART_H
