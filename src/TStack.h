#pragma once
#include <stdexcept>
#include <algorithm>

constexpr size_t STACK_INIT_SIZE = 10;
constexpr size_t STACK_RESIZE_FACTOR = 2;

template <typename T>
class TStack
{
private:
  T* pMem;
  size_t size;
  size_t top;

  void Resize(size_t newSize);

public:
  explicit TStack(size_t initialSize = STACK_INIT_SIZE);
  TStack(const TStack& other);
	TStack(const TStack&& other);
  TStack& operator=(const TStack& other);
  ~TStack();

  void Push(const T& value);
  void Pop();
  T& Top();
  const T& Top() const;

  bool IsEmpty() const;
  size_t GetSize() const;
  size_t GetCapacity() const;
};


template <typename T>
TStack<T>::TStack(size_t initialSize)
{
  if (initialSize == 0)
  {
    throw std::invalid_argument("Stack size must be greater than zero");
  }

  size = initialSize;
  top = 0;
  pMem = new T[size];
}

template <typename T>
TStack<T>::TStack(const TStack& other)
{
  size = other.size;
  top = other.top;
  pMem = new T[size];

  for (size_t i = 0; i < top; i++)
  {
    pMem[i] = other.pMem[i];
  }
}

template <typename T>
TStack<T>::TStack(const TStack&& other)
{
  size = other.size;
  top = other.top;
  pMem = other.pMem;
  other.pMem = nullptr;
  other.size = 0;
	other.top = 0;
}

template <typename T>
TStack<T>& TStack<T>::operator=(const TStack& other)
{
  if (this != &other)
  {
    delete[] pMem;

    size = other.size;
    top = other.top;
    pMem = new T[size];

    for (size_t i = 0; i < top; i++)
    {
      pMem[i] = other.pMem[i];
    }
  }

  return *this;
}

template <typename T>
TStack<T>::~TStack()
{
  delete[] pMem;
}

template <typename T>
void TStack<T>::Resize(size_t newSize)
{
  T* newMem = new T[newSize];

  for (size_t i = 0; i < top; i++)
  {
    newMem[i] = pMem[i];
  }

  delete[] pMem;
  pMem = newMem;
  size = newSize;
}

template <typename T>
void TStack<T>::Push(const T& value)
{
  if (top == size)
  {
    Resize(size * STACK_RESIZE_FACTOR);
  }

  pMem[top] = value;
  top++;
}

template <typename T>
void TStack<T>::Pop()
{
  if (IsEmpty())
  {
    throw std::underflow_error("Stack is empty");
  }

  top--;
}

template <typename T>
T& TStack<T>::Top()
{
  if (IsEmpty())
  {
    throw std::underflow_error("Stack is empty");
  }

  return pMem[top - 1];
}

template <typename T>
const T& TStack<T>::Top() const
{
  if (IsEmpty())
  {
    throw std::underflow_error("Stack is empty");
  }

  return pMem[top - 1];
}

template <typename T>
bool TStack<T>::IsEmpty() const
{
  return top == 0;
}

template <typename T>
size_t TStack<T>::GetSize() const
{
  return top;
}

template <typename T>
size_t TStack<T>::GetCapacity() const
{
  return size;
}
