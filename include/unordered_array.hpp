/*
 * MY implement of data struture UNDER MIT LICENSE.
 * jimages123@gmail.com (c) 2018
 */

/*
 * The implement of unordered array.
 */

#ifndef DAT_UNORDERED_ARRAY_H
#define DAT_UNORDERED_ARRAY_H

#include <iostream>
#include <memory>
#include <type_traits>

template <typename T>
class unordered_array
{
	std::unique_ptr<T[]> ptr;
	std::weak_ptr<T> after_last;
	size_t size = 0;
	size_t capacity = 0;
	void check_cap(size_t cap)
	{
		if ( cap >= capacity) setcapacity( capacity * 2);
	}

public:
	explicit unordered_array() = default;
	explicit unordered_array(size_t size): size(size), capacity(size)
	{
		ptr.reset(new T [size]);
		after_last = ptr[0];
	}
	void push_back(const T &value)
	{
		check_cap(size + 1);
		(after_last++)->T(value);
		size++;
	}

	size_t setcapacity(size_t nsize)
	{
		if (nsize <= capacity) {
			return capacity;
		}

		std::unique_ptr<T> new_ptr(new T[nsize]);
		std::weak_ptr<T> new_after_last(new_ptr);
		for (std::weak_ptr<T> n = ptr; n != after_last; ++n) {
			*new_after_last++ = *n;
		}

		capacity = nsize;
		ptr.reset(new_ptr);
		after_last.reset(new_after_last);
		return capacity;
	}
	
};
#endif // DAT_UNORDERED_ARRAY
