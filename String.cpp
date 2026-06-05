#include "String.h"
#include <cstring>
#include <cstdlib>
#include <new>
#include <stdexcept>

void String::ensure_capacity(size_t required_capacity) {
    if (required_capacity <= capacity_) return;
    size_t new_capacity = capacity_ ? capacity_ * 2 : 1;
    if (new_capacity < required_capacity) new_capacity = required_capacity;
    char* new_data = static_cast<char*>(realloc(data_, new_capacity));
    if (!new_data) throw std::bad_alloc();
    data_     = new_data;
    capacity_ = new_capacity;
}

void String::assign(const char* source, size_t length) {
    ensure_capacity(length + 1);
    if (source) memcpy(data_, source, length);
    data_[length] = '\0';
    size_ = length;
}


String::String() : data_(nullptr), size_(0), capacity_(0) {
    ensure_capacity(1);
    data_[0] = '\0';
}

String::String(const char* source) : data_(nullptr), size_(0), capacity_(0) {
    size_t length = source ? strlen(source) : 0;
    ensure_capacity(length + 1);
    if (source) memcpy(data_, source, length);
    data_[length] = '\0';
    size_ = length;
}

String::String(const String& other) : data_(nullptr), size_(0), capacity_(0) {
    assign(other.data_, other.size_);
}

String::String(String&& other) noexcept
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
    other.data_ = nullptr;
    other.size_ = 0;
    other.capacity_ = 0;
}

String::~String() {
    free(data_);
}


String& String::operator=(const String& other) {
    if (this != &other)
        assign(other.data_, other.size_);
    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (this != &other) {
        free(data_);
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    return *this;
}

String& String::operator=(const char* source) {
    size_t length = source ? strlen(source) : 0;
    assign(source, length);
    return *this;
}


String& String::operator+=(const String& other) {
    ensure_capacity(size_ + other.size_ + 1);
    memcpy(data_ + size_, other.data_, other.size_ + 1); // copies '\0' too
    size_ += other.size_;
    return *this;
}

String& String::operator+=(const char* source) {
    if (!source || !*source) return *this;
    size_t length = strlen(source);
    ensure_capacity(size_ + length + 1);
    memcpy(data_ + size_, source, length + 1);
    size_ += length;
    return *this;
}


char& String::operator[](size_t index) {
    if (index >= size_) {
        throw std::out_of_range("String index out of bounds");
    }
    return data_[index];
}

const char& String::operator[](size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("String index out of bounds");
    }
    return data_[index];
}

const char* String::c_str()  const { return data_ ? data_ : ""; }
size_t      String::size()   const { return size_; }
size_t      String::length() const { return size_; }
bool        String::empty()  const { return size_ == 0; }


int String::compare(const String& other) const { return strcmp(c_str(), other.c_str()); }
int String::compare(const char*   other) const { return strcmp(c_str(), other ? other : ""); }

bool operator==(const String& left, const String& right) { return left.compare(right) == 0; }
bool operator!=(const String& left, const String& right) { return left.compare(right) != 0; }
bool operator< (const String& left, const String& right) { return left.compare(right) <  0; }
bool operator> (const String& left, const String& right) { return left.compare(right) >  0; }
bool operator<=(const String& left, const String& right) { return left.compare(right) <= 0; }
bool operator>=(const String& left, const String& right) { return left.compare(right) >= 0; }


String operator+(const String& left, const String& right) { String result(left); result += right; return result; }
String operator+(const String& left, const char*   right) { String result(left); result += right; return result; }
String operator+(const char*   left, const String& right) { String result(left); result += right; return result; }
