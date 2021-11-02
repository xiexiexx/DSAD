#ifndef CIRCULARLY_LINKED_QUEUE_STACK_CLASS
#define CIRCULARLY_LINKED_QUEUE_STACK_CLASS

#include <cstddef>

template <typename T>
struct lnode {
  T data;
  lnode<T>* next;
};

template <typename T>
class circularly_linked_queue_stack {
public:
  circularly_linked_queue_stack();
  ~circularly_linked_queue_stack();
  T& front();
  const T& front() const;
  void push_front(const T& item);
  void push_back(const T& item);
  void pop_back();
  size_t size() const;
  bool empty() const;
private:
  size_t count;
  lnode<T>* right;
};

template <typename T>
circularly_linked_queue_stack<T>::circularly_linked_queue_stack()
  : count(0)
{
  right = new lnode<T>;
  right->next = right;
}

template <typename T>
circularly_linked_queue_stack<T>::~circularly_linked_queue_stack()
{
  lnode<T>* left = right->next;
  while (left != right)
  {
    right->next = left;
    left = left->next;
    delete right->next;
  }
  delete right;
}

template <typename T>
T& circularly_linked_queue_stack<T>::front()
{
  return right->next->data;
}

template <typename T>
const T& circularly_linked_queue_stack<T>::front() const
{
  return right->next->data;
}

template <typename T>
void circularly_linked_queue_stack<T>::push_front(const T& item)
{
  lnode<T>* p = new lnode<T>;
  p->data = item;
  p->next = right->next;
  right->next = p;
  ++count;
}

template <typename T>
void circularly_linked_queue_stack<T>::push_back(const T& item)
{
  right->data = item;
  lnode<T>* p = new lnode<T>;
  p->next = right->next;
  right->next = p;
  right = p;
  ++count;
}

template <typename T>
void circularly_linked_queue_stack<T>::pop_front()
{
  lnode<T>* left = right->next;
  right->next = left->next;
  delete left;
  --count;
}

template <typename T>
size_t circularly_linked_queue_stack<T>::size() const
{
  return count;
}

template <typename T>
bool circularly_linked_queue_stack<T>::empty() const
{
  return (count == 0);
}

#endif  // CIRCULARLY_LINKED_QUEUE_STACK_CLASS
