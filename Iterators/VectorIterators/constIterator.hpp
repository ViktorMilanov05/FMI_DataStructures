#include <iostream>

template <class T>
class const_iterator {
public:
	const_iterator(const T* iter) : iter{ iter } {};
	const_iterator(const T* iter, size_t off) : iter{ iter + off } {};
	const_iterator<T> operator+(int off) const {
		return { iter + off };
	};
	const_iterator<T> operator-(int off) const {
		return { iter - off };
	};
	int operator-(const const_iterator<T>& other) const {
		return iter - other.iter;
	};
	const T* operator->() const {
		return iter;
	}
	const T& operator*() const {
		return (*iter);
	}
	bool operator==(const const_iterator<T>& other) const {
		return iter == other.iter;
	}
	bool operator!=(const const_iterator<T>& other) const {
		return iter != other.iter;
	}
private:
	T* iter;
};