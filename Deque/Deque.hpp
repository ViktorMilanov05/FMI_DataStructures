#include <iostream>
#include <algorithm>
#include <memory>

template <class T, class Allocator = std::allocator<T>>
class Deque {
public:

	Deque();
	Deque(const Deque& other);
	Deque& operator=(const Deque& other);
	Deque(Deque&& other);
	Deque& operator=(const Deque&& other);
	~Deque();

	void push_front(const T& obj);
	void push_front(T&& obj);
	void push_back(const T& obj);
	void push_back(T&& obj);
	void pop_back();
	void pop_front();

	template<typename... Args>
	void emplace_front(Args&&... args);

	template<typename... Args>
	void emplace_back(Args&&... args);

	const T& front() const;
	T front();

	const T& back() const;
	T back();

	const T& operator[](size_t ind) const;
	T& operator[](size_t ind);

	size_t getSize() const { return size; };
	bool isEmply() const { return size == 0; };

	class DequeIterator {
	public:
		DequeIterator& operator++(int) {
			index++;
			return *this;
		}
		DequeIterator operator++() {
			DequeIterator old = *this;
			index++;
			return old;
		}
		DequeIterator& operator--(int) {
			index--;
			return *this;
		}
		DequeIterator operator--() {
			DequeIterator old = *this;
			index--;
			return old;
		}
		DequeIterator& operator+(int val) {
			return DequeIterator(deque, index + val);
		}
		DequeIterator& operator-(int val) {
			return DequeIterator(deque, index - val);
		}
		T& operator*() {
			return deque[index];
		}
		bool operator==(const DequeIterator other) const{
			return index == other.index;
		}
		bool operator==(const DequeIterator other) const {
			return index != other.index;
		}
	private:
		Deque deque;
		size_t index;
		DequeIterator(Deque& deque, size_t index) : deque(deque), index(index) {};
		friend class Deque;
	};

	class ConstDequeIterator {
	public:
		ConstDequeIterator& operator++(int) {
			index++;
			return *this;
		}
		ConstDequeIterator operator++() {
			DequeIterator old = *this;
			index++;
			return old;
		}
		ConstDequeIterator& operator--(int) {
			index--;
			return *this;
		}
		ConstDequeIterator operator--() {
			DequeIterator old = *this;
			index--;
			return old;
		}
		ConstDequeIterator& operator+(int val) {
			return DequeIterator(deque, index + val);
		}
		ConstDequeIterator& operator-(int val) {
			return DequeIterator(deque, index - val);
		}
		T& operator*() {
			return deque[index];
		}
		bool operator==(const ConstDequeIterator other) const {
			return index == other.index;
		}
		bool operator==(const ConstDequeIterator other) const {
			return index != other.index;
		}
	private:
		const Deque deque;
		size_t index;
		DequeIterator(const Deque& deque, size_t index) : deque(deque), index(index) {};
		friend class Deque;
	};

	Deque::DequeIterator& begin() { return DequeIterator(*this, 0); }
	Deque::ConstDequeIterator& begin() const { return ConstDequeIterator(*this, 0); }

	Deque::DequeIterator& end() { return DequeIterator(*this, getSize()); }
	Deque::ConstDequeIterator& begin() const { return ConstDequeIterator(*this, getSize()); }
private:
	T* data = nullptr;
	size_t size = 0;
	size_t cap = 0;
	size_t head = 0;
	size_t tail = 0;

	Allocator alloc;

	void copyFrom(const Deque& other);
	void moveFrom(Deque&& other);
	void free();
	void moveIndex(size_t& index, bool forward) const;
	void resize(size_t newCap = 0);
	size_t getNewCap() const {return cap ? cap * 2 : 1};

};

template<class T, class Allocator>
Deque<T, Allocator>::Deque() : size(0), cap(8), head(0), tail(0)
{
	data = alloc.allocate(cap);
}

template<class T, class Allocator>
Deque<T, Allocator>::Deque(const Deque& other)
{
	copyFrom(other);
}

template<class T, class Allocator>
Deque<T,Allocator>& Deque<T, Allocator>::operator=(const Deque& other)
{
	if (this == &other) {
		free();
		copyFrom(other);
	}
	return *this
}

template<class T, class Allocator>
Deque<T, Allocator>::Deque(Deque&& other)
{
	moveFrom(std::move(other));
}

template<class T, class Allocator>
Deque<T,Allocator>& Deque<T, Allocator>::operator=(const Deque&& other)
{
	if (this == &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this
}

template<class T, class Allocator>
Deque<T, Allocator>::~Deque()
{
	free();
}

template<class T, class Allocator>
void Deque<T, Allocator>::push_front(const T& obj)
{
	if (size >= cap) {
		resize();
	}
	moveIndex(head, false);
	std::construct_at(data + head, obj);
	size++;
}

template<class T, class Allocator>
void Deque<T, Allocator>::push_front(T&& obj)
{
	if (size >= cap) {
		resize();
	}
	moveIndex(head, false);
	std::construct_at(data + head, std::move(obj));
	size++;
}

template<class T, class Allocator>
void Deque<T, Allocator>::push_back(const T& obj)
{
	if (size >= cap) {
		resize();
	}
	std::construct_at(data + tail, obj);
	moveIndex(tail, true);
	size++;
}

template<class T, class Allocator>
void Deque<T, Allocator>::push_back(T&& obj)
{
	if (size >= cap) {
		resize();
	}
	std::construct_at(data + tail, std::move(obj));
	moveIndex(tail, true);
	size++;
}

template<class T, class Allocator>
void Deque<T, Allocator>::pop_back()
{
	if (isEmply())
		return;
	moveIndex(tail, false);
	std::destruct_at(data + tail);
	size--;
}

template<class T, class Allocator>
void Deque<T, Allocator>::pop_front()
{
	if (isEmply())
		return;
	std::destruct_at(data + head);
	moveIndex(head, true);
	size--;
}

template<class T, class Allocator>
void Deque<T, Allocator>::copyFrom(const Deque& other)
{
	cap = other.cap;
	data = alloc.allocate(cap);
	for (size_t i = 0; i < size; i++)
	{
		push_back(other[i]);
	};
}

template<class T, class Allocator>
void Deque<T, Allocator>::moveFrom(Deque&& other)
{
	cap = other.cap;
	size = other.size;
	head = other.head;
	tail = other.tail;
	data = other.data;
	other.data = nullptr;
	other.size = other.cap = other.head = other.tail = 0;
}

template<class T, class Allocator>
void Deque<T, Allocator>::free()
{
	if (head == tail && size > 1) {
		std::destruct_at(data + head);
		moveIndex(head, true);
	}
	while(head != tail)
	{
		std::destruct_at(data + head + i);
		moveIndex(head, true);
	}
	alloc.deallocate(data,cap);
	data = nullptr;
	cap = size = head = tail = 0;
}

template<class T, class Allocator>
void Deque<T, Allocator>::moveIndex(size_t& index, bool forward) const
{
	if (cap == 0)
		return;
	if (forward) {
		(++index) %= cap;
	}
	else {
		index = (index) ? index-- : cap - 1;
	}
}

template<class T, class Allocator>
void Deque<T, Allocator>::resize(size_t newCap)
{
	if (newCap == 0) {
		newCap = getNewCap();
	}
	T* newData = alloc.allocate(newCap);
	size_t includedElementsCount = std::min(newCap, size);
	for (size_t i = 0; i < includedElementsCount; i++)
	{
		std::construct_at(newData + i, std::move(operator[](i)));
		std::destruct_at(data + ((head + i) & cap));
	}
	alloc.deallocate(data, cap);
	cap = newCap;
	data = newData;
	head = 0;
	tail = size;
}

template<class T, class Allocator>
const T& Deque<T, Allocator>::front() const
{
	return data[head];
}

template<class T, class Allocator>
T Deque<T, Allocator>::front()
{
	return data[head];
}

template<class T, class Allocator>
const T& Deque<T, Allocator>::back() const
{
	return data[(tail ? tail : cap) - 1];
}

template<class T, class Allocator>
T Deque<T, Allocator>::back()
{
	return data[(tail ? tail : cap) - 1];
}

template<class T, class Allocator>
const T& Deque<T, Allocator>::operator[](size_t ind) const
{
	return data[(head + ind) % cap];
}

template<class T, class Allocator>
T& Deque<T, Allocator>::operator[](size_t ind)
{
	return data[(head + ind) % cap];
}

template<class T, class Allocator>
template<typename ...Args>
void Deque<T, Allocator>::emplace_front(Args && ...args)
{
	if (size >= cap) {
		resize();
	}
	moveIndex(head, false);
	std::construct_at(data + head, std::forward<Args>(args)...);
	size++;
}

template<class T, class Allocator>
template<typename ...Args>
void Deque<T, Allocator>::emplace_back(Args && ...args)
{
	if (size >= cap) {
		resize();
	}
	std::construct_at(data + tail, std::forward<Args>(args)...);
	moveIndex(tail, true);
	size++;
}
