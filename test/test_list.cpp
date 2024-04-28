#include"gtest.h"
#include"list.h"

TEST(list, can_create_empty_list)
{
	ASSERT_NO_THROW(list<int> l);
}

TEST(list, can_add_element_to_empty_list)
{
	list<int> l;
	ASSERT_NO_THROW(l.push(1));
}

TEST(list, can_copy_list)
{
	list<int> l;
	l.push(1);
	ASSERT_NO_THROW(list<int> lCopy(l));
}

TEST(list, copied_list_is_equal_to_source_one)
{
	list<int> l;
	l.push(1);
	l.push(2);
	l.push(3);
	list<int> lCopy(l);
	EXPECT_EQ(l, lCopy);
}

TEST(list, can_assign_list)
{
	list<int> l;
	l.push(1);
	list<int> lCopy;
	ASSERT_NO_THROW(lCopy = l);
}

TEST(list, can_assign_list_to_itself)
{
	list<int> l;
	l.push(1);
	ASSERT_NO_THROW(l = l);
}

TEST(list, assigned_list_is_equal_to_source_one)
{
	list<int> l;
	l.push(1);
	l.push(2);
	l.push(3);
	list<int> lCopy;
	lCopy.push(4);
	lCopy = l;
	EXPECT_EQ(l, lCopy);
}

TEST(list, can_get_size)
{
	list<int> l;
	l.push(1);
	l.push(2);
	l.push(3);
	EXPECT_EQ(l.size(), 3);
}

TEST(list, isEmpty_works_for_empty)
{
	list<int> l;
	EXPECT_EQ(l.isEmpty(), true);
}

TEST(list, isEmpty_works_for_not_empty)
{
	list<int> l;
	l.push(1);
	EXPECT_EQ(l.isEmpty(), false);
}

TEST(list, can_pop_element)
{
	list<int> l;
	l.push(10);
	l.push(9);
	l.push(8);
	l.push(7);
	list<int> expl;
	expl.push(10);
	expl.push(9);
	expl.push(8);
	l.pop(3);
	EXPECT_EQ(l, expl);
}

TEST(list, cant_get_element_with_too_large_index)
{
	list<int> l;
	l.push(10);
	l.push(9);
	l.push(8);
	ASSERT_ANY_THROW(l.at(4));
}

TEST(list, can_get_element)
{
	list<int> l;
	l.push(10);
	l.push(9);
	l.push(8);
	EXPECT_EQ(l.at(2), 8);
}

TEST(list, can_get_element_using_operator)
{
	list<int> l;
	l.push(10);
	l.push(9);
	l.push(8);
	EXPECT_EQ(l[2], 8);
}