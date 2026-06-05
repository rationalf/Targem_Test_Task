#pragma once
#include <cstddef>

class String {
public:
    String();
    String(const char* source);
    String(const String& other);
    String(String&& other) noexcept;
    ~String();

    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;
    String& operator=(const char* source);

    String& operator+=(const String& other);
    String& operator+=(const char* source);

    char& operator[](size_t index);
    const char& operator[](size_t index) const;

    const char* c_str()  const;
    size_t size()   const;
    size_t length() const;
    bool empty()  const;

    int compare(const String& other) const;
    int compare(const char* other)   const;

private:
    char*  data_;
    size_t size_;
    size_t capacity_;

    void assign(const char* source, size_t length);
    void ensure_capacity(size_t required_capacity);
};

bool operator==(const String& left, const String& right);
bool operator!=(const String& left, const String& right);
bool operator<(const String& left,  const String& right);
bool operator>(const String& left,  const String& right);
bool operator<=(const String& left, const String& right);
bool operator>=(const String& left, const String& right);

String operator+(const String& left, const String& right);
String operator+(const String& left, const char*   right);
String operator+(const char*   left, const String& right);
