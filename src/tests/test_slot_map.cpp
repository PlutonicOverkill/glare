#include "gtest/gtest.h"
#include "../glare/slot_map.hpp"

TEST(SlotMap, DefaultConstructor)
{
	Glare::Slot_map<int> sm;
	EXPECT_EQ(sm.size(), 0);
}

TEST(SlotMap, AddRemove)
{
	Glare::Slot_map<int> sm;
	auto p1 = sm.add(1);
	ASSERT_TRUE(p1);
	EXPECT_EQ(*p1, 1);
	EXPECT_EQ(sm.size(), 1);
	
	auto p2 = sm.add(2);
	ASSERT_TRUE(p2);
	EXPECT_EQ(*p2, 2);
	EXPECT_EQ(sm.size(), 2);
	
	p1.remove();
	EXPECT_FALSE(p1);
	EXPECT_EQ(sm.size(), 1);
	EXPECT_EQ(*p2, 2);
}

TEST(SlotMap, BufferedAddRemove)
{
	Glare::Slot_map<int> sm;
	
	auto p1 = sm.buffered_add(1);
	auto p2 = sm.buffered_add(2);
	p1.buffered_remove();
	
	EXPECT_EQ(sm.size(), 0);
	EXPECT_FALSE(p1);
	EXPECT_FALSE(p2);
	
	sm.clean_buffers();
	
	EXPECT_EQ(sm.size(), 1);
	EXPECT_FALSE(p1);
	ASSERT_TRUE(p2);
	EXPECT_EQ(*p2, 2);
}

TEST(SlotMap, MultipleRemove)
{
	Glare::Slot_map<int> sm;
	auto p = sm.add(42);
	EXPECT_EQ(sm.size(), 1);
	ASSERT_TRUE(p);
	EXPECT_EQ(*p, 42);
	
	for(int i = 0; i < 3; ++i)
	{
		p.remove();
		EXPECT_EQ(sm.size(), 0);
		EXPECT_FALSE(p);
	}
}

TEST(SlotMap, MultipleBufferedRemove)
{
	Glare::Slot_map<int> sm;
	auto p = sm.add(42);
	EXPECT_EQ(sm.size(), 1);
	ASSERT_TRUE(p);
	EXPECT_EQ(*p, 42);
	
	for(int i = 0; i < 3; ++i)
	{
		p.buffered_remove();
		EXPECT_EQ(sm.size(), 1);
		ASSERT_TRUE(p);
		EXPECT_EQ(*p, 42);
	}
	
	sm.clean_buffers();
	EXPECT_EQ(sm.size(), 0);
	EXPECT_FALSE(p);
}

TEST(SlotMap, Clear)
{
	Glare::Slot_map<int> sm;
	sm.add(1);
	sm.add(2);
	sm.add(3);
	
	sm.clear();
	EXPECT_EQ(sm.size(), 0);
}

TEST(SlotMap, Iterator)
{
	// TODO
}