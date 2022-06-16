#pragma once

#include <autogen/Object.hpp>

namespace System::Collections::Generic {

template <class TKey, class TValue>
struct Dictionary : ::Object {
    struct Entry {
        std::int32_t hashCode;
        std::int32_t next;
        std::pair<TKey, TValue> kv;
    };

    ::Array<std::int32_t>* buckets;
    ::Array<Entry>* entries;
    std::int32_t count;
    std::int32_t version;
    std::int32_t freeList;
    std::int32_t freeCount;
    struct System_Collections_Generic_IEqualityComparer_TKey__o* comparer;
    struct System_Collections_Generic_Dictionary_KeyCollection_TKey__TValue__o* keys;
    struct System_Collections_Generic_Dictionary_ValueCollection_TKey__TValue__o* values;
    Il2CppObject* _syncRoot;

    using value_type = const std::pair<TKey, TValue>;

    class const_iterator {
        const Dictionary* m_dict;
        std::int32_t m_index;

        void advance_to_valid() {
            assert(m_index <= m_dict->count);
            while (m_index < m_dict->count && m_dict->entries->m_Items[m_index].hashCode < 0) {
                m_index++;
            }
        }

    public:
        explicit const_iterator(const Dictionary& dict, int index) : m_dict(&dict), m_index(index) {
            advance_to_valid();
        }

        const_iterator& operator++() {
            m_index++;
            advance_to_valid();
            return *this;
        }

        const std::pair<TKey, TValue>& operator*() const {
            assert(m_index < m_dict->count);
            const auto& entry = m_dict->entries->m_Items[m_index];
            assert(entry.hashCode >= 0);
            return entry.kv;
        }

        const std::pair<TKey, TValue>* operator->() const {
            return &**this;
        }

        friend bool operator==(const const_iterator& lhs, const const_iterator& rhs) {
            assert(lhs.m_dict == rhs.m_dict);
            return lhs.m_index == rhs.m_index;
        }

        friend bool operator!=(const const_iterator& lhs, const const_iterator& rhs) {
            return !(lhs == rhs);
        }
    };

    const_iterator begin() const {
        return const_iterator(*this, 0);
    }

    const_iterator end() const {
        return const_iterator(*this, count);
    }

    std::size_t size() const {
        return static_cast<std::size_t>(count - freeCount);
    }

    const_iterator find(const TKey& key) const {
        for (auto it = begin(); it != end(); ++it) {
            if (it->first == key) {
                return it;
            }
        }

        return end();
    }

    const TValue& at(const TKey& key) const {
        const auto it = find(key);
        if (it == end()) {
            throw std::out_of_range("Dictionary::at - missing key");
        }

        return it->second;
    }
};

} // namespace System::Collections::Generic
