#ifndef MYOPTIONAL_H
#define MYOPTIONAL_H

#include <type_traits>

// clang-format off

/**
 *   @brief Status codes used by myoptional
 */
enum class Status {
    OK = 0,
    INVALID_ARG,
    ERROR
};

// clang-format on

/**
 *   @brief Class that enables to hold user defined class or status code
 *
 *   @startuml
 *   note "Useless diagram ;-)" as N
 *
 *   class myoptional {
 *       myoptional(const P& value)
 *       operator T()
 *       operator Status()
 *       T* operator->() cont
 *       T* operator->()
 *       const T& operator*() const&
 *       T& operator*()
 *   }
 *   @enduml
 *
 *   @tparam T must be a class or const class. Can be either default or non-default constructible
 */
template <class T, std::enable_if_t<std::is_class<T>::value, bool> = true>
class myoptional {
public:
    constexpr myoptional() = delete;

    /**
     *   @brief Converting constructor that enables to assign user defined class
     *
     *   @tparam P used to check if user is assigning value or status code at compile-time
     */
    template <class P, std::enable_if_t<std::is_same<std::remove_const_t<T>, P>::value, bool> = true>
    constexpr myoptional(const P& value) noexcept
        : mValue(value)
        , mStatus(Status::OK)
    {
    }

    /**
     *   @brief Converting constructor that enables to assign status code
     *
     *   @tparam P used to check if user is assigning value or status code at compile-time
     */
    template <class P, std::enable_if_t<std::is_same<P, Status>::value, bool> = true>
    constexpr myoptional(const P status) noexcept
    {
        // Status::OK indicates that we have user value. It cannot be assigned explicitly
        if (status == Status::OK) {
            mStatus = Status::INVALID_ARG;
        } else {
            mStatus = status;
        }
    }

    /**
     *   @brief Convenience implict conversion to allow assigning copy of user defined value
     */
    operator T&() noexcept
    {
        return mValue;
    }

    /**
     *   @brief Convenience implict conversion to allow accessing status code
     */
    operator Status() noexcept
    {
        return mStatus;
    }

    /**
     *   @brief const access to user defined class members
     */
    constexpr const T* operator->() const noexcept
    {
        return operator bool() ? &mValue : nullptr;
    }

    /**
     *   @brief access to user defined class members
     */
    constexpr T* operator->() noexcept
    {
        return operator bool() ? &mValue : nullptr;
    }

    /**
     *   @brief const access to user defined object
     */
    constexpr const T& operator*() const& noexcept
    {
        return mValue;
    }

    /**
     *   @brief access to user defined object
     */
    constexpr T& operator*() & noexcept
    {
        return mValue;
    }

    /**
     *   @brief convenience funtion to check if user data is avaiable
     */
    constexpr explicit operator bool() const noexcept
    {
        return status() == Status::OK;
    }

    /**
     *   @brief status code getter
     */
    constexpr Status status() const noexcept
    {
        return mStatus;
    }

    typedef T type;

private:
    /**
     *   @brief anonymous union-like class. mValue will not be initialized automatically.
     *   Since we have one member (no active member swtiching) and handling class objects only
     *   placement new is not needed
     */
    union {
        T mValue;
    };

    Status mStatus{ Status::INVALID_ARG };
};

#endif // MYOPTIONAL_H

