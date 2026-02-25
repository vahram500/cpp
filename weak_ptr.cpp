#include <iostream>

struct ControlBlock {
    std::size_t* count;
    void* ptr;
};

template <typename T>
class SharedPtr {
private:
    T* m_ptr;
    ControlBlock* m_control;
};
