#include <bits/stdc++.h>

class node{
    public:
        int value;      //value assigned to the node
        node* smaller;  //smaller child pointer
        node* bigger;   //bigger child pointer
        node* parent;   //parent pointer
        bool role;      //indicates whether the node is a bigger child
        
        /// @brief intialize node
        /// @param x value
        /// @param r role
        /// @param p parent
        node(int x, bool r = false, node* p = NULL){
            value = x;
            smaller = NULL;
            bigger = NULL;
            parent = p;
            role = r;
        }

};

class set{
    private:
        node* root; //root node
        int size;   //current size
        node* maximum; //pointer to maximum node
        node* minimum; //pointer to minimum node
    public:
        set(){
            size = 0;
            maximum = NULL;
            minimum = NULL;
        }
        /// @brief inserts value x into the set
        /// @param x 
        void insert(int x){
            if(size == 0){
                root = new node(x);
                maximum = root;
                minimum = root;
                size++;
                return;
            }
            node* cur = root;
            bool placed = false;
            while(!placed){
                if(x == (*cur).value) placed = true;
                if(x < (*cur).value){
                    if((*cur).smaller == NULL){
                        (*cur).smaller = new node(x, false, cur);
                        placed = true;
                        size++;
                        if(x < (*minimum).value) minimum = (*cur).smaller;
                    } else {
                        cur = (*cur).smaller;
                    }
                } else {
                    if((*cur).bigger == NULL){
                        (*cur).bigger = new node(x, true, cur);
                        placed = true;
                        size++;
                        if(x > (*maximum).value) maximum = (*cur).bigger;
                    } else {
                        cur = (*cur).bigger;
                    }
                }
            }
        }

        /// @brief deletes node with given value
        /// @param x 
        void erase(int x){
            node* target = find(x);
            if(target == NULL) return;
            if(maximum == target) maximum = (*target).parent; //updating the maximum value
            if(minimum == target) minimum = (*target).parent; //updating the minimum value
            node* cur = (*target).bigger;
            while((*cur).smaller != NULL) cur = (*cur).smaller; //finding a new place for the smaller branch
            (*cur).smaller = (*target).smaller;
            (*(*target).smaller).parent = cur;
            if((*(*target).parent).smaller == target){
                (*(*target).parent).smaller = (*target).bigger;
                (*(*target).bigger).parent = (*target).parent;
            } else {
                (*(*target).parent).bigger = (*target).bigger;
                (*(*target).bigger).parent = (*target).parent;
            }
            size--;
            delete(target);
        }

        /// @brief finds the node with value x
        /// @param x 
        /// @return returns pointer to the node if found, false if not found
        node* find(int x){
            node* cur = root;
            bool found = false;
            while(!found){
                if(cur == NULL) return cur;
                if(x == (*cur).value) found = true;
                if(x < (*cur).value) {
                    cur = (*cur).smaller;
                }else {
                    cur = (*cur).bigger;
                }
            }
            return cur;
        }

        /// @brief checks if x is contained in the set
        /// @param x 
        /// @return true if the set contains x, false otherwise
        bool contains(int x){
            node* cur = root;
            bool found = false;
            while(!found){
                if(cur == NULL) return false;
                if(x == (*cur).value) found = true;
                if(x < (*cur).value) {
                    cur = (*cur).smaller;
                }else {
                    cur = (*cur).bigger;
                }
            }
            return true;
        }

        /// @brief an input type iterator
        struct Iterator{
            using iterator_category = std::input_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = int;
            using pointer = node*;
            using reference = int&;

            Iterator(pointer ptr) : m_ptr(ptr) {}
            
            reference operator*() const {return (*m_ptr).value; }
            pointer operator->() {return m_ptr;}

            Iterator& operator++(){
                if((*m_ptr).bigger == NULL){
                    node* cur = (*m_ptr).parent;
                    bool prev = (*m_ptr).role;
                    if(!prev){
                        m_ptr = cur;
                        return *this;
                    } else {
                        while(prev){
                            prev = (*cur).role;
                            cur = (*cur).parent;
                        }
                        m_ptr = cur;
                        return *this;
                    }
                } else {
                    node* cur = (*m_ptr).bigger;
                    while((*cur).smaller != NULL){
                        cur = (*cur).smaller;
                    }
                    m_ptr = cur;
                    return *this;
                }
            }

            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

            private:
                pointer m_ptr;
        };

        int length(){ return size; }

        Iterator begin() { return Iterator(minimum);}
        Iterator end() {return Iterator(maximum);}
};

using namespace std::chrono;

int main(){
    int n, p; std::cin >> n >> p;
    std::vector<int> d;
    for(int j = 0; j < p; j++){
        set a;
        srand((unsigned)time(NULL));
        auto start = high_resolution_clock::now();
        for(int i = 0; i < n; i++){
            a.insert(rand()%n);
        }
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        d.push_back(duration.count());
    }
    int sum;
    for(int j = 0; j < (int)d.size(); j++){
        std::cout << "Test #" << j+1  << ": " << d[j] << '\n';
        sum += d[j];
    }
    std::cout << "Average duration: " << sum/p << '\n';
    return 0;
}