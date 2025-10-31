#pragma once
#include <stdexcept>

constexpr size_t QUEUE_INIT_SIZE = 10;
constexpr size_t QUEUE_RESIZE_FACTOR = 2;

template <typename T>
class TQueue
{
private:
  T* pMem;
  size_t size;
  size_t front;
  size_t rear;
  size_t count;

  void Resize(size_t newSize);

public:
  explicit TQueue(size_t initialSize = QUEUE_INIT_SIZE);
  TQueue(const TQueue& other);
  TQueue& operator=(const TQueue& other);
  ~TQueue();

  void Push(const T& value);
  void Pop();
  T& Front();
  const T& Front() const;

  bool IsEmpty() const;
  bool IsFull() const;
  size_t GetSize() const;
  size_t GetCapacity() const;
};

template <typename T>
TQueue<T>::TQueue(size_t initialSize)
{
  if (initialSize == 0)
  {
    throw std::invalid_argument("Queue size must be greater than zero");
  }

  size = initialSize;
  pMem = new T[size];
  front = 0;
  rear = 0;
  count = 0;
}

template <typename T>
TQueue<T>::TQueue(const TQueue& other)
{
  size = other.size;
  front = other.front;
  rear = other.rear;
  count = other.count;
  pMem = new T[size];

  for (size_t i = 0; i < size; i++)
  {
    pMem[i] = other.pMem[i];
  }
}

template <typename T>
TQueue<T>& TQueue<T>::operator=(const TQueue& other)
{
  if (this != &other)
  {
    delete[] pMem;

    size = other.size;
    front = other.front;
    rear = other.rear;
    count = other.count;
    pMem = new T[size];

    for (size_t i = 0; i < size; i++)
    {
      pMem[i] = other.pMem[i];
    }
  }

  return *this;
}

template <typename T>
TQueue<T>::~TQueue()
{
  delete[] pMem;
}

template <typename T>
void TQueue<T>::Resize(size_t newSize)
{
  T* newMem = new T[newSize];

  for (size_t i = 0; i < count; i++)
  {
    newMem[i] = pMem[(front + i) % size];
  }

  delete[] pMem;
  pMem = newMem;
  size = newSize;
  front = 0;
  rear = count % size;
}

template <typename T>
void TQueue<T>::Push(const T& value)
{
  if (IsFull())
  {
    Resize(size * QUEUE_RESIZE_FACTOR);
  }

  pMem[rear] = value;
  rear = (rear + 1) % size;
  count++;
}

template <typename T>
void TQueue<T>::Pop()
{
  if (IsEmpty())
  {
    throw std::underflow_error("Queue is empty");
  }

  front = (front + 1) % size;
  count--;
}

template <typename T>
T& TQueue<T>::Front()
{
  if (IsEmpty())
  {
    throw std::underflow_error("Queue is empty");
  }

  return pMem[front];
}

template <typename T>
const T& TQueue<T>::Front() const
{
  if (IsEmpty())
  {
    throw std::underflow_error("Queue is empty");
  }

  return pMem[front];
}

template <typename T>
bool TQueue<T>::IsEmpty() const
{
  return count == 0;
}

template <typename T>
bool TQueue<T>::IsFull() const
{
  return count == size;
}

template <typename T>
size_t TQueue<T>::GetSize() const
{
  return count;
}

template <typename T>
size_t TQueue<T>::GetCapacity() const
{
  return size;
}
