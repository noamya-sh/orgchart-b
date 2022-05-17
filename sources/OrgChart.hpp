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
    class OrgChart{
    private:
        struct Node {
            string value;
            vector <Node*> boys;
            Node* father = nullptr;
        };

        vector<Node*> toSearch;

    public:
        Node* search(string s);
        OrgChart();
        ~OrgChart();
        OrgChart& add_root(string s);
        friend ostream &operator<<(ostream &output, const OrgChart &orgChart);
        OrgChart& add_sub(string s1, string s2);
        Node* root;
        Node* last;

        class iterator {

        private:
            Node* current;
            type_it type = LEVEL;


        public:
            queue<Node*> toLevel;
            Node *nextLevel();
            Node *nextPreorder();
            Node *nextReverseLevel();
            Node *getUncle(Node* cur);
            iterator(type_it t,Node* ptr = nullptr)
                    : type(t),current(ptr) {
            }

            string& operator*() const {
                return current->value;
            }

            string* operator->() const {
                return &(current->value);
            }

            // ++i;
            iterator& operator++() {
                //++current;
                if (type == LEVEL){
                    this->current = nextLevel();
                }
                else if (type == REVERSE_LEVEL){
                }
                else{
                    this->current = nextPreorder();
                }
//                current = current->m_next;
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            iterator operator++(int) {
                iterator tmp= *this;
//                current= current->m_next;
                return tmp;
            }

            bool operator==(const iterator& it) const {
                return current == it.current;
            }

            bool operator!=(const iterator& it) const {
                return current != it.current;
            }
            size_t size(){
                return current->value.length();
            }
        };  // END OF CLASS ITERATOR
        iterator begin() {
            return begin_level_order();
        }
        iterator end() {
            return end_level_order();
        }
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
