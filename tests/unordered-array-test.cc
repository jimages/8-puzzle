#include <string>
#include <exception>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "unordered_array.hpp"

TEST(UnorderedArray, DefaultConstructor) {
	dat::unordered_array<int> i;
	EXPECT_EQ(0u, i.size());

	dat::unordered_array<std::string> s;
	EXPECT_EQ(0u, s.size());
}

TEST(UnorderedArray, ConstructorFromSize) {
	dat::unordered_array<int> i(5);
	EXPECT_EQ(5u, i.size());

	dat::unordered_array<std::string> s(5);
	EXPECT_EQ(5u, s.size());
}

TEST(UnorderedArray, ConstructorFromSizeAndValue) {
	dat::unordered_array<int> i(5, 1);
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(1, i[n]);
	}
	EXPECT_EQ(5u, i.size());

	dat::unordered_array<std::string> s(5, "TEST");
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(std::string("TEST"), s[n]);
	}
	EXPECT_EQ(5u, s.size());
}
TEST(UnorderedArray, Access) {

	// We check if we can access certain element
	dat::unordered_array<int> i(5u,3);
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(3, i[n]);
	}

	dat::unordered_array<std::string> s(5, "test");
	for (int n = 0; n != 5; ++n) {
		EXPECT_EQ(std::string("test"), s.at(n));
	}
}
