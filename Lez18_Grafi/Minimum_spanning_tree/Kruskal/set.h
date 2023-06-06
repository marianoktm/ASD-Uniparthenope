#ifndef ASD_SET_H
#define ASD_SET_H

#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

template<class T> class set_element;
template<class T> class set_header;
template<class T> class set_pool;


/** SET ELEMENT **/
template<class T> class set_element {
private:
    T data;
    set_header<T> * header;
    set_element<T> * next = nullptr;

public:
    set_element() = default;
    explicit set_element(T newdata): data(newdata) {}
    set_element(T newdata, set_header<T> * newheader): data(newdata), header(newheader) {}

    void setElementData(T newdata) { this->data = newdata; }
    T getElementData() { return this->data; }

    void setElementHeader(set_header<T> * newheader) { this-> header = newheader; }
    set_header<T> * getElementHeader() { return this->header; }

    void setElementNext(set_element<T> * newnext) { this->next = newnext; }
    set_element<T> * getElementNext() { return this->next; }
};


/** SET HEADER **/
template<class T> class set_header {
private:
    int rank = 0;
    set_element<T> * head = nullptr;
    set_element<T> * tail = nullptr;

public:
    set_header() = default;
    explicit set_header(set_element<T> * singleelement) { this->head = singleelement; this->tail = singleelement; }
    set_header(set_element<T> * newhead, set_element<T> * newtail, int newrank): head(newhead), tail(newtail), rank(newrank) {}

    void setHeaderRank(int newrank) { this->rank = newrank; }
    int getHeaderRank() { return this->rank; }

    void setHeaderHead(set_element<T> * newhead) { this->head = newhead; }
    set_element<T> * getHeaderHead() { return this->head; }

    void setHeaderTail(set_element<T> * newtail) { this->tail = newtail; }
    set_element<T> * getHeaderTail() { return this->tail; }

    bool operator==(set_header & comp) const { return rank == comp.rank and head == comp.head and tail == comp.tail; }
    bool operator!=(set_header & comp) const { return !(this == comp); }
};


/** SET POOL CLASS **/
template<class T> class set_pool {
private:
    unordered_map<T, set_element<T> *> data_to_element_map;
    unordered_map<set_element<T> *, T> element_to_data_map;

    void concatenate_set_lists(set_header<T> * x_header_right, set_header<T> * y_header_left) {
        set_element<T> * y_head = y_header_left->getHeaderHead();
        set_element<T> * x_tail = x_header_right->getHeaderTail();
        set_element<T> * y_tail = y_header_left->getHeaderTail();

        x_tail->setElementNext(y_head);
        x_header_right->setHeaderTail(y_tail);
    }

    void change_list_header(set_header<T> * x_header_new, set_header<T> * y_header_old) {
        set_element<T> * curr = y_header_old->getHeaderHead();
        while (curr != nullptr) {
            curr->setElementHeader(x_header_new);
            curr = curr->getElementNext();
        }
    }

public:
    /// Make Set Function
    void make_set(T data) {
        set_element<T> * new_element = new set_element<T>(data);
        set_header<T> * new_header = new set_header<T>(new_element);
        new_element->setElementHeader(new_header);

        data_to_element_map[data] = new_element;
        element_to_data_map[new_element] = data;
    }

    /// Find Set Function
    set_header<T> * find_set(T data) {
        set_element<T> * element = data_to_element_map[data];
        return element->getElementHeader();
    }

    /// Link Function
    void link_set(set_header<T> * x_header, set_header<T> * y_header) {
        set_element<T> * x_head = x_header->getHeaderHead();
        set_element<T> * y_head = y_header->getHeaderHead();
        set_element<T> * x_tail = x_header->getHeaderTail();
        set_element<T> * y_tail = y_header->getHeaderTail();
        int x_rank = x_header->getHeaderRank();
        int y_rank = y_header->getHeaderRank();

        if (x_rank > y_rank) {
            change_list_header(x_header, y_header);
            concatenate_set_lists(x_header, y_header);
            delete y_header;
        }
        else {
            change_list_header(y_header, x_header);
            concatenate_set_lists(y_header, x_header);
            if (x_rank == y_rank) {
                y_header->setHeaderRank(y_rank + 1);
            }
            delete x_header;
        }
    }

    /// Union Function
    void union_set(T x_data, T y_data) {
        link_set(find_set(x_data), find_set(y_data));
    }

    /// Print Pool
    void print_pool() {
        for (auto & elem : data_to_element_map) {
            cout << "[" << elem.first << "] ";
        }
        cout << endl;
    }

    /// Print Set
    void print_set(T data) {
        set_header<T> * header = find_set(data);
        set_element<T> * curr = header->getHeaderHead();
        while (curr != nullptr) {
            cout << "[" << curr->getElementData() << "] ";
            curr = curr->getElementNext();
        }
        cout << endl;
    }
};

#endif //ASD_SET_H
