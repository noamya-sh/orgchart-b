#include "OrgChart.hpp"
#include <iostream>

namespace ariel{
    //Check that the input is correct in the add_root and add_sub functions
    void check_arg(const string &s){
        if (s.empty()){
            throw runtime_error("the arg is empty!");
        }
        for (char ch:s){
            if (ch == '\n' || ch == '\r' || ch =='\t'){
                throw invalid_argument("Invalid characters");
            }
        }
    }
    OrgChart& OrgChart::add_root(const string &s) {
        check_arg(s);
        // if exist root - replace his name
        if (this->root != nullptr){
            this->root->value = s;
        }
        else{ //if not exist root:
            this->root =new Node(s,0);
        }
        return *this;
    }

    ostream &operator<<(ostream &output, OrgChart &orgChart) {
        int level = 0;
        if (orgChart.root != nullptr){
            output << level << ":";
        }
        for (auto it = orgChart.begin(); it != orgChart.end(); ++it)
        {
            auto const &cur = it;
            // if start new level - add \n
            if (cur.get_height() !=level) {
                output << "\n" << cur.get_height() << ":";
            }
            level = cur.get_height();
            output << " " << *cur;
        }

        return output;
    }

    OrgChart& OrgChart::add_sub(const string &s1, const string &s2) {
        check_arg(s1);
        check_arg(s2);
        if (this->root == nullptr){
            throw runtime_error("no exist root");
        }
        //search the father of new node
        Node *father = search(s1);
        if (father == nullptr){
            throw runtime_error("no exist father");
        }
        Node* child = new Node(s2,father->height+1);
        child->father = father;
        father->boys.push_back(child);
        return *this;
    }

    OrgChart::iterator OrgChart::begin_level_order() {
        if (this->root == nullptr){
            throw runtime_error("orgchart empty");
        }
        iterator it = iterator(LEVEL, this->root);
        it.get_toLevel().push(this->root);
        return it;
    }

    OrgChart::iterator OrgChart::end_level_order() {
        if (this->root == nullptr){
            throw runtime_error("orgchart empty");
        }
        iterator it = iterator(LEVEL, nullptr);
        return it;
    }

    OrgChart::iterator OrgChart::begin_reverse_order() {
        if (this->root == nullptr){
            throw runtime_error("orgchart empty");
        }
        iterator it = iterator(REVERSE_LEVEL);
        vector<Node*> reverse;
        queue<Node*> q;
        q.push(this->root);
        vector<Node *> temp;
        while (!q.empty()){
            size_t size = q.size();
            for (int i = 0; i < size; ++i) {
                Node *n = q.front();
                q.pop();
                // push to index 0
                temp.insert(temp.begin(),n);
                //push all boys
                for (unsigned int j = 0; j < n->boys.size(); ++j) {
                    q.push(n->boys[j]);
                }
            }
                for (Node *n:temp ){
                    reverse.insert(reverse.begin(),n);
                }
                temp.clear();
        }
        it.set_toReverseLevel(reverse);
        if (!reverse.empty()){ //init current node
            it.set_cur(reverse.at(0));
        }
        return it;
    }

    OrgChart::iterator OrgChart::reverse_order() {
        if (this->root == nullptr){
            throw runtime_error("orgchart empty");
        }
        return OrgChart::iterator(REVERSE_LEVEL);
    }

    OrgChart::iterator OrgChart::begin_preorder() {
        if (this->root == nullptr){
            throw runtime_error("orgchart empty");
        }
        return iterator(PREORDER,this->root);
    }

    OrgChart::iterator OrgChart::end_preorder() {
        if (this->root == nullptr){
            throw runtime_error("orgchart empty");
        }
        return iterator(PREORDER, nullptr);
    }

    Node *OrgChart::search(string const &s) {
        queue<Node *> queue;
        queue.push(root);
        while(!queue.empty()){
            Node *n = queue.front();
            if (n->value == s){
                return n;
            }
            queue.pop();
            for (size_t i = 0; i < n->boys.size(); ++i) {
                queue.push(n->boys.at(i));
            }
        }
        return nullptr;
    }

     Node *OrgChart::iterator::nextLevel() {

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

    Node *OrgChart::iterator::nextPreorder() {
        //if exists boys - get first boy
        if (!this->current->boys.empty()){
            return this->current->boys[0];
        }
        // go to uncle - next
        return getUncle(this->current);
    }

    Node *OrgChart::iterator::getUncle(Node *cur) {
        if (cur->father != nullptr){
            size_t i = 0;
            //find index in boys vector
            for (; i < cur->father->boys.size(); ++i) {
                if (cur->father->boys.at(i) == cur){
                    break;
                }
            }
            // if this last boy
            if (i == cur->father->boys.size()-1){
                return getUncle(cur->father);
            }
            // get next boy
            return cur->father->boys.at(i + 1);
        }
        return nullptr;
    }
    OrgChart::OrgChart() : root(){}
    OrgChart::~OrgChart() {
        queue<Node *> queue;
        queue.push(root);
        while(!queue.empty()){
            Node *n = queue.front();
            queue.pop();
            for (size_t i = 0; i < n->boys.size(); ++i) {
                queue.push(n->boys.at(i));
            }
            delete n;
        }
    }
    Node *OrgChart::iterator::nextReverseLevel() {
        this->idx_reverse++;
        if (idx_reverse >= toReverseLevel.size()){
            return nullptr;
        }
        return this->toReverseLevel.at(idx_reverse);
    }
    //++iterator
    OrgChart::iterator &OrgChart::iterator::operator++() {

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
    //iterator++
    OrgChart::iterator OrgChart::iterator::operator++(int){
            iterator tmp= *this;
            ++*this;
            return tmp;
    }

    queue<Node *> OrgChart::iterator::get_toLevel() const{
        return this->toLevel;
    }

    void OrgChart::iterator::set_idx_reverse(size_t x) {
        this->idx_reverse = x;
    }

    size_t OrgChart::iterator::get_idx_reverse() const {
        return this->idx_reverse;
    }
    void OrgChart::iterator::set_toReverseLevel(vector<Node *> vec) {
        this->toReverseLevel = move(vec);
    }

    void OrgChart::iterator::set_cur(Node *n) {
        this->current = n;
    }
}

