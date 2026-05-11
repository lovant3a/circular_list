#ifndef CIRCULAR_LIST_HPP
#define CIRCULAR_LIST_HPP

template <typename T>
void CircularList<T>::check_not_empty() const {
    if (sz == 0) {
        throw ListException(101);
    }
}

template <typename T>
void CircularList<T>::destroy_all() {
    if (sz == 0) return;
    Node* ptr = current;
    for (std::size_t i = 0; i < sz; ++i) {
        Node* tmp = ptr->next;
        delete ptr;
        ptr = tmp;
    }
    current = nullptr;
    sz = 0;
}

// конструкторы и деструктор 
template <typename T>
CircularList<T>::CircularList() : current(nullptr), sz(0) {}

template <typename T>
CircularList<T>::CircularList(const CircularList& other) : current(nullptr), sz(0) {
    if (other.sz == 0) return;

    Node* src = other.current;
    Node* last = nullptr;
    for (std::size_t i = 0; i < other.sz; ++i) {
        Node* new_node = new Node(src->data);
        if (sz == 0) current = new_node;
        else { last->next = new_node; new_node->prev = last; }
        last = new_node;
        src = src->next;
        ++sz;
    }
    if (last) {
        last->next = current;
        current->prev = last;
    }
}

template <typename T>
CircularList<T>::CircularList(CircularList&& other) noexcept
    : current(other.current), sz(other.sz) {
    other.current = nullptr;
    other.sz = 0;
}

template <typename T>
CircularList<T>::~CircularList() {
    destroy_all();
}

// присваивание
template <typename T>
CircularList<T>& CircularList<T>::operator=(const CircularList& other) {
    if (this != &other) {
        destroy_all();
        if (other.sz == 0) return *this;

        Node* src = other.current;
        Node* last = nullptr;
        for (std::size_t i = 0; i < other.sz; ++i) {
            Node* new_node = new Node(src->data);
            if (sz == 0) current = new_node;
            else { last->next = new_node; new_node->prev = last; }
            last = new_node;
            src = src->next;
            ++sz;
        }
        if (last) { last->next = current; current->prev = last; }
    }
    return *this;
}

template <typename T>
CircularList<T>& CircularList<T>::operator=(CircularList&& other) noexcept {
    if (this != &other) {
        destroy_all();
        current = other.current;
        sz = other.sz;
        other.current = nullptr;
        other.sz = 0;
    }
    return *this;
}

// вставка (копия)
template <typename T>
void CircularList<T>::insert_before(const T& val) {
    Node* nd = new Node(val);
    if (sz == 0) {
        current = nd; nd->next = nd; nd->prev = nd;
    }
    else {
        Node* pr = current->prev;
        pr->next = nd; nd->prev = pr;
        nd->next = current; current->prev = nd;
    }
    ++sz;
}

template <typename T>
void CircularList<T>::insert_after(const T& val) {
    Node* nd = new Node(val);
    if (sz == 0) {
        current = nd; nd->next = nd; nd->prev = nd;
    }
    else {
        Node* nx = current->next;
        current->next = nd; nd->prev = current;
        nd->next = nx; nx->prev = nd;
    }
    ++sz;
}

// вставка (перемещение)
template <typename T>
void CircularList<T>::insert_before(T&& val) {
    Node* nd = new Node(std::move(val));
    if (sz == 0) {
        current = nd; nd->next = nd; nd->prev = nd;
    }
    else {
        Node* pr = current->prev;
        pr->next = nd; nd->prev = pr;
        nd->next = current; current->prev = nd;
    }
    ++sz;
}

template <typename T>
void CircularList<T>::insert_after(T&& val) {
    Node* nd = new Node(std::move(val));
    if (sz == 0) {
        current = nd; nd->next = nd; nd->prev = nd;
    }
    else {
        Node* nx = current->next;
        current->next = nd; nd->prev = current;
        nd->next = nx; nx->prev = nd;
    }
    ++sz;
}

// удаление и навигация 
template <typename T>
void CircularList<T>::remove_current() {
    check_not_empty();
    if (sz == 1) {
        delete current;
        current = nullptr;
        sz = 0;
        return;
    }
    Node* pr = current->prev;
    Node* nx = current->next;
    pr->next = nx; nx->prev = pr;
    delete current;
    current = nx;
    --sz;
}

template <typename T>
void CircularList<T>::next() {
    check_not_empty();
    current = current->next;
}

template <typename T>
void CircularList<T>::prev() {
    check_not_empty();
    current = current->prev;
}

template <typename T>
T* CircularList<T>::get() {
    check_not_empty();
    return &(current->data);
}

template <typename T>
const T* CircularList<T>::get() const {
    check_not_empty();
    return &(current->data);
}

// вывод
template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularList<T>& list) {
    if (list.empty()) {
        os << "[пустой список]";
        return os;
    }
    os << "[ ";
    auto* ptr = list.current;
    for (std::size_t i = 0; i < list.sz; ++i) {
        os << ptr->data;
        ptr = ptr->next;
        if (i < list.sz - 1) os << ", ";
    }
    os << " ] (тек: " << list.current->data << ")";
    return os;
}

#endif 