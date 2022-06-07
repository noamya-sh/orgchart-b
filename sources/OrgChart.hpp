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
        int height;
        vector <Node*> boys;
        Node* father = nullptr;
        Node(string const &s,int h):value(s),height(h){}
    };
    class OrgChart{
    private:
        vector<Node*> toSearch;
        vector<Node*> levels;
        Node* root;
    public:

        Node* search(const string &s);
        OrgChart();
        OrgChart(OrgChart &o) = default;
        OrgChart(OrgChart &&o) = default ;
        OrgChart& operator=(const OrgChart& o) = default;
        OrgChart& operator=(OrgChart&& o) = default;
        ~OrgChart();
        OrgChart& add_root(const string &s);
        friend ostream &operator<<(ostream &output, OrgChart &orgChart);
        OrgChart& add_sub(const string &s1, const string &s2);


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
//            vector<Node*> rev;
            size_t idx_reverse = 0;
        public:
            int get_height() const{ return this->current->height;};
            queue<Node*> get_toLevel() const;
            void set_toReverseLevel(vector<Node*> vec);
            void set_idx_reverse(size_t x);
            size_t get_idx_reverse() const;
            void set_cur(Node *n);
            iterator(type_it t,Node* ptr = nullptr): type(t),current(ptr) {}
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
        iterator reverse_order();
        iterator begin_preorder();
        iterator end_preorder();
//        string get_father(string &boy);

    };
}
#endif //ORGCHART_A_ORGCHART_H
