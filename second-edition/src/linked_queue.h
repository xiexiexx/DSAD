#ifndef LINKED_QUEUE_CLASS
#define LINKED_QUEUE_CLASS

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
  void push(const T& item);
  void pop();
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
  left = new lnode<T>;
  left->next = NULL;
  right = left;
}

template <typename T>
linked_queue<T>::~linked_queue()
{
  while (left != NULL)
  {
    lnode<T>* p = left;
    left = left->next;
    delete p;
  }
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
void linked_queue<T>::push(const T& item)
{
  right->data = item;
  lnode<T>* p = new lnode<T>;
  p->next = NULL;
  right->next = p;
  right = p;
  ++count;
}

template <typename T>
void linked_queue<T>::pop()
{
  lnode<T>* p = left;
  left = left->next;
  delete p;
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
