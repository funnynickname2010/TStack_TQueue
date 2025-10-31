#include "../src/TQueue.h"
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

TEST(TQueue, can_create_queue_with_positive_size)
{
	ASSERT_NO_THROW(TQueue<int> q(5));
}

TEST(TQueue, throws_when_create_queue_with_zero_size)
{
	ASSERT_THROW(TQueue<int> q(0), std::invalid_argument);
}

TEST(TQueue, can_push_and_pop_element)
{
	TQueue<int> q(3);
	q.Push(10);
	ASSERT_EQ(q.Front(), 10);
	q.Pop();
	ASSERT_EQ(q.GetSize(), 0);
}

TEST(TQueue, elements_are_popped_in_fifo_order)
{
	TQueue<int> q(3);
	q.Push(1);
	q.Push(2);
	q.Push(3);

	ASSERT_EQ(q.Front(), 1);
	q.Pop();

	ASSERT_EQ(q.Front(), 2);
	q.Pop();

	ASSERT_EQ(q.Front(), 3);
	q.Pop();
}

TEST(TQueue, throws_when_pop_from_empty_queue)
{
	TQueue<int> q(2);
	ASSERT_THROW(q.Pop(), std::underflow_error);
}

TEST(TQueue, can_handle_wraparound)
{
	TQueue<int> q(3);
	q.Push(1);
	q.Push(2);
	q.Pop(); // remove 1
	q.Pop(); // remove 2
	q.Push(3);
	q.Push(4);

	ASSERT_EQ(q.Front(), 3);
	q.Pop();

	ASSERT_EQ(q.Front(), 4);
	q.Pop();
	ASSERT_EQ(q.GetSize(), 0);
}

TEST(TQueue, can_resize_queue_to_bigger_capacity)
{
	TQueue<int> q(2);
	q.Push(1);
	q.Push(2);
	//q.Resize(4);
	q.Push(3);
	q.Push(4);

	ASSERT_EQ(q.Front(), 1);
	q.Pop();
	ASSERT_EQ(q.Front(), 2);
	q.Pop();
	ASSERT_EQ(q.Front(), 3);
	q.Pop();
	ASSERT_EQ(q.Front(), 4);
	q.Pop();
	ASSERT_EQ(q.GetSize(), 0);
}

TEST(TQueue, size_and_capacity_work_correctly)
{
	TQueue<int> q(5);
	ASSERT_EQ(q.GetSize(), 0);
	ASSERT_EQ(q.GetCapacity(), 5);
	q.Push(10);
	ASSERT_EQ(q.GetSize(), 1);
	q.Pop();
	ASSERT_EQ(q.GetSize(), 0);
}