#include <iostream>

template <typename T>
class DLLIterator {
	friend DoublyLinkedList<T>;
	Node* currentElPtr;
	DoublyLinkedList& list;

public:
	typedef std::bidirectional_iterator_tag iterator_category;
	DLLIterator(DoublyLinkedList& list, Node* currentEl = nullptr) : currentElPtr(currentEl), list(list) {};
	T& operator*() { return currentElPtr->data; };
	T* operator->() { return &currentElPtr->data; }

	DLLIterator& operator++() {
		if (currentElPtr)
			currentElPtr = currentElPtr->next;
		return (*this);
	}
	DLLIterator operator++(int) {
		DLLIterator copy(*this);
		++(*this);
		return copy;
	}
	DLLIterator& operator--() {
		if (currentElPtr)
			currentElPtr = currentElPtr->prev;
		else
			currentElPtr = list.tail;
		return (*this);
	}
	DLLIterator operator--(int) {
		DLLIterator copy(*this);
		--(*this);
		return copy;
	}
	bool operator==(const DLLIterator& other) const { return currentElPtr == other.currentElPtr };
	bool operator!=(const DLLIterator& other) const { return currentElPtr != other.currentElPtr };
};