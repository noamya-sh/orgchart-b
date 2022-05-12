#ifndef ORGCHART_A_ORGCHART_H
#define ORGCHART_A_ORGCHART_H
#include <iostream>
#include <utility>
using namespace std;
namespace ariel{

    class OrgChart{
    private:
        struct Node {
            OrgChart& m_value;
            Node* m_next;
            Node(OrgChart  &v, Node* n)
                    : m_value(v), m_next(n) {
            }
        };
    public:
        OrgChart() : m_first(nullptr) {
        }

        OrgChart& add_root(string s);
        OrgChart* begin_level_order();
        OrgChart* end_level_order();
        OrgChart* begin_reverse_order();
        OrgChart* reverse_order();
        OrgChart* begin_preorder();
        OrgChart* end_preorder();
        friend ostream &operator<<(ostream &output, const OrgChart &orgChart);

        OrgChart& add_sub(string s1, string s2);
        Node* m_first;
        class iterator {

        private:
            Node* pointer_to_current_node;

        public:

            iterator(Node* ptr = nullptr)
                    : pointer_to_current_node(ptr) {
            }

            // Note that the method is const as this operator does not
            // allow changing of the iterator.
            // Note that it returns T& as it allows to change what it points to.
            // A const_iterator class will return const T&
            // and the method will still be const
            OrgChart& operator*() const {
                //return *pointer_to_current_node;
                return pointer_to_current_node->m_value;
            }

            OrgChart* operator->() const {
                return &(pointer_to_current_node->m_value);
            }

            // ++i;
            iterator& operator++() {
                //++pointer_to_current_node;
                pointer_to_current_node = pointer_to_current_node->m_next;
                return *this;
            }

            // i++;
            // Usually iterators are passed by value and not by const& as they are small.
            iterator operator++(int) {
                iterator tmp= *this;
                pointer_to_current_node= pointer_to_current_node->m_next;
                return tmp;
            }

            bool operator==(const iterator& rhs) const {
                return pointer_to_current_node == rhs.pointer_to_current_node;
            }

            bool operator!=(const iterator& rhs) const {
                return pointer_to_current_node != rhs.pointer_to_current_node;
            }
        };  // END OF CLASS ITERATOR
        iterator begin() const {
            // return &(m_first->m_value);
            return iterator{m_first};
        }
        static int* size() {
            // return nullptr;
            return 0;
        }
        static iterator end() {
            // return nullptr;
            return iterator{nullptr};
        }
    };
}
#endif //ORGCHART_A_ORGCHART_H
