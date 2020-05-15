#pragma once

#include <iostream>
#include <limits>

template<typename T, int Capacity = 10>
struct chunk_allocator
{
  using value_type      = T;

  using pointer         = T*;
  using const_pointer   = const T*;
  using reference       = T&;
  using const_reference = const T&;

  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;

  template<typename U>
  struct rebind {
    using other = chunk_allocator<U, Capacity>;
  };

  chunk_allocator() 
    : m_pBuffer(nullptr)
    , m_szCount(0)
  { }

  ~chunk_allocator() = default;

  template<typename U>
  chunk_allocator(const chunk_allocator<U>&) {}

  size_type max_size() const {
    return std::numeric_limits<size_type>::max();
  }

  T* allocate(std::size_t n) 
  {
    if (m_szCount >= Capacity){
     throw std::bad_alloc();
    }
    
    if (m_pBuffer == nullptr) {
      m_pBuffer = new T[Capacity];
    }
    
    m_szCount += n;
    return m_pBuffer + (m_szCount * sizeof(T) * n);
  }

  void deallocate(T* /*p*/, std::size_t n)
  {
    m_szCount -= n;
    if (m_szCount == 0) {
      delete [] m_pBuffer;
      m_pBuffer = nullptr;
    }
  }

  template<typename U, typename ...Args>
  void construct(U* p, Args &&...args)
  {
    new(p) U(std::forward<Args>(args)...);
  }

  template<typename U>
  void destroy(U* p)
  {
    p->~U();
  }

private:
  T* m_pBuffer;
  size_t m_szCount;
};