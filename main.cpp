#include <cstddef>
#include <utility>
#include <stdexcept>

template <typename T>
class Vector {
    
public:
    Vector() noexcept
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
    int size() const noexcept {
        return m_size;
    }
    
    int capacity() const noexcept {
        return m_capacity;
    }
    
    bool empty() const noexcept {
        return m_size == 0;
    }
    
    void reserve(int newCap) {
        if (newCap <= m_capacity) return;
        if (newCap < 0) {
            throw std::invalid_argument("negative capacity");
        }
        reallocate(newCap);
    }
    
    void shrink_to_fit() {
        if (m_capacity == m_size) return;
        if (m_size == 0) {
            delete[] m_data;
            m_data = nullptr;
            m_capacity = 0;
            return;
        }
        T* newData = new T[m_size];
        for (int i = 0; i < m_size; i++) {
            newData[i] = m_data[i];
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = m_size;
    }
    
    T& operator[](int index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("index is out of range");
        }
        return m_data[index];
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("index is out of range");
        }
        return m_data[index];
    }
    
    T& at(int index) {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("error: index is out of range");
        }
        return m_data[index];
    }
    
    const T& at(int index) const {
        if (index < 0 || index >= m_size) {
            throw std::out_of_range("error: index is out of range");
        }
        return m_data[index];
    }
    
    T& front() {
        if (m_size == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return m_data[0];
    }
    
    const T& front() const {
        if (m_size == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return m_data[0];
    }
    
    T& back() {
        if (m_size == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return m_data[m_size - 1];
    }
    
    const T& back() const {
        if (m_size == 0) {
            throw std::out_of_range("Vector is empty");
        }
        return m_data[m_size - 1];
    }
    
    T* data() noexcept {
        return m_data;
    }
    
    const T* data() const noexcept {
        return m_data;
    }
    
    void clear() noexcept {
        m_size = 0;
    }
    
    void push_back(const T& val) {
        grow_if_needed();
        m_data[m_size] = val;
        m_size++;
    }
    
    void push_back(T&& val) {
        grow_if_needed();
        m_data[m_size] = std::move(val);
        m_size++;
    }
    
    void pop_back() {
        if (m_size == 0) {
            throw std::out_of_range("error: vector is empty");
        }
        m_size--;
    }
    
    void resize(int newSize) {
        if (newSize == m_size) return;
        if (newSize < 0) {
            throw std::invalid_argument("negative size");
        }
        if (newSize < m_size) {
            m_size = newSize;
        } else if (newSize > m_size) {
            if (newSize > m_capacity) {
                reserve(newSize);
            }
            for (int i = m_size; i < newSize; i++) {
                m_data[i] = T();
            }
            m_size = newSize;
        }
    }
    
    void resize(int newSize, const T& val) {
        if (newSize == m_size) return;
        if (newSize < 0) {
            throw std::invalid_argument("negative size");
        }
        if (newSize < m_size) {
            m_size = newSize;
        } else if (newSize > m_size) {
            if (newSize > m_capacity) {
                reserve(newSize);
            }
            for (int i = m_size; i < newSize; i++) {
                m_data[i] = val;
            }
            m_size = newSize;
        }
    }
    
    void swap(Vector& other) noexcept {
        std::swap(m_size, other.m_size);
        std::swap(m_capacity, other.m_capacity);
        std::swap(m_data, other.m_data);
    }
    
private:
    int m_size;
    int m_capacity;
    T* m_data;

    void grow_if_needed() {
        if (m_size == m_capacity) {
            int newCap;
            if (m_capacity == 0) {
                newCap = 1;
            } else {
                newCap = m_capacity * 2;
            }
            reserve(newCap);
        }
    }

    void reallocate(int newCap) {
        T* newData = new T[newCap];
        for (int i = 0; i < m_size; i++) {
            newData[i] = std::move(m_data[i]);
        }
        delete[] m_data;
        m_data = newData;
        m_capacity = newCap;
    }
};