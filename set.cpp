#include <bits/stdc++.h>


//using a version of binary search to find
//the first element position bigger or equal to the value.
//equivalnt to a lower_bound function
int* binary_search(int* start, int* end, int value){
    if(start > end){
        return NULL;
    }
    if(start == end){
        return start;
    }
    int length = std::distance(start,end);
    int mid = (length)/2;
    int s = *(start+mid);
    if(s == value){
        return start+mid;
    }
    if(s < value){
        return binary_search((start+mid+1), end, value);
    } else {
        return binary_search(start, start+mid, value);
    }
}

class set{
    private:
        int* space; //pointer to the start of the array
        int length; //length of the array
    public:
        set(){
            length = 0;
            space = NULL;
        }

        /// @brief finds the position of given value in the set
        /// @param x value to be found
        /// @return pointer to the found element or end pointer if not found
        int* find(int x){
            int* pos = binary_search(space, space+length, x);
            if(pos == NULL || *pos != x){
                return space+length;
            } else {
                return pos;
            }
        }

        /// @brief insert the given value into the set
        /// @param x value to be inserted
        void insert(int x) {
            int *pos = lower_bound(x);
            if(pos == NULL){ //if the value has to be ended at the end
                int* inter = (int*)malloc(sizeof(int)*(length+1));
                for(int i = 0; i < length;i++) inter[i] = space[i];
                inter[length] = x;
                free(space);
                space = inter;
                length++;
            } else if(*pos != x){ //all other cases
                int* inter = (int*)malloc(sizeof(int)*(length+1));
                for(int i = 0; i < (pos-space);i++) inter[i] = space[i];
                inter[pos-space] = x;
                for(int i = pos-space+1; i < length+1;i++) inter[i] = space[i-1];
                free(space);
                space = inter;
                length++;
            }
        }

        /// @brief erases the given value from the set
        /// @param x value to be erased
        void erase(int x){
            int* pos = find(x);
            if(pos != space+length){
                int* inter = (int*)malloc(sizeof(int)*(length-1));
                for(int i = 0; i < pos-space;i++) inter[i] = space[i];
                for(int i = pos-space+1; i < length;i++) inter[i-1] = space[i];
                free(space);
                space = inter;
                length--;
            }
        }

        /// @brief find the first element not smaller than given value
        /// @return return the pointer to the position of the first element that satifies the condition
        int* lower_bound(int x){
            int* pos = binary_search(space, space+length, x);
            return pos;
        }
        
        /// @brief number of elements in the set
        int size() {return length;}
        
        ~set(){
            free(space);
        }

        /// @brief simple input iterator
        struct Iterator{
            using iterator_category = std::input_iterator_tag;
            using difference_type = std::ptrdiff_t;
            using value_type = int;
            using pointer = int*;
            using reference = int&;

            Iterator(pointer ptr) : m_ptr(ptr) {}
            
            reference operator*() const {return (*m_ptr); }
            pointer operator->() {return m_ptr;}

            Iterator& operator++(){
                m_ptr = m_ptr+1;
                return *this;
            }

            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

            private:
                pointer m_ptr;
        };

        Iterator begin() {return space; };
        Iterator end() {return space+length; };
};

void printset(int* start, int* end){
    for(int* i = start; i != end; i++){
        std:: cout << *i << " ";
    }
    std::cout << '\n';
}

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
        //std::cout << "Test #" << j+1  << ": " << d[j] << '\n';
        sum += d[j];
    }
    std::cout << "Average duration: " << sum/p << '\n';
    return 0;
}