#include <iostream>
#include <exception>

template <typename T>
class Vector {
    
public:
    Vector() 
    : m_size(0) 
    , m_capacity(0) 
    , m_data(nullptr) {}
    
    Vector(int size, int capacity, T* data) 
    : m_size(size) 
    , m_capacity(capacity) {
        m_data = new T[m_capacity];
        for (int i = 0; i < m_size; i++) {
            m_data[i] = data[i];
        }
    }
    
    Vector(const Vector& other) 
    : m_size(other.m_size) 
    , m_capacity(other.m_capacity) {
        m_data = new T[m_capacity];
        for (int i = 0; i < m_size; i++) {
            m_data[i] = other.m_data[i];
        }
    }
    
    Vector(Vector&& other) noexcept {
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        m_data = other.m_data;
        other.m_size = 0;
        other.m_capacity = 0;
        other.m_data = nullptr;
    }
     
    Vector& operator=(const Vector& other) {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = new T[m_capacity];
            for (int i = 0; i < m_size; i++) {
                m_data[i] = other.m_data[i];
            }
        }
        return *this;
    }
    
    Vector& operator=(Vector&& other) noexcept {
        if (this != &other) {
            delete[] m_data;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_data = other.m_data;
            other.m_size = 0;
            other.m_capacity = 0;
            other.m_data = nullptr;
        }
        return *this;
    }
     
    ~Vector() {
        delete[] m_data;
        m_data = nullptr;
    }
    
public:
    int size() const {
        return m_size;
    }
    
    int capacity() const {
        return m_capacity;
    }
    
    bool empty() const {
        return m_size == 0;
    }
    
    void reserve(int newCap) {
        if (newCap <= m_capacity) return;
        if (newCap < 0) {
            throw std::invalid_argument("error: negative capacity");
        }
        T* newData = new T[newCap];
        for (int i = 0; i < m_size; i++) {
            newData[i] = m_data[i];
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = newCap;
    }
    
    void push_back(T val) {
        if (m_size == m_capacity) {
            int newCap;
            if (m_capacity == 0) {
                newCap = 1;
            } else {
                newCap = m_capacity * 2;
            }
            T* newData = new T[newCap];
            for (int i = 0; i < m_size; i++) {
                newData[i] = m_data[i];
            }
            delete[] m_data;
            m_data = newData;
            m_capacity = newCap;
        }
        m_data[m_size] = val;
        m_size++;
    }
    
    void pop_back() {
        if (m_size == 0) {
            throw std::out_of_range("error: vector is empty");
        }
        m_size--;
    }
    
    T& at(int index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("error: index is out of range");
        }
        return m_data[index];
    }
    
private:
    int m_size;
    int m_capacity;
    T* m_data;
};

int main() {
    
    return 0;
}