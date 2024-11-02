#include <iostream>

template <typename T>
class ConstDLLIterator {
	friend DoublyLinkedList<T>;
	Node* currentElPtr;
	DoublyLinkedList& list;

public:
	typedef std::bidirectional_iterator_tag iterator_category;
	ConstDLLIterator(DoublyLinkedList& list, Node* currentEl = nullptr) : currentElPtr(currentEl), list(list) {};
	ConstDLLIterator(const DLLIterator& iter) : currentElPtr(iter.currentElPtr), list(iter.list) {};
	const T& operator*() const { return currentElPtr->data; };
	const T* operator->() const { return &currentElPtr->data; }

	ConstDLLIterator& operator++() {
		if (currentElPtr)
			currentElPtr = currentElPtr->next;
		return (*this);
	}
	ConstDLLIterator operator++(int) {
		DLLIterator copy(*this);
		++(*this);
		return copy;
	}
	ConstDLLIterator& operator--() {
		if (currentElPtr)
			currentElPtr = currentElPtr->prev;
		else
			currentElPtr = list.tail;
		return (*this);
	}
	ConstDLLIterator operator--(int) {
		DLLIterator copy(*this);
		--(*this);
		return copy;
	}
	bool operator==(const DLLIterator& other) const { return currentElPtr == other.currentElPtr };
	bool operator!=(const DLLIterator& other) const { return currentElPtr != other.currentElPtr };
};