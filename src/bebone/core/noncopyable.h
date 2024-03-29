#ifndef _BEBONE_CORE_NONCOPYABLE_H_
#define _BEBONE_CORE_NONCOPYABLE_H_

namespace bebone::core {
    /// Class that prohibits copying a derived class
    struct NonCopyable {
        NonCopyable() = default;

        NonCopyable(const NonCopyable &) = delete;
        void operator=(const NonCopyable &) = delete;
        NonCopyable(NonCopyable &&) = delete;
        NonCopyable &operator=(NonCopyable &&) = delete;
    };
}

#endif
