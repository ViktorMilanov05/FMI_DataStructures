#include <iostream>

template <typename T>
class DoublyLinkedList {
	struct Node {
		T data;
		Node* next = nullptr;
		Node* prev = nullptr;
		Node(const T& data) : data(data), next(nullptr), prev(nullptr) {};
	};
	Node* head = nullptr;
	Node* tail = nullptr;
	size_t count = 0;

	void copyFrom(const DoublyLinkedList& other);
	void moveFrom(DoublyLinkedList&& other);
	void free();
public:
	DoublyLinkedList() : head(nullptr), tail(nullptr), count(0) {};
	DoublyLinkedList(const DoublyLinkedList<T>& other);
	DoublyLinkedList(DoublyLinkedList<T>&& other);
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
	DoublyLinkedList<T>& operator=(DoublyLinkedList<T>&& other);
	~DoublyLinkedList();

	void pushBack(const T& el);
	void pushBack(T&& el);
	void pushFront(const T& el);
	void pushFront(T&& el);
	void popBack();
	void popFront();
	T& front() { if (isEmpty()) { throw std::exception(); } return head->data; };
	const T& front() const { if (isEmpty()) { throw std::exception(); } return head->data; };
	T& back() { if (isEmpty()) { throw std::exception(); } return tail->data; };
	const T& back() const { if (isEmpty()) { throw std::exception(); } return tail->data; };
	void print() const;
	size_t getSize() const { return count; };
	bool isEmpty() const { return head == nullptr; }
	void clear();
	class DLLIterator;
	class ConstDLLIterator;
	DLLIterator insert(const T& el, const ConstDLLIterator& iter);
	DLLIterator remove(const DLLIterator& iter);
	DLLIterator begin() { return DLLIterator((*this), head); }
	ConstDLLIterator c_begin() { return ConstDLLIterator((*this), head); }
	DLLIterator end() { return DLLIterator((*this), nullptr); }
	ConstDLLIterator c_end() { return ConstDLLIterator((*this), nullptr); }
};

template<typename T>
void DoublyLinkedList<T>::pushBack(const T& el)
{
	Node* toAdd = new Node(el);
	if (isEmpty()) {
		head = tail = toAdd;
	}
	else {
		toAdd->prev = tail;
		tail->next = toAdd;
		tail = toAdd;
	}
	count++;
}

template<typename T>
void DoublyLinkedList<T>::pushBack(T&& el)
{
	Node* toAdd = new Node(std::move(el));
	if (isEmpty()) {
		head = tail = toAdd;
	}
	else {
		toAdd->prev = tail;
		tail->next = toAdd;
		tail = toAdd;
	}
	count++;
}

template<typename T>
void DoublyLinkedList<T>::pushFront(const T& el)
{
	Node* toAdd = new Node(el);
	if (isEmpty()) {
		head = tail = toAdd;
	}
	else {
		toAdd->next = head;
		head->prev = toAdd;
		head = toAdd;
	}
	count++;
}

template<typename T>
void DoublyLinkedList<T>::pushFront(T&& el)
{
	Node* toAdd = new Node(std::move(el));
	if (isEmpty()) {
		head = tail = toAdd;
	}
	else {
		toAdd->next = head;
		head->prev = toAdd;
		head = toAdd;
	}
	count++;
}

template<typename T>
void DoublyLinkedList<T>::popBack()
{
	if (isEmpty()) {
		throw std::exception();
	}
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node* toDel = tail;
		tail->prev->next = nullptr;
		tail = tail->prev;
		delete toDel;
	}
	count--;
}

template<typename T>
void DoublyLinkedList<T>::popFront()
{
	if (isEmpty()) {
		throw std::exception();
	}
	if (head == tail) {
		delete head;
		head = tail = nullptr;
	}
	else {
		Node* toDel = head;
		head->next->prev = nullptr;
		head = head->next;
		delete toDel;
	}
	count--;
}

template<typename T>
void DoublyLinkedList<T>::print() const
{
	Node* iter = head;
	while (iter) {
		std::cout << iter->data;
		if (iter != tail) {
			std::cout << " <-> ";
		}
		iter = iter->next;
	}
}

template<typename T>
void DoublyLinkedList<T>::clear()
{
	free();
}

template<typename T>
typename DoublyLinkedList<T>::DLLIterator DoublyLinkedList<T>::insert(const T& el, const ConstDLLIterator& iter)
{
	if (iter == c_begin()) {
		pushFront(el);
		return begin();
	}
	else if (iter == c_end) {
		pushBack(el);
		return DLLIterator(*this, tail);
	}
	else {
		Node* elToAdd = new Node(el);
		elToAdd->next = iter.currentElPtr;
		elToAdd->prev = iter.currentElPtr->prev;
		iter.currentElPtr->prev->next = elToAdd;
		iter.currentElPtr->prev = elToAdd;
		count++;
		return DLLIterator(*this, elToAdd);
	}
}

template<typename T>
typename DoublyLinkedList<T>::DLLIterator DoublyLinkedList<T>::remove(const DLLIterator& iter)
{
	Node* toRemove = iter.currentElIter;
	if (!toRemove) {
		std::exception();
	}
	if (toRemove == head) {
		popFront();
		return begin();
	}
	else if (toRemove == tail) {
		popBack();
		return end();
	}
	else {
		toRemove->prev->next = toRemove->next;
		toRemove->next->prev = toRemove->prev;
		Node* toReturn = toRemove->next;
		delete toRemove;
		count--;
		return DLLIterator(*this, toReturn);
	}
}

template<typename T>
void DoublyLinkedList<T>::copyFrom(const DoublyLinkedList& other)
{
	Node* iter = other.head;
	while (iter) {
		pushBack(iter->data);
		iter = iter->next;
	}
}

template<typename T>
void DoublyLinkedList<T>::moveFrom(DoublyLinkedList&& other)
{
	head = other.head;
	tail = other.tail;
	count = other.count;
	other.head = other.tail = nullptr;
	count = 0;
}

template<typename T>
void DoublyLinkedList<T>::free()
{
	Node* iter = head;
	while (iter) {
		Node* toDel = iter;
		iter = iter->next;
		delete toDel;
	}
	count = 0;
	head = tail = nullptr;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
{
	copyFrom(other);
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList<T>&& other)
{
	moveFrom(std::move(other));
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other)
{
	if (this != &other) {
		free();
		copyFrom(other);
	}
	return *this;
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList<T>&& other)
{
	if (this != &other) {
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	free();
}