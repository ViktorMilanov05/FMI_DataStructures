#include <iostream>
#include "Tab.h";
#include <memory>

class BrowserLinkedList {

    struct Node
    {
        Node(const Tab& data) : data(data), next(nullptr), prev(nullptr) {}
        Tab data;
        Node* next;
        Node* prev;
    };

    size_t count = 0;
    Node* tail = nullptr;
    Node* head = nullptr;

    void copyFrom(const BrowserLinkedList& other);
    void moveFrom(BrowserLinkedList&& other);
    void free();

    bool compareByUrl(const Tab& first, const Tab& second) const;
    bool compareByTimestamp(const Tab& first, const Tab& second) const;
    Node* getMid(Node* list);
    Node* mergeSort(Node* list, std::string by);
    Node* mergeLists(Node* first, Node* second, std::string by);
    void pushBackForMerge(Node*& resultBegin, Node*& resultEnd, Node* toAdd);
public:
    BrowserLinkedList();
    BrowserLinkedList(const BrowserLinkedList& other);
    BrowserLinkedList(BrowserLinkedList&& other);

    BrowserLinkedList& operator=(const BrowserLinkedList& other);
    BrowserLinkedList& operator=(BrowserLinkedList&& other);
    ~BrowserLinkedList();

    void pushBack(const Tab& el); 
    void pushBack(Tab&& el);
    void pushFront(const Tab& el);
    void pushFront(Tab&& el);
    void popBack();
    void popFront();

    const Tab& front() const;
    const Tab& back() const;

    Tab& front();
    Tab& back();

    size_t getSize() const;

    bool isEmpty() const;

    void clear();

    class DllIterator;
    class ConstDllIterator;

    DllIterator insert(const Tab& element, const ConstDllIterator& it);
    DllIterator remove(const DllIterator& it);

    void print(const ConstDllIterator& curr) const;

    DllIterator begin();
    DllIterator end();
    ConstDllIterator cbegin() const;
    ConstDllIterator cend() const;

    DllIterator mergeSort(std::string by);

    class DllIterator
    {
        BrowserLinkedList* list;
        friend class DoublyLinkedList;

    public:
        Node* currentElementPtr; // should be private and for that I have friend class DoublyLinkedList, but can't access it and for that I put it as public
        typedef std::bidirectional_iterator_tag iterator_category;

        DllIterator(BrowserLinkedList* list, Node* currentElementPtr = nullptr) : list(list), currentElementPtr(currentElementPtr) {}

        Tab& operator*();
        Tab* operator->();

        DllIterator& operator++();

        DllIterator operator++(int);

        DllIterator& operator--();

        DllIterator operator--(int);

        ConstDllIterator toConst();

        bool operator==(const DllIterator& rhs) const;
        bool operator!=(const DllIterator& rhs) const;
    };

    class ConstDllIterator
    {
        const BrowserLinkedList* list;

        friend class DoublyLinkedList;

    public:
        Node* currentElementPtr; // should be private and for that I have friend class DoublyLinkedList, but can't access it and for that I put it as public

        typedef std::bidirectional_iterator_tag iterator_category;

        ConstDllIterator(const BrowserLinkedList* list, Node* currentElementPtr = nullptr) : list(list), currentElementPtr(currentElementPtr) {}

        const Tab& operator*() const;
        const Tab* operator->() const;

        ConstDllIterator& operator++();

        ConstDllIterator operator++(int);

        ConstDllIterator& operator--();

        ConstDllIterator operator--(int);

        bool operator==(const ConstDllIterator& rhs) const;
        bool operator!=(const ConstDllIterator& rhs) const;
    };
};