#pragma once
#include <memory_resource>
#include <vector>
#include <string>

class Arena
{
public:
    template <typename T, typename... A>
    T *make(A &&...args)
    {
        void *mem = m_store.allocate(sizeof(T), alignof(T));
        return new (mem) T{(A &&)args...};
    };

    template <typename T, typename... A>
    std::pmr::vector<T> make_vector(A &&...args)
    {
        std::pmr::polymorphic_allocator<int> pa{&m_store};
        auto v = std::pmr::vector<T>{pa};
        v = {(A &&)args...};
        return v;
    }

    std::pmr::string make_string(std::string &&s)
    {
        std::pmr::polymorphic_allocator<char> pa{&m_store};
        auto strspace = std::pmr::string(pa);
        strspace = s;
        return strspace;
    }

private:
    std::pmr::monotonic_buffer_resource m_store;
};