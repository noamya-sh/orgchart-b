#include "OrgChart.hpp"
#include <iostream>
#include <queue>
namespace ariel{
    OrgChart& OrgChart::add_root(string s) {
        this->root =new Node();
        this->root->value = s;
        this->toSearch.push_back(root);
        this->last = this->root;
//        cout << this->root->value << endl;
        return *this;
    }

    ostream &operator<<(ostream &output, const OrgChart &orgChart) {

        return output;
    }

    OrgChart& OrgChart::add_sub(string s1, string s2) {
        Node *k = search(s1);
        if (k == nullptr){
            throw runtime_error("no exist father");
        }
        Node* temp = new Node();
        temp->value=s2;
        temp->father = k;
        this->last =temp;
        k->boys.push_back(temp);
        this->toSearch.push_back(temp);
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

//    void OrgChart::bfs() {
//        vector<string> vec;
//        queue<Node*> q;
//        q.push(root);
//        while (!q.empty()){
//            Node* n = q.front();
//            vec.push_back(n->value);
//            //for: all nodes descents
//            q.pop();
//        }
//    }

    OrgChart::Node *OrgChart::search(string s) {
        for (Node *n: this->toSearch) {
            if (n->value == s){
                return n;
            }
        }
        return nullptr;
    }

//    string OrgChart::get_father(string &boy) {
//        Node *n = search(boy);
//        if (n == nullptr){
//            throw runtime_error("no exist this input");
//        }
////        if (n==root){
////            return "this root";
////        }
//        return n->father->value;
//    }

    OrgChart::Node *OrgChart::iterator::nextLevel() {
        for (Node *n:current->boys) {
            toLevel.push(n);
        }
        if (toLevel.empty()){
            return nullptr;
        }
        Node *n = toLevel.front();
        toLevel.pop();
        return n;
    }
}

