#include "OrgChart.hpp"
#include <iostream>

namespace ariel{
    /*Check that the input is correct in the add_root and add_sub functions*/
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
            this->toSearch.push_back(root);
        }
        return *this;
    }

    ostream &operator<<(ostream &output, OrgChart &orgChart) {
        int last_level = 0;
        for (auto it = orgChart.begin(); it != orgChart.end(); ++it)
        {
            auto cur = it;
            if (cur.get_height() !=last_level) {
                output << "\n";
            }
            last_level = cur.get_height();
            output << " " << *cur << " ";
        }

        return output;
//        auto it = orgChart.begin_preorder();
//        while (it != orgChart.end_preorder()){
//            output << " ->" << (*it++);
//
//        }
//        return output << endl;
    }

    OrgChart& OrgChart::add_sub(const string &s1, const string &s2) {
        check_arg(s1);
        check_arg(s2);
        if (this->root == nullptr){
            throw runtime_error("no exist root");
        }
        //search the father of new node
        Node *dad = search(s1);
        if (dad == nullptr){
            throw runtime_error("no exist father");
        }
        Node* temp = new Node(s2,dad->height+1);
        temp->father = dad;
        dad->boys.push_back(temp);
        this->toSearch.push_back(temp);
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
//        int max = -1;
//        Node *n = nullptr;
//        for (size_t i = 0; i < toSearch.size(); ++i) {
//            if (toSearch[i]->height > max){
//                max = toSearch[i]->height;
//            }
//        }
//        size_t i = 0;
//        for (; i < toSearch.size(); ++i) {
//            if (toSearch[i]->height == max){
//                n = toSearch[i];
//                break;
//            }
//        }
//        iterator it = iterator(REVERSE_LEVEL,n);
//        it.set_idx_reverse(i);
//        it.set_toReverseLevel(toSearch);
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
                temp.insert(temp.begin(),n);
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
        if (!reverse.empty()){
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
        for (Node *n: this->toSearch) {
            if (n->value == s){
                return n;
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
        if (!this->current->boys.empty()){
            return this->current->boys[0];
        }
        return getUncle(this->current);
    }

    Node *OrgChart::iterator::getUncle(Node *cur) {
        if (cur->father != nullptr){
            size_t i = 0;
            for (; i < cur->father->boys.size(); ++i) {
                if (cur->father->boys.at(i) == cur){
                    break;
                }
            }
            if (i == cur->father->boys.size()-1){
                return getUncle(cur->father);
            }
            return cur->father->boys.at(i + 1);
        }
        return nullptr;
    }
    OrgChart::OrgChart() : root(){}
    OrgChart::~OrgChart() {
        for (Node *n:toSearch) {
            delete n;
        }
    }
    Node *OrgChart::iterator::nextReverseLevel() {
//        for (size_t i = get_idx_reverse()+1; i < toReverseLevel.size(); ++i) {
//            if (toReverseLevel[i]->height == this->current->height){
//                set_idx_reverse(i);
//                return toReverseLevel[i];
//            }
//        }
//        for (size_t i = 0; i < toReverseLevel.size(); ++i) {
//            if (toReverseLevel[i]->height == this->current->height-1){
//                set_idx_reverse(i);
//                return toReverseLevel[i];
//            }
//        }
//        cout << "I here" << endl;
//        for (unsigned int i = 0; i < toReverseLevel.size(); ++i) {
//            cout << i << ": " << toReverseLevel[i]->value << endl;
//        }
        this->idx_reverse++;
        if (idx_reverse >= toReverseLevel.size()){
            return nullptr;
        }
        return this->toReverseLevel.at(idx_reverse);
//        catch(const exception& e){
//            return nullptr;
//        }
//        return nullptr;
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

