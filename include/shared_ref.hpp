//  :copyright: (c) 2016-2017 The Regents of the University of California.
//  :license: MIT, see LICENSE.md for more details.
/**
 *  \addtogroup shared_ref
 *  \brief Shared reference definition.
 */

#pragma once

#include <cassert>
#include <memory>


namespace ref
{
// MACROS
// ------

#define CHECK_NULLPTR(x)                                                \
    assert(bool(x) && "Pointer cannot be null.");


// OBJECTS
// -------


template <typename T>
class shared_ref
{
protected:
    std::shared_ptr<T> ptr_;

public:
    typedef T element_type;

    shared_ref() = delete;
    shared_ref(const shared_ref<T>&) = default;
    shared_ref<T> & operator=(const shared_ref<T>&) = default;
    shared_ref(shared_ref<T> &&other);
    shared_ref<T> & operator=(shared_ref<T> &&other);

    template <typename Y>
    shared_ref(Y *ptr);

    template <typename Y, typename Deleter>
    shared_ref(Y *ptr, Deleter d);

    template <typename Y, typename Deleter, typename Alloc>
    shared_ref(Y *ptr, Deleter d, Alloc alloc);

    shared_ref(const std::shared_ptr<T> &ptr);

    template <typename Y>
    shared_ref(const std::shared_ptr<Y> &ptr);

    shared_ref(std::shared_ptr<T> &&ptr);

    template <typename Y>
    shared_ref(std::shared_ptr<Y> &&ptr);

    shared_ref<T> & operator=(const std::shared_ptr<T> &ptr);

    template <typename Y>
    shared_ref<T> & operator=(const std::shared_ptr<Y> &ptr);

    shared_ref<T> & operator=(std::shared_ptr<T> &&ptr);

    template <typename Y>
    shared_ref<T> & operator=(std::shared_ptr<Y> &&ptr);

    long use_count() const;
    bool unique() const;

    T & get() const;
    std::shared_ptr<T> ptr() const;
    operator T&() const;
    T & operator*() const;
    T * operator->() const;

    void swap(shared_ref<T> &other);

    template <typename Archive>
    void serialize(Archive & archive,
        const uint32_t version);
};


// FUNCTIONS
// ---------


template <typename T, typename... Ts>
shared_ref<T> make_shared(Ts&&... ts)
{
    return shared_ref<T>(std::make_shared<T>(std::forward<Ts>(ts)...));
}


// IMPLEMENTATION
// --------------


template <typename T>
template <typename Y>
shared_ref<T>::shared_ref(Y *ptr)
{
    CHECK_NULLPTR(ptr);
    ptr_.reset(ptr);
}


template <typename T>
template <typename Y, typename Deleter>
shared_ref<T>::shared_ref(Y *ptr, Deleter d)
{
    CHECK_NULLPTR(ptr);
    ptr_.reset(ptr, d);
}


template <typename T>
template <typename Y, typename Deleter, typename Alloc>
shared_ref<T>::shared_ref(Y *ptr, Deleter d, Alloc alloc)
{
    CHECK_NULLPTR(ptr);
    ptr_.reset(ptr, d, alloc);
}

template <typename T>
shared_ref<T>::shared_ref(const std::shared_ptr<T> &ptr)
{
    CHECK_NULLPTR(ptr);
    ptr_ = ptr;
}

template <typename T>
template <typename Y>
shared_ref<T>::shared_ref(const std::shared_ptr<Y> &ptr)
{
    CHECK_NULLPTR(ptr);
    ptr_ = ptr;
}

template <typename T>
shared_ref<T>::shared_ref(std::shared_ptr<T> &&ptr)
{
    CHECK_NULLPTR(ptr);
    ptr_ = std::move(ptr);
}

template <typename T>
template <typename Y>
shared_ref<T>::shared_ref(std::shared_ptr<Y> &&ptr)
{
    CHECK_NULLPTR(ptr);
    ptr_ = std::move(ptr);
}


template <typename T>
shared_ref<T> & shared_ref<T>::operator=(const std::shared_ptr<T> &ptr)
{
    CHECK_NULLPTR(ptr);
    ptr_ = ptr;
}


template <typename T>
template <typename Y>
shared_ref<T> & shared_ref<T>::operator=(const std::shared_ptr<Y> &ptr)
{
    CHECK_NULLPTR(ptr);
    ptr_ = ptr;
}


template <typename T>
shared_ref<T> & shared_ref<T>::operator=(std::shared_ptr<T> &&ptr)
{
    CHECK_NULLPTR(ptr);
    ptr_ = std::move(ptr);
}


template <typename T>
template <typename Y>
shared_ref<T> & shared_ref<T>::operator=(std::shared_ptr<Y> &&ptr)
{
    CHECK_NULLPTR(ptr);
    ptr_ = std::move(ptr);
}


template <typename T>
shared_ref<T>::shared_ref(shared_ref<T> &&other):
    ptr_(other.ptr_)
{}


template <typename T>
shared_ref<T> & shared_ref<T>::operator=(shared_ref<T> &&other)
{
    swap(other);
    return *this;
}


template <typename T>
long shared_ref<T>::use_count() const
{
    return ptr_.use_count();
}


template <typename T>
bool shared_ref<T>::unique() const
{
    return ptr_.unique();
}


template <typename T>
T & shared_ref<T>::get() const
{
    return *ptr_;
}


template <typename T>
std::shared_ptr<T> shared_ref<T>::ptr() const
{
    return ptr_;
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
    return ptr_.get();
}


template <typename T>
void shared_ref<T>::swap(shared_ref<T> &other)
{
    ptr_.swap(other.ptr_);
}

}   /* ref */
