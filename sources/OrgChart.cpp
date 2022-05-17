#include "OrgChart.hpp"
#include <iostream>
#include <queue>
namespace ariel{
    OrgChart& OrgChart::add_root(string s) {
        this->root =new Node();
        this->root->value = s;
        this->toSearch.push_back(root);

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
        k->boys.push_back(temp);
        this->toSearch.push_back(temp);
        return *this;
    }

    OrgChart::iterator OrgChart::begin_level_order() {
        iterator it = iterator(LEVEL, this->root);
        it.toLevel.push(this->root);
        return it;
    }

    OrgChart::iterator OrgChart::end_level_order() {
        iterator it = iterator(LEVEL, nullptr);
        return it;
    }

    OrgChart::iterator OrgChart::begin_reverse_order() {
        return OrgChart::iterator(REVERSE_LEVEL);
    }

    OrgChart::iterator OrgChart::end_reverse_order() {
        return OrgChart::iterator(REVERSE_LEVEL);
    }

    OrgChart::iterator OrgChart::begin_preorder() {
        return iterator(PREORDER,this->root);
    }

    OrgChart::iterator OrgChart::end_preorder() {
        return iterator(PREORDER, nullptr);
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
//            cout << "enter to q:" << n->value << endl;
            toLevel.push(n);
        }
        if (toLevel.empty()){
            return nullptr;
        }
        toLevel.pop();
        Node *n = toLevel.front();
//        cout << "return from q:" << n->value<<endl;

        return n;
    }

    OrgChart::Node *OrgChart::iterator::nextPreorder() {
        if (!this->current->boys.empty()){
            return this->current->boys.at(0);
        }
        return getUncle(this->current);
    }

    OrgChart::Node *OrgChart::iterator::getUncle(Node *cur) {
        if (cur->father != nullptr){
            size_t i = 0;
            for (; i < cur->father->boys.size(); ++i) {
                if (cur->father->boys[i] == cur){
                    break;
                }
            }
            if (i == cur->father->boys.size()-1){
                return getUncle(cur->father);
            }
            return cur->father->boys[i+1];
        } else {
            return nullptr;
        }
    }
}

