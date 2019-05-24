#include <string>
#include <exception>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "list.hpp"

TEST(ListTest, DefaultConstructor) {
	dat::list<int> i;
	dat::list<std::string> s;

	// Now we check the validation of the constructure.
	EXPECT_EQ(0u, i.size());
	EXPECT_EQ(0u, s.size());
}

TEST(ListTest, ConstructorFromSize) {
	dat::list<int> i(5u);

	// We will have 5 elements in our list.
	EXPECT_EQ(5u, i.size());

	dat::list<std::string> s(5u);

	// We will init list with 5 string in the list.
	EXPECT_EQ(5u, s.size());
}

TEST(ListTest, ConstructorFromSizeAndValue) {
	dat::list<int> i(5u,3);

	// We will have 5 elements in our list.
	EXPECT_EQ(5u, i.size());
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(3, i.at(n));
	}

	dat::list<std::string> s(5, "test");

	// We check the value of the test.
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(std::string("test"), s.at(n));
	}
	// We will init list with 5 string in the list.
	EXPECT_EQ(5u, s.size());
}

TEST(ListTest, Access) {

	// We check if we can access certain element
	dat::list<int> i(5u,3);
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(3, i.at(n));
	}

	dat::list<std::string> s(5, "test");
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(std::string("test"), s.at(n));
	}
}

TEST(ListTest, AccessOverFlow) {
	dat::list<int> i(5u,3);
	EXPECT_THROW(i.at(10), std::out_of_range);
}

TEST(ListTest, Set) {
	// We check if we can set certain element.
	dat::list<int> i(5);
	for (int n = 0; n != 5; ++n)
		i.set(n,n);
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(n, i.at(n));
	}

	dat::list<std::string> s(5);
	for (int n = 0; n != 5; ++n)
		s.set(n, "test");
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(std::string("test"), s.at(n));
	}
}

TEST(ListTest, SetOverFlow) {
	dat::list<int> i(5u,3);
	EXPECT_THROW(i.set(10,10), std::out_of_range);
}

TEST(ListTest, PushBack) {
	// We test push back .
	dat::list<int> i(3u,0);
	i.push_back(1);
	EXPECT_EQ(1, i.at(3u));

	dat::list<std::string> s(3u,"test");
	s.push_back("blablabla");
	EXPECT_EQ(std::string("blablabla"), s.at(3u));

}
TEST(ListTest, PushBefore) {
	// We test push back and push before.
	dat::list<int> i(3u,0);
	i.push_before(1);
	EXPECT_EQ(1, i.at(0u));

	dat::list<std::string> s(3,"test");
	s.push_before("blablabla");
	EXPECT_EQ(std::string("blablabla"), s.at(0));
}

TEST(ListTest, PopBack) {
	// We test push back and push before.
	dat::list<int> i(3,0);
	for (int n = 0; n != 3; ++n)
		i.set(n,n);
	EXPECT_EQ(2, i.pop_back());
	// New we check the size
	EXPECT_EQ(2u, i.size());

	dat::list<std::string> s(3, "test");
	EXPECT_EQ(std::string("test"), s.pop_back());
	EXPECT_EQ(2u, s.size());

	//When we have only one elements.
	dat::list<int> t(1,0);
	EXPECT_EQ(0, t.pop_back());
	EXPECT_EQ(0u, t.size());

}

TEST(ListTest, PopBefore) {
	dat::list<int> i(3);
	for (int n = 0; n != 3; ++n)
		i.set(n,n);
	EXPECT_EQ(0, i.pop_before());

	// New we check the size
	EXPECT_EQ(2u, i.size());

	dat::list<std::string> s(3u, "test");
	EXPECT_EQ(std::string("test"), s.pop_before());
	EXPECT_EQ(2u, s.size());
}

TEST(ListTest, InsertAfter) {
	dat::list<int> i(3u, 0);
	i.insert_after(0u,1);
	EXPECT_EQ(1, i.at(1));
}

TEST(ListTest, InsertAfterOutOfRange) {
	// We test when we the position in which we want to insert is invalid.
	dat::list<int> i(3u, 0);
	EXPECT_THROW(i.insert_after(10u,1), std::out_of_range);
}
TEST(ListTest, RemoveAfter) {
	dat::list<int> i(3);
	for (int n = 0; n != 3; ++n)
		i.set(n,n);
	i.remove(1);
	EXPECT_EQ(2, i.size());
	EXPECT_EQ(0, i.at(0));
	EXPECT_EQ(2, i.at(1));

	dat::list<int> s(3u);
	for (int n = 0; n != 3; ++n)
		s.set(n,n);
	s.remove(0);
	EXPECT_EQ(1, s.at(0u));
	EXPECT_EQ(2, s.at(1u));
	EXPECT_EQ(2, s.size());
}
TEST(ListTest, RemoveAfterOutOfRange) {
	// We test when we the position in which we want to insert is invalid.
	dat::list<int> i(3u, 0);
	EXPECT_THROW(i.remove(10u), std::out_of_range);
}
