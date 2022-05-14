#ifndef ORGCHART_A_ORGCHART_H
#define ORGCHART_A_ORGCHART_H
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
namespace ariel{

    class OrgChart{
    private:
        struct Node {
            string m_value;
            Node* m_next;
            Node(string &v, Node* n)
                    : m_value(v), m_next(n) {
            }
        };

    public:
        OrgChart() : m_first(nullptr) {
        }
        ~OrgChart(){
            delete m_first;
        }
        OrgChart& add_root(string s);
        friend ostream &operator<<(ostream &output, const OrgChart &orgChart);
        OrgChart& add_sub(string s1, string s2);
        Node* m_first;

        class iterator {

        private:
            Node* current;

        public:
            iterator(Node* ptr = nullptr)
                    : current(ptr) {
            }

            string& operator*() const {
                //return *current;
                return current->m_value;
            }

            string* operator->() const {
                return &(current->m_value);
            }

            // ++i;
            iterator& operator++() {
                //++current;
                current = current->m_next;
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            iterator operator++(int) {
                iterator tmp= *this;
                current= current->m_next;
                return tmp;
            }

            bool operator==(const iterator& it) const {
                return current == it.current;
            }

            bool operator!=(const iterator& it) const {
                return current != it.current;
            }
            size_t size(){
                return current->m_value.length();
            }
        };  // END OF CLASS ITERATOR
        iterator begin() const {
            // return &(m_first->m_value);
            return iterator{m_first};
        }
//        static int size() {
//            return 0;
//        }
        static iterator end() {
            // return nullptr;
            return iterator{nullptr};
        }
        iterator begin_level_order();
        iterator end_level_order();
        iterator begin_reverse_order();
        iterator reverse_order();
        iterator begin_preorder();
        iterator end_preorder();
    };
}
#endif //ORGCHART_A_ORGCHART_H
