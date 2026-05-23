#ifndef CIRCULAR_LIST_H
#define CIRCULAR_LIST_H

#include <iostream>
#include <string>
#include <cstddef>
#include <utility>

// исключение с кодом ошибки
class ListException : public std::exception {
    int code_;
    std::string message;

    std::string getCodeMessage(int code) const {
        switch (code) {
        case 101: return "список пуст";
        case 102: return "неверный индекс";
        case 103: return "ошибка ввода";
        case 104: return "элемент не найден";
        default:  return "неизвестная ошибка";
        }
    }

public:
    ListException(int code) : code_(code), message(getCodeMessage(code)) {}
    const char* what() const noexcept override { return message.c_str(); }
    int getCode() const { return code_; }
};

template <typename T>
class CircularList {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& v) : data(v), prev(nullptr), next(nullptr) {}
        Node(T&& v) : data(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    Node* current;
    std::size_t sz;

    void check_not_empty() const;
    void destroy_all();

public:
    CircularList();
    CircularList(const CircularList& other);
    CircularList(CircularList&& other) noexcept;
    CircularList clone() const;
    ~CircularList();

    CircularList& operator=(const CircularList& other);
    CircularList& operator=(CircularList&& other) noexcept;

    void insert_before(const T& val);
    void insert_before(T&& val);
    void insert_after(const T& val);
    void insert_after(T&& val);
    void remove_current();

    void next();
    void prev();

    T* get();
    const T* get() const;

    std::size_t size() const { return sz; }
    bool empty() const { return sz == 0; }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const CircularList<U>& list);
};

#include "circular_list.hpp"

#endif 
