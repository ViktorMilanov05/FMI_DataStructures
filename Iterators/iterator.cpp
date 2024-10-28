#include <iostream>

template <class T>
class iterator {
public:
	iterator(T* iter) : iter{ iter } {};
	iterator(T* iter + off) : iter{ iter + off } {};

	iterator<T>& operator++() {
		iter++;
		return (*this);
	}

	iterator<T> operator++(int) {
		iterator res = (*this);
		++(*this);
		return res;
	}

	iterator<T>& operator--() {
		iter--;
		return (*this);
	}

	iterator<T> operator--(int) {
		iterator res = (*this);
		--(*this);
		return res;
	}

	operator const_iterator<T>() const {
		return const_iterator<T>(iter);
	}

	iterator<T> operator+(int off) const {
		return { iter + off };
	};
	iterator<T> operator-(int off) const {
		return { iter - off };
	};
	int operator-(const const_iterator<T>& other) const {
		return iter - other.iter;
	};
	const T* operator->() const {
		return iter;
	}
	T* operator->() {
		return iter;
	}
	T& operator*() {
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