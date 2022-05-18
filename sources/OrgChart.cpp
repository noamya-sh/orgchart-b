#include "OrgChart.hpp"
#include <iostream>
#include <queue>
namespace ariel{
    OrgChart& OrgChart::add_root(string s) {
        this->root =new Node(s);
        this->root->value = s;
        this->toSearch.push_back(root);
        return *this;
    }

    ostream &operator<<(ostream &output, OrgChart &orgChart) {
        return output;
    }

    OrgChart& OrgChart::add_sub(string s1, string s2) {
        if (this->root == nullptr){
            throw runtime_error("no exist root");
        }
        Node *dad = search(s1);
        if (dad == nullptr){
            throw runtime_error("no exist father");
        }
        Node* temp = new Node(s2);
//        temp->value=s2;
        temp->father = dad;
        temp->height = dad->height+1;
        dad->boys.push_back(temp);
        this->toSearch.push_back(temp);
        return *this;
    }

    OrgChart::iterator OrgChart::begin_level_order() {
        iterator it = iterator(LEVEL, this->root);
        it.get_toLevel().push(this->root);
        return it;
    }

    OrgChart::iterator OrgChart::end_level_order() {
        iterator it = iterator(LEVEL, nullptr);
        return it;
    }

    OrgChart::iterator OrgChart::begin_reverse_order() {
        int max = -1;
        Node *n = nullptr;
        for (size_t i = 0; i < toSearch.size(); ++i) {
            if (toSearch[i]->height > max){
                max = toSearch[i]->height;
            }
        }
        size_t i = 0;
        for (; i < toSearch.size(); ++i) {
            if (toSearch[i]->height == max){
                n = toSearch[i];
                break;
            }
        }
        iterator it = iterator(REVERSE_LEVEL,n);
        it.set_idx_reverse(i);
        it.set_toReverseLevel(toSearch);
        return it;
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
    Node *OrgChart::search(string s) {
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

     Node *OrgChart::iterator::nextLevel() {

        for (Node *n:current->boys) {
//            cout << "PUSH:"  << n->value << endl;
            toLevel.push(n);
        }
        if (toLevel.empty()){
            return nullptr;
        }

        Node *n = toLevel.front();
         toLevel.pop();
//         cout << "POP:"  << n->value << endl;
        return n;
    }

    Node *OrgChart::iterator::nextPreorder() {
        if (!this->current->boys.empty()){
            return this->current->boys[0];
        }
        return getUncle(this->current);
    }

    Node *OrgChart::iterator::getUncle(Node *cur) {
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
    OrgChart::OrgChart() : root(){}
    OrgChart::~OrgChart() {
        for (Node *n:toSearch) {
            delete n;
        }
    }
    Node *OrgChart::iterator::nextReverseLevel() {
        for (size_t i = get_idx_reverse()+1; i < toReverseLevel.size(); ++i) {
            if (toReverseLevel[i]->height == this->current->height){
                set_idx_reverse(i);
                return toReverseLevel[i];
            }
        }
        for (size_t i = 0; i < toReverseLevel.size(); ++i) {
            if (toReverseLevel[i]->height == this->current->height-1){
                set_idx_reverse(i);
                return toReverseLevel[i];
            }
        }
        return nullptr;
    }

    OrgChart::iterator &OrgChart::iterator::operator++() {
        //++current;
        if (type == LEVEL){
            this->current = nextLevel();
        }
        else if (type == REVERSE_LEVEL){
            this->current = nextReverseLevel();
        }
        else{
            this->current = nextPreorder();
        }
        return *this;
    }

    OrgChart::iterator OrgChart::iterator::operator++(int){
            iterator tmp= *this;
            ++*this;
            return tmp;
    }

    OrgChart::OrgChart(OrgChart &o) {
        this->root = o.root;
        this->toSearch = o.toSearch;
    }

    queue<Node *> OrgChart::iterator::get_toLevel() {
        return this->toLevel;
    }

    void OrgChart::iterator::set_idx_reverse(size_t x) {
        this->idx_reverse = x;
    }

    size_t OrgChart::iterator::get_idx_reverse() const {
        return this->idx_reverse;
    }



    void OrgChart::iterator::set_toReverseLevel(vector<Node *> vec) {
        this->toReverseLevel = vec;
    }

    OrgChart &OrgChart::operator=(const OrgChart &o) {
        this->root = o.root;
        this->toSearch = o.toSearch;
        return *this;
    }

    OrgChart::OrgChart(OrgChart &&o) noexcept {
        this->root = o.root;
        this->toSearch = o.toSearch;
    }

    OrgChart &OrgChart::operator=(OrgChart &&o) noexcept{
        this->root = o.root;
        this->toSearch = o.toSearch;
        return *this;
    }
}

