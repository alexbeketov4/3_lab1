#pragma once
template <typename T>
class UnqPtr
{
private:
    T* ptr;

public:

    UnqPtr() : ptr(nullptr) {}

    explicit UnqPtr(T* p) : ptr(p) {}

    UnqPtr(UnqPtr<T>&& other) noexcept : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    UnqPtr<T>& operator=(UnqPtr<T>&& other) noexcept
    {
        if (this != &other)
        {
            delete ptr;
            ptr = other.ptr;
            other.ptr = nullptr;
        }
        return *this;
    }

    UnqPtr(const UnqPtr<T>&) = delete;
    UnqPtr<T>& operator=(const UnqPtr<T>&) = delete;

    ~UnqPtr()
    {
        delete ptr;
    }

    const T& operator*() const
    {
        if (!ptr) throw "Dereferencing a null pointer";
        return *ptr;
    }

    const T* operator->() const
    {
        return ptr;
    }

    T& operator*()
    {
        if (!ptr) throw "Dereferencing a null pointer";
        return *ptr;
    }

    T* operator->()
    {
        return ptr;
    }

    operator bool() const
    {
        return ptr != nullptr;
    }

    bool operator!() const
    {
        return ptr == nullptr;
    }

    void release()
    {
        delete ptr;
        ptr = nullptr;
    }

    void reset(T* p = nullptr)
    {
        if (ptr != p)
        {
            delete ptr;
            ptr = p;
        }
    }

    T* get() const
    {
        return ptr;
    }
};
