//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup shared_ref
 *  \brief Shared reference definition.
 */

#pragma once

#include <memory>


// OBJECTS
// -------


template <typename T>
class shared_ref
{
protected:
    std::shared_ptr<T> ptr;

public:
    typedef T element_type;

    shared_ref() = delete;
    shared_ref(const shared_ref<T>&) = default;
    shared_ref<T> & operator=(const shared_ref<T>&) = default;
    shared_ref(shared_ref<T> &&other);
    shared_ref<T> & operator=(shared_ref<T> &&other);

    template <typename... Ts>
    shared_ref(Ts&&... ts);

    long use_count() const;
    bool unique() const;

    T & get() const;
    operator T&() const;
    T & operator*() const;
    T * operator->() const;

    void swap(shared_ref<T> &other);
};


// IMPLEMENTATION
// --------------


template <typename T>
shared_ref<T>::shared_ref(shared_ref<T> &&other):
    ptr(std::make_shared<T>())
{
    swap(other);
}


template <typename T>
shared_ref<T> & shared_ref<T>::operator=(shared_ref<T> &&other)
{
    swap(other);
    return *this;
}


template <typename T>
template <typename... Ts>
shared_ref<T>::shared_ref(Ts&&... ts):
    ptr(std::make_shared<T>(std::forward<Ts>(ts)...))
{}


template <typename T>
long shared_ref<T>::use_count() const
{
    return ptr.use_count();
}


template <typename T>
bool shared_ref<T>::unique() const
{
    return ptr.unique();
}


template <typename T>
T & shared_ref<T>::get() const
{
    return *ptr;
}


template <typename T>
shared_ref<T>::operator T&() const
{
    return get();
}


template <typename T>
T & shared_ref<T>::operator*() const
{
    return get();
}


template <typename T>
T * shared_ref<T>::operator->() const
{
    return ptr.get();
}


template <typename T>
void shared_ref<T>::swap(shared_ref<T> &other)
{
    ptr.swap(other.ptr);
}
