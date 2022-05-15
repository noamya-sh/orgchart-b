#include "OrgChart.hpp"
#include <queue>
namespace ariel{

    OrgChart& OrgChart::add_root(string s) {
        root = new Node(s);
        this->toSearch.push_back(root);
        return *this;
    }

    ostream &operator<<(ostream &output, const OrgChart &orgChart) {
        return output;
    }

    OrgChart& OrgChart::add_sub(string s1, string s2) {
        Node *f = search(s1);
        if (f == nullptr){
            throw runtime_error("no exist father");
        }
        Node *b = new Node(s2);
        b->father = f;
        f->boys.push_back(b);
        return *this;
    }

    OrgChart::iterator OrgChart::begin_level_order() {
        return OrgChart::iterator(LEVEL);
    }

    OrgChart::iterator OrgChart::end_level_order() {
        iterator it = OrgChart::iterator(LEVEL);

        return it;
    }

    OrgChart::iterator OrgChart::begin_reverse_order() {
        return OrgChart::iterator(REVERSE_LEVEL);
    }

    OrgChart::iterator OrgChart::end_reverse_order() {
        return OrgChart::iterator(REVERSE_LEVEL);
    }

    OrgChart::iterator OrgChart::begin_preorder() {
        return OrgChart::iterator(PREORDER);
    }

    OrgChart::iterator OrgChart::end_preorder() {
        return OrgChart::iterator(PREORDER);
    }

    void OrgChart::bfs() {
        vector<string> vec;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()){
            Node* n = q.front();
            vec.push_back(n->value);
            //for: all nodes descents
            q.pop();
        }
    }

    OrgChart::Node *OrgChart::search(string s) {
        for (Node *n:toSearch) {
            if (n->value == s){
                return n;
            }
        }
        return nullptr;
    }

    string OrgChart::get_father(string &boy) {
        Node *n = search(boy);
        if (n == nullptr){
            throw runtime_error("no exist this input");
        }
        if (n==root){
            return "this root";
        }
        return n->father->value;
    }
}

