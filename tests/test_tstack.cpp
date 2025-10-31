#include "../src/TStack.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

TEST(TStack, can_create_stack_with_positive_size)
{
  ASSERT_NO_THROW(TStack<int> stack(5));
}

TEST(TStack, throws_when_create_stack_with_zero_size)
{
  ASSERT_ANY_THROW(TStack<int> stack(0));
}

TEST(TStack, can_push_element)
{
  TStack<int> stack(3);
  ASSERT_NO_THROW(stack.Push(10));
}

TEST(TStack, can_pop_element)
{
  TStack<int> stack(3);
  stack.Push(10);
  ASSERT_NO_THROW(stack.Pop());
}

TEST(TStack, pop_reduces_stack_size)
{
  TStack<int> stack(3);
  stack.Push(10);
  size_t before = stack.GetSize();
  stack.Pop();
  size_t after = stack.GetSize();
  EXPECT_EQ(before - 1, after);
}

TEST(TStack, can_get_top_element)
{
  TStack<int> stack(3);
  stack.Push(42);
  EXPECT_EQ(stack.Top(), 42);
}

TEST(TStack, top_does_not_remove_element)
{
  TStack<int> stack(3);
  stack.Push(1);
  stack.Top();
  EXPECT_EQ(stack.GetSize(), 1);
}

TEST(TStack, throws_when_pop_from_empty_stack)
{
  TStack<int> stack(3);
  ASSERT_ANY_THROW(stack.Pop());
}

TEST(TStack, throws_when_top_from_empty_stack)
{
  TStack<int> stack(3);
  ASSERT_ANY_THROW(stack.Top());
}

TEST(TStack, can_push_and_pop_multiple_elements)
{
  TStack<int> stack(5);
  stack.Push(1);
  stack.Push(2);
  stack.Push(3);

  EXPECT_EQ(stack.Top(), 3);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 2);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 1);
}

TEST(TStack, can_resize_when_full)
{
  TStack<int> stack(2);
  stack.Push(1);
  stack.Push(2);
  stack.Push(3); // triggers resize
  EXPECT_EQ(stack.Top(), 3);
  EXPECT_EQ(stack.GetSize(), 3);
}

TEST(TStack, resized_stack_preserves_elements)
{
  TStack<int> stack(2);
  stack.Push(10);
  stack.Push(20);
  stack.Push(30); // resize occurs

  EXPECT_EQ(stack.Top(), 30);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 20);
  stack.Pop();
  EXPECT_EQ(stack.Top(), 10);
}

TEST(TStack, can_work_with_strings)
{
  TStack<std::string> stack(2);
  stack.Push("first");
  stack.Push("second");

  EXPECT_EQ(stack.Top(), "second");
  stack.Pop();
  EXPECT_EQ(stack.Top(), "first");
}
