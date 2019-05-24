/*
 * MY implement of data struture UNDER MIT LICENSE.
 * jimages123@gmail.com (c) 2018
 */

/*
 * The implement of unordered array.
 */

#ifndef DAT_LIST_H
#define DAT_LIST_H

#include <exception>
#include <iostream>
#include <memory>
#include <type_traits>
// My own namespace.
namespace dat {

	template <typename T>
	class list {
	private:
		struct node {
			T value;
			std::shared_ptr<node> next;
		};
		std::shared_ptr<node> root;
		std::shared_ptr<node> tail = root;
		size_t count = 0;

	public:
		list() = default;
		list(size_t size, T val) {
			for (int n = 0; n != size; ++n) {
				push_back(val);
			}
		}
		list(size_t size) {
			auto value = new T();
			for (int n = 0; n != size; ++n) {
				push_back(*value);
			}
			delete value;
		}

		void push_back(T val) {
			auto p = std::make_shared<node>();
			p->value = val;
			p->next = nullptr;
			if (root == nullptr) {
				root.swap(p);
				tail = root;
			} else {
				tail->next.swap(p);
				tail = tail->next;
			}
			++count;
		}
		void push_before(T val) {
			auto p = std::make_shared<node>();
			p->value = val;
			p->next = root;
			root = p;
			++count;
		}
		T operator[](size_t ind) const {
			return at(ind);
		}
		T at(const size_t ind) const {

			std::shared_ptr<node> ptr(root);
			if (ind < 0) {
				throw std::out_of_range("Negative index invalid.");
			}

			// check whether we run out of range.
			if (ind >= this->size()) {
				throw std::out_of_range("index out of range.");
			}

			for (size_t n = 0; n != ind; n++) {
				ptr = ptr->next;
			}
			return ptr->value;
		}
		void set(size_t ind, T value) {
			std::shared_ptr<node> ptr(root);
			if (ind < 0) {
				throw std::out_of_range("Negative index invalid.");
			}
			// check whether we run out of range.
			if (ind >= this->size()) {
				throw std::out_of_range("index out of range.");
			}

			for (size_t n = 0; n != ind; n++) {
				ptr = ptr->next;
			}
			ptr->value = value;
		}
		T pop_back() {
			if( tail == root) {
				auto v = root;
				tail.reset();
				root.reset();
				count = 0u;
				return v->value;
			}
			auto ptr = root;
			size_t ind = this->size();
			for (size_t n = 0; n != ind - 2; n++) {
				ptr = ptr->next;
			}
			tail = ptr;
			T value = ptr->next->value;
			ptr->next.reset();
			--count;
			return value;
		}
		T pop_before() {
			if (root == nullptr) {
				throw std::runtime_error("Null list");
			}

			auto ptr = root;
			root = root->next;
			--count;
			return ptr->value;
		}
		void insert_after(size_t ind, T val) {
			std::shared_ptr<node> ptr(root);
			if (ind < 0) {
				throw std::out_of_range("Negative index invalid.");
			}
			// check whether we run out of range.
			if (ind >= this->size()) {
				throw std::out_of_range("index out of range.");
			}

			for (size_t n = 0; n != ind; n++) {
				ptr = ptr->next;
			}

			auto next = ptr->next;
			auto p = std::make_shared<node>();
			p->value = val;
			p->next = next;
			ptr->next = p;
			++count;
		}
		void remove(size_t ind) {
			std::shared_ptr<node> ptr(root);
			if (ind < 0) {
				throw std::out_of_range("Negative index invalid.");
			}
			// check whether we run out of range.
			if (ind >= this->size()) {
				throw std::out_of_range("index out of range.");
			}
			if (ind == 0u) {
				root = root->next;
			} else {
				for (size_t n = 0; n != ind - 1; n++) {
					ptr = ptr->next;
				}
				ptr->next = ptr->next->next;
			}
			--count;
		}
		size_t size() const {
			return count;
		}
	};
} // namespace dat
#endif // DAT_LIST_H
