#include <iostream>
#include <bits/stdc++.h>

int* binary_search(int* start, int* end, int value){
    if(start == end){
        return NULL;
    }
    int size = end-start;
    int mid = size/2;
    int s = *(start+mid);
    if(s == value){
        return start+mid;
    }else if(s < value){
        return binary_search((start+mid+1), end, value);
    } else {
        return binary_search(start, start+mid-1, value);
    }
}

int* binary_search2(int* start, int* end, int value){
    if(start+1 == end || start == NULL){
        return start;
    }
    int size = std::distance(start,end);
    int mid = (size)/2;
    int s = *(start+mid);
    if(s == value){
        return start+mid;
    }
    if(s < value){
        return binary_search2((start+mid+1), end, value);
    } else {
        return binary_search2(start, start+mid-1, value);
    }
}

class set{
    private:
        int* space;
        int size;
    public:
        set(){
            size = 0;
            space = NULL;
        }
        int* find(int x){
            int* pos = binary_search(space, space+size, x);
            if(pos == NULL){
                return space+size;
            } else {
                return pos;
            }
        }
        void insert(int x) {
            int *pos = lower_bound(x);
            if(pos == NULL || *pos != x){
                int* inter = (int*)malloc(sizeof(int)*(size+1));
                for(int i = 0; i < pos-space;i++) inter[i] = space[i];
                inter[pos-space] = x;
                for(int i = pos-space+1; i < size+1;i++) inter[i] = space[i-1];
                free(space);
                space = inter;
                size++;
            }
        }
        void erase(int x){
            int* pos = find(x);
            if(pos != space+size){
                int* inter = (int*)malloc(sizeof(int)*(size-1));
                for(int i = 0; i < pos-space;i++) inter[i] = space[i];
                for(int i = pos-space+1; i < size;i++) inter[i-1] = space[i];
                free(space);
                space = inter;
                size--;
            }
        }
        int* lower_bound(int x){
            int* pos = binary_search2(space, space+size, x);
            return pos;
        }
        int* begin() {return space;}
        int* end() {return space+size;}
        int length() {return size;}
};

void printset(int* start, int* end){
    for(int* i = start; i != end; i++){
        std:: cout << *i << " ";
    }
    std::cout << '\n';
}

int main(){
    set a;
    a.insert(1);
    for(int i = 0;i < 20;i++){
        std::cout << binary_search2(a.begin(), a.end(), i)-a.begin() << '\n';
        a.insert(i);
        printset(a.begin(), a.end());
    }
    return 0;
}