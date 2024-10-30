#include <iostream>
#include "Iterators.hpp"

const size_t GROWTH_FACTOR = 2;

template <class T>
class vector {
	using iter = iterator<T>;
	using c_iter = const_iterator<T>;
	using r_iter = reverse_iterator<T>;

	vector() = default;
	explicit vector(size_t count);
	vector(size_t count, const T& initial);
	vector(const vector& other);
	vector& operator=(const vector& other);
	vector(vector&& other);
	vector& operator=(vector&& other);
	~vector();

	void push_back(const T& el);
	void push_back(T&& el);
	void pop_back();
	void erase(c_iter position);
	void erase(c_iter start, c_iter end);
	void clear();

	template<class... Args>
	void emplace_back(Args&&... arg);

	const T& operator[](size_t ind) const { return data[ind]; };
	T& operator[](size_t ind) { return data[ind]; };
	T* data() { return data; };

	void resize(size_t n);
	void reserve(size_t n);
	void shrink_to_fit();

	bool empty() const { return size == 0 };
	size_t size() const { return size; };
	size_t cap() const { return cap; };

	iter begin() { return iter(data); }
	iter end() { return iter(data + size()); }

	c_iter c_begin() { return c_iter(data); }
	c_iter c_end() { return c_iter(data + size()); }

	r_iter r_begin() { return size > 0 ? r_iter(data + size() - 1) : r_iter(nullptr); }
	r_iter r_end() { return size > 0 ? r_iter(data - 1) : r_iter(nullptr); }

	T& back() { return data[size() - 1] };
	T& front() { return data[0] };
	const T& back() const { return data[size() - 1] };
	const T& front() const { return data[0] };

private:
	size_t calculateCap() const;
	void copyFrom(const vector& other);
	void moveFrom(vector&& other);
	void free();

	T* data = nullptr;
	size_t cap = 0;
	size_t size = 0;
};

template <class T>
vector<T>::vector(size_t count) {
	data = static_cast<T*>(operator new(count * sizeof(T)));
	for (size_t i = 0; i < count; i++)
	{
		new (&data[i]) T();
	}
	cap = size = count;
}

template <class T>
vector<T>::vector(size_t count, const T& initial) {
	data = static_cast<T*>(operator new(count * sizeof(T)));
	for (size_t i = 0; i < count; i++)
	{
		new (&data[i]) T(initial);
	}
	cap = size = count;
}

template <class T>
vector<T>::vector(const vector<T>& other) {
	copyFrom(other);
}
template<class T>
vector<T>& vector<T>::operator=(const vector<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}
template <class T>
vector<T>::vector(vector<T>&& other) {
	moveFrom(std::move(other));
}

template<class T>
vector<T>& vector<T>::operator=(vector<T>&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<class T>
vector<T>::~vector()
{
	free();
}

template<class T>
void vector<T>::push_back(const T& el)
{
	if (size == cap)
		reserve(calculateCap());
	new (&data[size++]) T(el);
}

template<class T>
void vector<T>::push_back(T&& el)
{
	if (size == cap)
		reserve(calculateCap());
	new (&data[size++]) T(std::move(el));
}

template<class T>
void vector<T>::pop_back()
{
	if (empty())
		return;
	erase(--end());
}

template<class T>
void vector<T>::erase(c_iter position)
{
	erase(position, position + 1);
}

template<class T>
void vector<T>::erase(c_iter start, c_iter end)
{
	int elToRemove = end - start;
	if (elToRemove <= 0)
		return;
	int start_curr = start - begin();
	int end_curr = end - begin();
	if (end != c_end()) {
		for (size_t i = end_curr; i < size; i++)
		{
			new (&data[start_curr++]) T(std::move(data[i]))
		}
	}
	for (size_t i = end_curr; i < size; i++)
	{
		data[i].~T()
	}
	size -= elToRemove;
}

template<class T>
void vector<T>::clear()
{
	for (size_t i = 0; i < size; i++)
	{
		data[i].~T();
	}
	size = 0;
}

template<class T>
size_t vector<T>::calculateCap() const
{
	if (cap == 0) {
		return 1;
	}
	return cap * GROWTH_FACTOR;
}

template<class T>
void vector<T>::copyFrom(const vector& other)
{
	data = static_cast<T*>(operator new(other.cap() * sizeof(T)));
	for (size_t i = 0; i < other.size(); i++)
	{
		new (&data[i]) T(other[i]);
	}
	cap = other.cap();
	size = other.size();
}

template<class T>
void vector<T>::moveFrom(vector&& other)
{
	data = other.data;
	cap = other.cap;
	size = other.size;
	other.data = nullptr;
	otehr.cap = other.size = 0;
}

template<class T>
void vector<T>::free()
{
	for (size_t i = 0; i < size; i++)
	{
		data[i].~T();
	}
	operator delete(data, cap * sizeof(T));
}

template<class T>
void vector<T>::resize(size_t n)
{
	if (n < size) {
		for (size_t i = n; i < size; i++)
		{
			data[i].~T();
		}
		size = n
	}
	else if (n > size) {
		if (n <= cap) {
			for (size_t i = size; i < n; i++)
			{
				new (&data[i]) T();
			}
			size = n;
		}
		else {
			T* newData = static_cast<T*>(operator new (n * sizeof(T)));
			for (size_t i = 0; i < size; i++)
			{
				new (&newData[i]) T(std::move(data[i]));
				//data[i].~T();
			}
			for (size_t i = size; i < n; i++)
			{
				new (&newData[i]) T();
			}
			operator delete(data, cap * sizeof(T));
			data = newData;
			cap = size = n
		}
	}
}

template<class T>
void vector<T>::reserve(size_t n)
{
	if (n > cap) {
		T* newData = static_cast<T*>(operator new (n * sizeof(T)));
		for (size_t i = 0; i < size; i++)
		{
			new (&newData[i]) T(std::move(data[i]));
			data[i].~T();
		}
		operator delete(data, cap * sizeof(T));
		data = newData;
		cap = n;
	}
}

template<class T>
void vector<T>::shrink_to_fit()
{
	if (cap == size)
		return;
	T* newData = static_cast<T*>(operator new (size * sizeof(T)));
	for (size_t i = 0; i < size; i++)
	{
		new (&newData[i]) T(std::move(data[i]));
		data[i].~T();
	}
	operator delete(data, cap * sizeof(T));
	data = newData;
	cap = size;
}

template<class T>
template<class ...Args>
void vector<T>::emplace_back(Args && ...arg)
{
	if (cap == size) {
		reserve(calculateCap());
	}
	new (&data[size++]) T(std::forward < Args(arg)...);
}