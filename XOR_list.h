#include "iostream"
#include "vector"
#include "list"

template<class T>
struct Item {
    T data;
    Item *npx;
};

template<class T>
class XOR_list {
private:
    Item<T> *_head;
    int _size;

    Item<T> *XOR(Item<T> *a, Item<T> *b);

    void browsing(void(*something)(Item<T> *, Item<T> *, Item<T> *));

public:

    XOR_list();

    explicit XOR_list(const std::vector<T> &other);

    XOR_list(const std::initializer_list<T> &other);

    ~XOR_list();

    void insert(T data);

    T front();

    T back();

    int size();

    void print();

    void clear();

    bool empty();
};

template<class T>

void XOR_list<T>::browsing(void(*something)(Item<T> *, Item<T> *, Item<T> *)) {
    Item<T> *curr = _head;
    Item<T> *prev = nullptr;
    Item<T> *next;

    while (curr != nullptr) {

        next = XOR(prev, curr->npx);

        something(curr, prev, next);

        prev = curr;
        curr = next;
    }
}

template<class T>
XOR_list<T>::XOR_list() {
    _size = 0;
    _head = nullptr;
}

template<class T>
XOR_list<T>::XOR_list(const std::vector<T> &other):XOR_list() {
    for (int i = 0; i < other.size(); i++) {
        insert(other[i]);
    }
}

template<class T>
XOR_list<T>::XOR_list(const std::initializer_list<T> &other):XOR_list((std::vector<T>) other) {}

template<class T>
XOR_list<T>::~XOR_list() {
    clear();
}

template<class T>
Item<T> *XOR_list<T>::XOR(Item<T> *a, Item<T> *b) {
    return reinterpret_cast<Item<T> *>(
            reinterpret_cast<uintptr_t>(a) ^
            reinterpret_cast<uintptr_t>(b));
}

template<class T>
void XOR_list<T>::insert(T data) {
    auto *newItem = new Item<T>();
    newItem->data = data;
    newItem->npx = _head;

    if (_head != nullptr) {
        _head->npx = XOR(newItem, _head->npx);
    }

    _head = newItem;
    _size++;
}

template<class T>
T XOR_list<T>::front() {
    return _head->data;
}

template<class T>
T XOR_list<T>::back() {
    Item<T> *curr = _head;
    Item<T> *prev = nullptr;
    Item<T> *next;

    while (curr != nullptr) {

        next = XOR(prev, curr->npx);

        if (next == nullptr) {
            return curr->data;
        }

        prev = curr;
        curr = next;
    }
}

template<class T>
int XOR_list<T>::size() {
    return _size;
}

template<class T>
void XOR_list<T>::print() {
    browsing([](Item<T> *curr, Item<T> *prev, Item<T> *next) {
        std::cout << curr->data << std::endl;
    });
}

template<class T>
bool XOR_list<T>::empty() {
    return _head == nullptr;
}

template<class T>
void XOR_list<T>::clear() {
    browsing([](Item<T> *curr, Item<T> *prev, Item<T> *next) {
        delete prev;
        if (next == nullptr)
            delete curr;
    });
    _size = 0;
}