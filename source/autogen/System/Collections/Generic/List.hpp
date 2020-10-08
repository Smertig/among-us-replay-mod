#pragma once

#include <autogen/Object.hpp>

namespace System::Collections::Generic {

template <class T>
struct List : ::Object {
    ::Array<T>* _items;
    std::int32_t _size;
    std::int32_t _version;
    struct Il2CppObject* _syncRoot;

    using value_type = const T*;

    const value_type* begin() const {
        return _items->m_Items;
    }

    const value_type* end() const {
        return _items->m_Items + size();
    }

    std::size_t size() const {
        return static_cast<std::size_t>(_size);
    }

    const value_type& operator[](std::size_t index) const {
        assert(index <= size());
        return begin()[index];
    }
};

} // namespace System::Collections::Generic
