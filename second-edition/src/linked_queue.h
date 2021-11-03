#ifndef LINKED_QUEUE_CLASS
#define LINKED_QUEUE_CLASS

#include <memory>

template <typename T>
struct lnode {
  T data;
  lnode<T>* next;
};

template <typename T>
class linked_queue {
public:
  linked_queue();
  ~linked_queue();
  T& front();
  const T& front() const;
  void enqueue(const T& item);
  void dequeue();
  size_t size() const;
  bool empty() const;
private:
  size_t count;
  lnode<T>* left;
  lnode<T>* right;
};

template <typename T>
linked_queue<T>::linked_queue()
  : count(0)
{
  left = (lnode<T>*) malloc(sizeof(lnode<T>));
  right = left;
}

template <typename T>
linked_queue<T>::~linked_queue()
{
  while (left != right)
  {
    lnode<T>* p = left;
    left = left->next;
    free(p);
  }
  free(right);
}

template <typename T>
T& linked_queue<T>::front()
{
  return left->data;
}

template <typename T>
const T& linked_queue<T>::front() const
{
  return left->data;
}

template <typename T>
void linked_queue<T>::enqueue(const T& item)
{
  *right = {item, (lnode<T>*) malloc(sizeof(lnode<T>))};
  right = right->next;
  ++count;
}

template <typename T>
void linked_queue<T>::dequeue()
{
  lnode<T>* p = left;
  left = left->next;
  free(p);
  --count;
}

template <typename T>
size_t linked_queue<T>::size() const
{
  return count;
}

template <typename T>
bool linked_queue<T>::empty() const
{
  return (count == 0);
}

#endif  // LINKED_QUEUE_CLASS
