#include <iostream>
#include <algorithm>
#include <cstring>

class String {
 public:
  String(){
    string_ = new char[1];
    cap = 0;
    size_ = 0;
    string_[0] = '\0';
  }

  String(const char* arg): string_(new char[strlen(arg) + 1]) {
    size_ = strlen(arg);
    cap = size_;
    std::copy(arg, arg + size_ + 1, string_);
  }

  String(const String& str): size_(str.size_), cap(str.cap), string_(new char[str.cap + 1]) {
    memcpy(string_, str.string_, size_ + 1);
  }

  String(size_t n, char c): size_(n), cap(n), string_(new char[n + 1]) {
    memset(string_, c, size_);
    string_[n] = '\0';
  }

  ~String() {
    delete[] string_;
  }

  void swap(String& s) {
    std::swap(size_, s.size_);
    std::swap(cap, s.cap);
    std::swap(string_, s.string_);
  }

  char* data() {
    return &string_[0];
  }

  const char* data() const {
    return &string_[0];
  }

  const char& front() const {
    return string_[0];
  }

  const char& back() const {
    return string_[size_ - 1];
  }

  char& front() {
    return string_[0];
  }

  char& back() {
    return string_[size_ - 1];
  }

  void push_back(char c) {
    if (size_ == cap) {
      remakingOfCapacity();
    }
    string_[size_] = c;
    string_[++size_] = '\0';
  }

  void pop_back() {
    string_[--size_] = '\0';
  }

  size_t length() const {
    return size_;
  }

  size_t size() const {
    return size_;
  }

  size_t capacity() const {
    return cap;
  }

  void shrink_to_fit() {
    char* buf_string = new char[size_ + 1];
    memcpy(buf_string, string_, size_ + 1);
    delete[] string_;
    cap = size_;
    string_ = buf_string;
  }


  bool empty() const {
    return size_ == 0;
  }

  void clear() {
    size_ = 0;
    string_[0] = '\0';
  }

  size_t find(const String& s) const{
    size_t result_index = length();
    if (s.size_ > size_) {
      return result_index;
    }
    bool is_substring = true;
    for (size_t i = 0; i < (size_ - s.size_ + 1); ++i) {
      is_substring = true;
      if (string_[i] == s.string_[0]) {
        for (size_t j = 1; j < s.size_; ++j) {
          if (s.string_[j] != string_[i + j]) {
            is_substring = false;
            break;
          }
        }
        if (is_substring) {
          return i;
        }
      }
    }
    return result_index;
  }

  size_t rfind(const String& s) const{
    size_t result_index = length();
    if (s.size_ > size_) {
      return result_index;
    }
    bool is_substring = true;
    for (size_t i = 0; i < (size_ - s.size_ + 1); ++i) {
      is_substring = true;
      if (string_[i] == s.string_[0]) {
        for (size_t j = 1; j < s.size_; ++j) {
          if (s.string_[j] != string_[i + j]) {
            is_substring = false;
            break;
          }
        }
        if (is_substring) {
          result_index = i;
        }
      }
    }
    return result_index;
  }

  String substr(size_t start, size_t count) const {
    String buffer_string = String(count, '\0');
    std::copy(string_ + start, string_ + start + count, buffer_string.string_);
    return buffer_string;
  }

  char& operator[](int val) {
    return string_[val];
  }

  const char& operator[](int val) const {
    return string_[val];
  }

  String& operator=(String s){
    swap(s);
    return *this;
  }


  String& operator=(const char* s){
    String buffer_string(s);
    swap(buffer_string);
    return *this;
  }

  String& operator+=(const String& s) {
    while ((size_ + s.size_) > cap) {
      cap *= 2;
    }
    char* buffer_array = new char[size_ + s.size_ + 1];
    std::copy(string_, string_ + size_, buffer_array);
    std::copy(s.string_, s.string_ + s.size_ + 1, buffer_array + size_);
    size_ += s.size_;
    //cap = size_;
    delete[] string_;
    string_ = buffer_array;
    return *this;
  }

  String& operator+=(char c) {
    this->push_back(c);
    return *this;
  }

 private:
  size_t size_ = 0;
  size_t cap = 0;
  char* string_ = nullptr;
  friend String operator+(const String& s1, const String& s2);
  friend String operator+(char c, const String& s2);
  friend String operator+(const String& s1, char c);
  friend bool operator==(const String& s1, const String& s2);
  friend bool operator>=(const String& s1, const String& s2);
  friend bool operator>(const String& s1, const String& s2);
  friend bool operator<=(const String& s1, const String& s2);
  friend bool operator<(const String& s1, const String& s2);
  friend std::ostream& operator<<(std::ostream& output, const String& s);
  friend std::istream& operator>>(std::istream& input, String& s);

  void remakingOfCapacity() {
    if (size_ == 0) {
      char* buf_string = new char[2];
      delete[] string_;
      buf_string[1] = '\0';
      string_ = buf_string;
      cap = 1;
    } else {
      char* buffer_array = new char[2*cap + 1];
      cap *= 2;
      std::copy(string_, string_ + size_ + 1, buffer_array);
      delete[] string_;
      string_ = buffer_array;
    }
  }
};

bool operator==(const String& s1, const String& s2) {
  if (s1.size_ != s2.size_) {
    return false;
  }
  for (size_t i = 0; i < s1.size_; ++i) {
    if (s1.string_[i] != s2.string_[i]) {
      return false;
    }
  }
  return true;
}

String operator+(char c, const String& s2) {
  String buf_string = String(1, c);
  buf_string += s2;
  return buf_string;
}

String operator+(const String& s1, char c) {
  String buf_string;
  buf_string.size_ = s1.size_ + 1;
  buf_string.string_ = new char[s1.size_ + 2];
  memcpy(buf_string.string_, s1.string_, s1.size_);
  buf_string.string_[s1.size_] = c;
  buf_string.string_[s1.size_ + 1] = '\0';
  return buf_string;
}

String operator+(const String& s1, const String& s2) {
  String buf_string = String(s2.string_);
  buf_string.size_ = s1.size_ + s2.size_;
  buf_string.cap = s1.cap + s2.cap;
  strcpy(buf_string.string_, s1.string_);
  strcat(buf_string.string_, s2.string_);
  buf_string.string_[buf_string.size_] = '\0';
  return buf_string;
}

bool operator>(const String& s1, const String& s2) {
  size_t sz =  s1.size_;
  for (size_t i = 0; i < sz; ++i) {
    if ((s1.string_[i] < s2.string_[i]) || (s2[i] == '\0')) {
      return false;
    }
  }
  return true;
}

bool operator<(const String& s1, const String& s2) {
  return (s2 > s1);
}

bool operator<=(const String& s1, const String& s2) {
  return !(s1 > s2);
}

bool operator>=(const String& s1, const String& s2) {
  return !(s1 < s2);
}

bool operator!=(const String& s1, const String& s2) {
  return !(s1 == s2);
}

std::ostream& operator<<(std::ostream& output, const String& s) {
  for (int i = 0;; ++i) {
    if (s[i] == '\0') {
      break;
    }
    output << s[i];
  }
  return output;
}

std::istream& operator>>(std::istream& input, String& s) {
  while (input.peek() != EOF && !std::isspace(input.peek())) {
    if (std::isspace(input.peek())) {
      input.ignore();
    } else {
      char c;
      input >> c;
      s.push_back(c);
    }
  }
  while (std::isspace(input.peek())) {
    input.ignore();
  }
  return input;
}
