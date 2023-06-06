#ifndef ASD_MIN_PRIORITY_QUEUE_H
#define ASD_MIN_PRIORITY_QUEUE_H

#include <vector>

using namespace std;

template<class T> class min_heap {
protected:
    vector<T> A;
    int heapsize = 0;

public:
    min_heap() = default;
    explicit min_heap(vector<T> new_A) {
        cout << "new min heap created" << endl;
        A = new_A;
        build_min_heap();
    }

    int left(int i) { return (2*i) + 1; }
    int right(int i) { return (2*i) + 2; }
    int parent(int i) { return (i-1) / 2;}

    void min_heapify(int i) {
        int min = i;
        int l = left(i);
        int r = right(i);

        if (l < heapsize and A.at(l) < A.at(min)) {
            min = l;
        }
        if (r < heapsize and A.at(r) < A.at(min)) {
            min = r;
        }
        if (min != i) {
            swap(A.at(i), A.at(min));
            min_heapify(min);
        }
    }

    void build_min_heap() {
        this->heapsize = A.size();
        for (int i = heapsize/2 - 1; i >= 0; i--) {
            min_heapify(i);
        }
    }

    void insert(T to_insert) {
        this->A.push_back(to_insert);
        this->heapsize++;
        if (this->heapsize > 1)
            this->min_heapify(0);
    }
};

template<class T> class min_priority_queue: public min_heap<T> {
public:
    min_priority_queue() = default;
    explicit min_priority_queue(vector<T> new_A): min_heap<T>(new_A) {
        cout << "new min priority queue created" << endl;
    }

    bool is_empty() {
        return this->A.empty();
    }

    T get_min() {
        return this->A.at(0);
    }

    T extract_min() {
        T min = get_min();
        swap(this->A.at(0), this->A.at(this->heapsize-1));
        this->heapsize--;
        this->min_heapify(0);
        this->A.pop_back();
        return min;
    }

    void decrease_key() {
        if (this->heapsize > 1)
            this->min_heapify(this->heapsize - 1);
    }
};


#endif //ASD_MIN_PRIORITY_QUEUE_H
