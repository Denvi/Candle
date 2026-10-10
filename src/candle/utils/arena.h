// This file is a part of "Candle" application.
// Copyright 2015-2026 Hayrullin Denis Ravilevich

#ifndef ARENA_H
#define ARENA_H

#include <QVector>

#include <cstddef>
#include <new>

// Bump allocator over fixed-size blocks. All allocations stay valid and
// at a stable address until clear() or destruction, so pointers into the
// arena remain interchangeable with individually allocated ones.
class Arena
{
public:
    Arena() : m_blocks(), m_current(nullptr), m_used(0), m_free(0) {}

    ~Arena() { clear(); }

    Arena(const Arena &) = delete;
    Arena &operator=(const Arena &) = delete;

    void *alloc(size_t size)
    {
        size = (size + ALIGN - 1) & ~(ALIGN - 1);

        if (m_free < size) {
            const size_t blockSize = size > BLOCK ? size : BLOCK;
            char *block = new char[blockSize];
            m_blocks.append(block);

            m_current = block;
            m_used = 0;
            m_free = blockSize;
        }

        char *result = m_current + m_used;
        m_used += size;
        m_free -= size;

        return result;
    }

    template<typename T, typename... Args>
    T *create(Args... args)
    {
        return new (alloc(sizeof(T))) T(args...);
    }

    void clear()
    {
        for (char *block : m_blocks)
            delete [] block;

        m_blocks.clear();
        m_current = nullptr;
        m_used = 0;
        m_free = 0;
    }

private:
    static const size_t BLOCK = 256 * 1024;
    static const size_t ALIGN = 16;

    QVector<char*> m_blocks;
    char *m_current;
    size_t m_used;
    size_t m_free;
};

#endif // ARENA_H
