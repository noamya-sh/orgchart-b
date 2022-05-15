#ifndef ORGCHART_A_ORGCHART_H
#define ORGCHART_A_ORGCHART_H
#include <iostream>
#include <utility>
#include <vector>

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
            Node* father;
            Node(string &v)
                    : value(v){
            }
        };
        Node* search(string s);
        vector<Node*> toSearch;

    public:
        OrgChart() : root(nullptr) {}
        ~OrgChart(){
            for (Node *n:toSearch) {
                delete n;
            }
        }
        OrgChart& add_root(string s);
        friend ostream &operator<<(ostream &output, const OrgChart &orgChart);
        OrgChart& add_sub(string s1, string s2);
        Node* root;
        void bfs();
        class iterator {

        private:
            Node* current;
            type_it type = LEVEL;

        public:
            iterator(type_it t,Node* ptr = nullptr)
                    : type(t),current(ptr) {
            }

            string& operator*() const {
                //return *current;
                return current->value;
            }

            string* operator->() const {
                return &(current->value);
            }

            // ++i;
            iterator& operator++() {
                //++current;
                if (type == LEVEL){}
                else if (type == REVERSE_LEVEL){
                }
                else{}
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
//        iterator begin() const {
//            // return &(root->value);
//            return iterator{LEVEL,root};
//        }
//        static iterator end() {
//            // return nullptr;
//            return iterator{LEVEL,nullptr};
//        }
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
