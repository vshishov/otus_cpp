#pragma once

#include <iostream>
#include <memory>

template < typename T, typename Allocator = std::allocator<T> >
class List
{
private:
  struct Node {
    T data;
    Node* next;
  };

  void Destroy(Node* node)
  {
    m_allocator.destroy(node);
    m_allocatorNode.deallocate(node, 1);
  }

public:
  explicit List(Allocator allocator = Allocator())
    : m_pHead(nullptr)
    , m_pTail(nullptr)
    , m_allocator(allocator)
  {
  }
  
  ~List()
  {
    auto ptr = m_pHead;
    while (ptr != nullptr) {
        auto next = ptr->next;
        Destroy(ptr);
        ptr = next;
    }
  }

  void Add(const T& a_data)
  {
    Node* node = m_allocatorNode.allocate(1);
    m_allocator.construct(node, Node{a_data, nullptr});
    if (m_pTail != nullptr) {
      m_pTail->next = node;
    }
    
    m_pTail = node;
    
    if (m_pHead == nullptr) {
      m_pHead = node;
    }
  }

  class Iterator : public std::iterator<std::input_iterator_tag, T>
  {
    friend class List;

  private:
    explicit Iterator(Node* a_pItem)
      : m_pItem(a_pItem)
    { }

  public:
    Iterator(const Iterator& it)
      : m_pItem(it.m_pItem)
    { }

    bool operator!=(const Iterator& rhs) const
    {
      return m_pItem != rhs.m_pItem;
    }

    bool operator==(const Iterator& rhs) const
    {
      return m_pItem == rhs.m_pItem;
    }

    T& operator*() const
    {
      return m_pItem->data;
    }

    T* operator->() const
    {
      return &m_pItem->data;
    }

    Iterator& operator++()
    {
      if (m_pItem != nullptr)
        m_pItem = m_pItem->next;
      return *this;
    }

  private:
    Node* m_pItem;
  };

  typedef Iterator iterator;

  iterator begin()
  {
    return iterator(m_pHead);
  }

  iterator end()
  {
    return iterator(m_pTail->next);
  }
  
private:
  Node* m_pHead;
  Node* m_pTail;

  using AllocatorTraits = std::allocator_traits<Allocator>;
  using RebindAllocNode = typename AllocatorTraits::template rebind_alloc<Node>;  
  Allocator m_allocator;
  RebindAllocNode m_allocatorNode;
};