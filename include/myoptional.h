#ifndef MYOPTIONAL_H
#define MYOPTIONAL_H

#include <iostream>
#include <type_traits>

enum class Status { OK = 0, INVALID_ARG, ERROR };

template <class T, std::enable_if_t<std::is_class<T>::value, bool> = true>
class myoptional {
public:
    // Empty object
    constexpr myoptional() = delete;

    // Constructor assigning value
    template <class P, std::enable_if_t<std::is_same<std::remove_const_t<T>, P>::value, bool> = true>
    constexpr myoptional(const P& val)
        // constexpr myoptional(const T& val)
        : _value(val)
        , _status(Status::OK)
    {
        std::cout << "User!" << std::endl;
    }

    // Constructor assigning error code
    template <class P, std::enable_if_t<std::is_same<P, Status>::value, bool> = true>
    constexpr myoptional(const P& val)
    {
        std::cout << "Status!" << std::endl;
        // static_assert(PVal == Status::OK, "dupaaaa!");
        // std::cout << "const " << std::is_const<T>::value << std::endl;
    }

    constexpr const T* operator->() const noexcept
    {
        return operator bool() ? &_value : nullptr;
    }

    constexpr T* operator->() noexcept
    {
        return operator bool() ? &_value : nullptr;
    }

    constexpr explicit operator bool() const noexcept
    {
        return status() == Status::OK;
    }

    constexpr Status status() const noexcept
    {
        return _status;
    }

private:
    T _value;
    Status _status{ Status::INVALID_ARG };
};

#endif // MYOPTIONAL_H

