#ifndef ASD_MIN_PRIORITY_QUEUE_H
#define ASD_MIN_PRIORITY_QUEUE_H

#include <algorithm>
#include <vector>
#include <iostream>
#include <functional>

using namespace std;

template<class T> class min_priority_queue {
private:
    vector<T> vctr;

public:
    explicit min_priority_queue(vector<T> new_vctr): vctr(new_vctr) {
        make_heap(vctr.begin(), vctr.end(), greater<T>());
        print();
    }

    void print(){
        cout << "Queue: " << endl;
        for (auto elem : vctr) {
            cout << *elem << "  ";
        }
        cout << endl;
    }

    void insert(T to_insert) {
        vctr.push_back(to_insert);
        push_heap(vctr.begin(), vctr.end(), greater<T>());
    }

    T get_min() {
        return vctr.front();
    }

    T extract_min() {
        auto min = vctr.front();
        pop_heap(vctr.begin(), vctr.end());
        vctr.pop_back();
        return min;
    }

    void re_heap() {
        make_heap(vctr.begin(), vctr.end(), greater<T>());
    }

    bool empty() {
        return vctr.empty();
    }
};


#endif //ASD_MIN_PRIORITY_QUEUE_H
