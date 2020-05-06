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
  List(Allocator allocator = Allocator())
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

  void print()
  {
    for (auto ptr = m_pHead; ptr != nullptr; ptr = ptr->next) {
      std::cout << ptr->data << std::endl;
    }
  }
  
private:
  Node* m_pHead;
  Node* m_pTail;

  using AllocatorTraits = std::allocator_traits<Allocator>;
  using RebindAllocNode = typename AllocatorTraits::template rebind_alloc<Node>;  
  Allocator m_allocator;
  RebindAllocNode m_allocatorNode;
};