#include "BrowserLinkedList.h"

BrowserLinkedList::BrowserLinkedList() : head(nullptr), tail(nullptr), count(0){}

bool BrowserLinkedList::isEmpty() const { return count == 0; }

void BrowserLinkedList::pushBack(const Tab& el)
{
    Node* added = new Node(el);
    count++;
    if (isEmpty())
        head = tail = added;
    else
    {
        tail->next = added;
        added->prev = tail;
        tail = added;
    }
}

void BrowserLinkedList::pushBack(Tab&& el)
{
    Node* added = new Node(std::move(el));
    count++;
    if (isEmpty())
        head = tail = added;
    else
    {
        tail->next = added;
        added->prev = tail;
        tail = added;
    }
}

void BrowserLinkedList::pushFront(const Tab& el)
{
    Node* added = new Node(el);
    if (isEmpty())
    {
        head = tail = added;
    }
    else
    {
        added->next = head;
        head->prev = added;
        head = added;
    }
    count++;
}

void BrowserLinkedList::pushFront(Tab&& el)
{
    Node* added = new Node(std::move(el));
    if (isEmpty())
    {
        head = tail = added;
    }
    else
    {
        added->next = head;
        head->prev = added;
        head = added;
    }
    count++;
}

void BrowserLinkedList::popBack()
{
    if (isEmpty())
        throw std::runtime_error("The list is empty!");

    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        tail->prev->next = nullptr;

        Node* toDelete = tail;
        tail = tail->prev;

        delete toDelete;

    }
    count--;
}

void BrowserLinkedList::popFront()
{
    if (isEmpty())
        throw std::runtime_error("The list is empty!");


    if (head == tail)
    {
        delete head;
        head = tail = nullptr;
    }
    else
    {
        head->next->prev = nullptr;

        Node* toDelete = head;
        head = head->next;

        delete toDelete;
    }

    count--;
}

BrowserLinkedList::DllIterator BrowserLinkedList::insert(const Tab& element, const ConstDllIterator& it)
{
    if (isEmpty())
    {
        pushFront(element);
        return begin();
    }
    else if (it.currentElementPtr == tail || count == 1)
    {
        pushBack(element);
        return DllIterator(this, tail);
    }
    else
    {
        Node* current = it.currentElementPtr;
        Node* newNode = new Node(element);

        newNode->prev = current;
        newNode->next = current->next;
        current->next->prev = newNode;
        current->next = newNode;
        count++;

        return DllIterator(this, newNode);
    }
}

BrowserLinkedList::DllIterator BrowserLinkedList::remove(const DllIterator& it)
{
    Node* toDelete = it.currentElementPtr;
    if (!toDelete)
        throw std::runtime_error("Cannot remove end iterator");

    if (toDelete == head)
    {
        popFront();
        return begin();
    }
    else if (toDelete == tail)
    {
        popBack();
        return DllIterator(this, tail);
    }
    else
    {
        toDelete->prev->next = toDelete->next;
        toDelete->next->prev = toDelete->prev;
        Node* nextNode = toDelete->next;

        delete toDelete;
        count--;

        return DllIterator(this, nextNode);
    }
}

const Tab& BrowserLinkedList::front() const
{
    if (isEmpty())
        throw std::runtime_error("The list is empty!");

    return head->data;
}

const Tab& BrowserLinkedList::back() const
{
    if (isEmpty())
        throw std::runtime_error("The list is empty!");

    return tail->data;
}

Tab& BrowserLinkedList::front()
{
    if (isEmpty())
        throw std::runtime_error("The list is empty!");

    return head->data;
}

Tab& BrowserLinkedList::back()
{
    if (isEmpty())
        throw std::runtime_error("The list is empty!");

    return tail->data;
}

size_t BrowserLinkedList::getSize() const
{
    return count;
}

void BrowserLinkedList::clear()
{
    free();
}

void BrowserLinkedList::print(const ConstDllIterator& curr) const
{
    ConstDllIterator iter = cbegin();
    while (iter != cend())
    {
        if (iter == curr) {
            std::cout << "> ";
        }
        Tab toPrint = *iter;
        std::cout << toPrint.getUrl() << ' ' << toPrint.getTimestamp() << std::endl;
        iter++;
    }
}

BrowserLinkedList::DllIterator BrowserLinkedList::begin()
{
    return DllIterator(this, head);
}

BrowserLinkedList::DllIterator BrowserLinkedList::end()
{
    return DllIterator(this, nullptr);
}

BrowserLinkedList::ConstDllIterator BrowserLinkedList::cbegin() const
{
    return ConstDllIterator(this, head);
}

BrowserLinkedList::ConstDllIterator BrowserLinkedList::cend() const
{
    return ConstDllIterator(this, nullptr);
}

BrowserLinkedList::BrowserLinkedList(const BrowserLinkedList& other) : head(nullptr), tail(nullptr)
{
    copyFrom(other);
}

BrowserLinkedList& BrowserLinkedList::operator=(const BrowserLinkedList& other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

BrowserLinkedList::BrowserLinkedList(BrowserLinkedList&& other)
{
    moveFrom(std::move(other));
}

BrowserLinkedList& BrowserLinkedList::operator=(BrowserLinkedList&& other)
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

BrowserLinkedList::~BrowserLinkedList()
{
    free();
}

void BrowserLinkedList::copyFrom(const BrowserLinkedList& other)
{
    Node* otherIter = other.head;
    while (otherIter != nullptr)
    {
        pushBack(otherIter->data);
        otherIter = otherIter->next;
    }
}

void BrowserLinkedList::moveFrom(BrowserLinkedList&& other)
{
    head = other.head;
    tail = other.tail;
    count = other.count;
    other.head = other.tail = nullptr;
    other.count = 0;
}

void BrowserLinkedList::free()
{
    Node* iter = head;
    while (iter != nullptr)
    {
        Node* toDelete = iter;
        iter = iter->next;
        delete toDelete;
    }

    head = tail = nullptr;
    count = 0;
}

Tab& BrowserLinkedList::DllIterator::operator*()
{
    return currentElementPtr->data;
}

Tab* BrowserLinkedList::DllIterator::operator->()
{
    return &currentElementPtr->data;
}

BrowserLinkedList::DllIterator& BrowserLinkedList::DllIterator::operator++() {
    if (currentElementPtr)
        currentElementPtr = currentElementPtr->next;
    return *this;
}

BrowserLinkedList::DllIterator BrowserLinkedList::DllIterator::operator++(int) {
    DllIterator copy(*this);
    ++(*this);
    return copy;
}

BrowserLinkedList::DllIterator& BrowserLinkedList::DllIterator::operator--() {
    if (currentElementPtr)
        currentElementPtr = currentElementPtr->prev;
    else
        currentElementPtr = list->tail;
    return *this;
}

BrowserLinkedList::DllIterator BrowserLinkedList::DllIterator::operator--(int) {
    DllIterator copy(*this);
    --(*this);
    return copy;
}

BrowserLinkedList::ConstDllIterator BrowserLinkedList::DllIterator::toConst()
{
    return ConstDllIterator(list, currentElementPtr);
}

bool BrowserLinkedList::DllIterator::operator==(const DllIterator& rhs) const
{
    return currentElementPtr == rhs.currentElementPtr;
}

bool BrowserLinkedList::DllIterator::operator!=(const DllIterator& rhs) const
{
    return !(rhs == *this);
}

const Tab& BrowserLinkedList::ConstDllIterator::operator*() const
{
    return currentElementPtr->data;
}

const Tab* BrowserLinkedList::ConstDllIterator::operator->() const
{
    return &currentElementPtr->data;
}

BrowserLinkedList::ConstDllIterator& BrowserLinkedList::ConstDllIterator::operator++() {
    if (currentElementPtr)
        currentElementPtr = currentElementPtr->next;
    return *this;
}

BrowserLinkedList::ConstDllIterator BrowserLinkedList::ConstDllIterator::operator++(int) {
    ConstDllIterator copy(*this);
    ++(*this);
    return copy;
}

BrowserLinkedList::ConstDllIterator& BrowserLinkedList::ConstDllIterator::operator--() {
    if (currentElementPtr)
        currentElementPtr = currentElementPtr->prev;
    else
        currentElementPtr = list->tail;
    return *this;
}

BrowserLinkedList::ConstDllIterator BrowserLinkedList::ConstDllIterator::operator--(int) {
    ConstDllIterator copy(*this);
    --(*this);
    return copy;
}

bool BrowserLinkedList::ConstDllIterator::operator==(const ConstDllIterator& rhs) const
{
    return currentElementPtr == rhs.currentElementPtr;
}

bool BrowserLinkedList::ConstDllIterator::operator!=(const ConstDllIterator& rhs) const
{
    return !(rhs == *this);
}

void BrowserLinkedList::pushBackForMerge(Node*& resultBegin, Node*& resultEnd, Node* toAdd)
{
    if (!resultBegin)
    {
        resultBegin = resultEnd = toAdd;
    }
    else
    {
        resultEnd->next = toAdd;
        resultEnd = toAdd;
    }
}

bool BrowserLinkedList::compareByUrl(const Tab& first, const Tab& second) const
{
    if (first.getUrl() < second.getUrl()) {
        return true;
    }
    if (first.getUrl() == second.getUrl()) {
        return first.getTimestamp() <= second.getTimestamp();
    }
    return false;
}

bool BrowserLinkedList::compareByTimestamp(const Tab& first, const Tab& second) const
{
    if (first.getTimestamp() < second.getTimestamp()) {
        return true;
    }
    if (first.getTimestamp() == second.getTimestamp()) {
        return first.getUrl() <= second.getUrl();
    }
    return false;
}

BrowserLinkedList::Node* BrowserLinkedList::mergeLists(Node* first, Node* second, std::string by)
{
    Node* resultBegin = nullptr, * resultEnd = nullptr;

    if (by == "URL") {
        while (first && second)
        {
            if (compareByUrl(first->data, second->data))
            {
                pushBackForMerge(resultBegin, resultEnd, first);
                first = first->next;
            }
            else
            {
                pushBackForMerge(resultBegin, resultEnd, second);
                second = second->next;
            }
        }
    }
    else {
        while (first && second)
        {
            if (compareByTimestamp(first->data, second->data))
            {
                pushBackForMerge(resultBegin, resultEnd, first);
                first = first->next;
            }
            else
            {
                pushBackForMerge(resultBegin, resultEnd, second);
                second = second->next;
            }
        }
    }
    if (!first)
    {
        pushBackForMerge(resultBegin, resultEnd, second);
    }
    else
    {
        pushBackForMerge(resultBegin, resultEnd, first);
    }

    tail = resultEnd;
    return resultBegin;
}

BrowserLinkedList::Node* BrowserLinkedList::getMid(Node* list)
{
    Node* slow = list;
    Node* fast = list->next;

    while (fast && fast->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

BrowserLinkedList::Node* BrowserLinkedList::mergeSort(Node* list, std::string by)
{
    
    if(!list || !list->next) 
        return list;
        
    Node* mid = getMid(list);

        
    Node* left = list;
    Node* right = mid->next;
    mid->next = nullptr;
    
    left = mergeSort(left, by);
    right = mergeSort(right, by);
    
    return mergeLists(left, right, by);
}

BrowserLinkedList::DllIterator BrowserLinkedList::mergeSort(std::string by)
{
    head = mergeSort(head, by);
    Node* test = tail;
    return DllIterator(this, head);
}
